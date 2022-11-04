#include <stdio.h>
#include <Ticker.h>
#include <Task.h>

#include <FS.h>
#include <LittleFS.h>

#include "matrix.h"
#include "wifi.h"
#include "View.h"
#include "ntp.h"

#include "upng.h"
#include "new/App.hpp"
#include "new/WifiConnection.hpp"

#define PNGBUF(x) upng_get_buffer(x)
#define DEBUG

//GifDecoder<9, 9, 11> decoder;
//uint16_t ptrCursor = 0;
File fileGif;

Ticker timeTicker;

utime espTime{0, 0, 0, 0};
String inputString = "";
bool stringComplete = false;

bool pngAvailable = false;

unsigned long lastTime, currentTime, loopTime, deltaTime;

struct RGBA
{
  uint32_t rgba;
};

RGBA img[8][8];

enum eimgType
{
  PNGtype,
  GIFtype,
  noType
};
typedef enum eimgType imgtype;
imgtype displayIMG;

// TextOnly sample("Hello",0,0);
FrameText sample("Hello", 0, 0);

uint16_t secs = 0;
const uint16_t max_secs = 86400; // 60*60*24
bool refreshTime = false;
String time_str = "";

//uint8_t currentFrame, lastFrame;
bool stopCode = false;

App app;

void updateTime()
{

  if (secs >= max_secs)
    refreshTime = true;

  uint8_t h, m, s, divh, divm, divs;

  divs = espTime.seconds / 60;
  s = (espTime.seconds) % 60;
  divm = (espTime.minutes + divs) / 60;
  m = (espTime.minutes + divs) % 60;
  divh = (espTime.hours + divm) / 24;
  h = (espTime.hours + divm) % 24;

  espTime.seconds = s;
  espTime.minutes = m;
  espTime.hours = h;

  time_str = formatUtime(espTime, false, true);
  sample.updateText(time_str);
  espTime.seconds++;
  ++secs;
}

void refreshUtime()
{
  if (refreshTime)
  {
    ntp_get_time(&espTime);
    refreshTime = false;
    secs = 0;
    Serial.println("Time refreshed");
  }
}

void setup()
{
  app.Setup();
  /* */
  /*unsigned long setupttime = millis();

  Serial.begin(9600);
  delay(200);


  ntp_client_setup();
  timeTicker.attach(1, updateTime);

  ntp_get_time(&espTime);
  // espTime.hours = 15;
  // espTime.minutes = 59;
  // espTime.seconds = 55;

  inputString.reserve(200);

  // Serial.printf("\nHEAP SPACE AVAILABLE: %d bytes", ESP.getFreeHeap());
  // Serial.printf("\nHEAP SPACE AVAILABLE: %d bytes", ESP.getFreeHeap());
  // Serial.printf("\nESP RESET REASON: %s ", ESP.getResetReason().c_str());
  // Serial.printf("\nESP SKETCH SIZE: %d ", ESP.getSketchSize());
  // Serial.printf("\nESP SKETCH SPACE AVAILABLE: %d ", ESP.getFreeSketchSpace());
  // Serial.printf("\nESP FLASH SIZE: %d ", ESP.getFlashChipSize());

  initMatrix();
  displayIMG = noType;
  FrameText sample("Hello", 0, 0);

  // Test Path: https://developer.lametric.com/content/apps/icon_thumbs/34.png
  // "http://developer.lametric.com/content/apps/icon_thumbs/7646.png" 620 ok - 4948 nok
  // downloadBitmap("http://developer.lametric.com/content/apps/icon_thumbs/3061.png");

  downloadBitmap("http://developer.lametric.com/content/apps/icon_thumbs/1443.gif");

  if (contentType == "image/png")
  {
    displayIMG = PNGtype;
    // upng_allocation();
    upngCallback();
  }
  if (contentType == "image/gif")
  {
    displayIMG = GIFtype;
    gif_allocation();
  }

  Serial.printf("\nRUNTIME: %lu", (millis() - setupttime));
  Serial.println("\nend setup, begin loop");

  lastTime = 0;
  currentTime = millis();
  loopTime = millis();
  */
}

void serialEvent()
{
  while (Serial.available())
  {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n')
    {
      stringComplete = true;
    }
  }
}

void render(/* double dT */)
{

  clearScreen();
  sample.render();
  if (displayIMG == PNGtype)
  {
    if (pngAvailable)
    {
      for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
          RGBA rgbacol = img[i][j];
          ledMatrix.drawPixel(i, j, rgbacol.rgba);
        }
    }
  drawScreen();
  }

  // if (displayIMG == GIFtype)
  // {
  //   decoder.decodeFrame();
  //   currentFrame = decoder.getFrameNo();
  //   if (currentFrame == lastFrame)
  //   {
  //     decoder.decodeFrame();
  //     currentFrame = decoder.getFrameNo();
  //   }
  //   lastFrame = currentFrame;

  //   drawScreen();
  //   delay(decoder.getFrameDelay_ms());
  // }
}

void loop()
{    
  app.Loop();
  /* 
  serialEvent();
  refreshUtime();

  update(deltaTime);
  render();
  */

}

void finish()
{
  fileGif.close();
  LittleFS.end();
}

void update(double dT)
{
  if (stringComplete)
  {
    sample.updateText(inputString);
    inputString = "";
    stringComplete = false;
  }

  sample.update(dT);
}

int calcTime()
{
  lastTime = currentTime;
  currentTime = millis();
  return (currentTime - lastTime);
}

void upngCallback()
{
  if (!pngAvailable)
  {
    upng_allocation();
    pngAvailable = true;
  }
}

void gif_allocation()
{
  bool fsformat;
  // if(!LittleFS.format()){
  //   Serial.println("Could not format FS");
  //   fsformat = false;
  // }
  bool xex = false;
  // if(!fsformat )
  if (!LittleFS.begin())
  {
    Serial.println("Could not format FS");
  }
  else
  {
    xex = LittleFS.exists("/test.gif");
  }

  // if(xex == false){ //file does not exist
  //     fileGif.write(ptrimagebuf,image_size);
  //     fileGif = LittleFS.open("/test.gif","w+");
  //     fileGif.close();
  // }

  Serial.println("\nwriting");
  fileGif = LittleFS.open("/test.gif", "w+");
  fileGif.write(ptrimagebuf, image_size);
  // xex = LittleFS.exists("/test.gif");
  // Serial.printf("gif exists: %d\n",xex);

  Serial.println("\nsetting callbacks");

  //decoder.startDecoding();
}

void upng_allocation()
{
  // PNG Magic Bytes als uint8_t = 137, 80, 78, 71
  // HEX: ‰PNG
  // PNGs sind in diesem Format: UPNG_RGBA8 = 32-bit RGBA
  // Das heißt:
  // Bit Depth = 8 -> 1 byte
  // Components = 4 -> RGBA
  // Zugriff auf die einzelnen Farbinformationen:
  //
  // über Pointer zum Buffer -> upng_get_buffer(upng);
  // loop bis 8*8 (width*height) / 4 (components) ... im Normalfall bei einem 8x8 Bild -> 256 / 4 = 64
  //
  // 8bit - 1 byte long -> R   = ptr + index * 4 components
  // 8bit - 1 byte long -> G   = ptr + index * 4 components + 1 (offset next color in bytes = 8 bit per color -> 1 byte)
  // 8bit - 1 byte long -> B   = ptr + index * 4 + 2
  // 8bit - 1 byte long -> A   = ptr + index * 4 + 3
  //
  // next pixel info from pointer ptr
  // ptr += components; -> ptr += 4 * index;
  //
  upng_t *upng;

  // Serial.println();
  // Serial.println("======================");
  // Serial.println("PNG Magic Bytes:");
  // Serial.println(*ptrimagebuf);
  // Serial.println(*(ptrimagebuf+1));
  // Serial.println(*(ptrimagebuf+2));
  // Serial.println(*(ptrimagebuf+3));
  // Serial.println("======================");

  upng = upng_new_from_bytes(ptrimagebuf, image_size);

  if (upng != NULL)
  {
    upng_decode(upng);
    Serial.print("Error: ");
    Serial.println(upng_get_error(upng));
    if (upng_get_error(upng) == UPNG_EOK)
    {
      // Serial.println("======================");
      // Serial.println("Image Metadata:");
      // Serial.printf("Image_WIDTH: %d\n",upng_get_width(upng));
      // Serial.printf("Image_HEIGHT: %d\n",upng_get_height(upng));
      // Serial.printf("Image_SIZE: %d\n",upng_get_size(upng));
      // Serial.printf("Image_BPP: %d\n",upng_get_bpp(upng));
      // Serial.printf("Image_BITDEPTH: %d\n",upng_get_bitdepth(upng));
      // Serial.printf("Image_PIXELSIZE: %d\n",upng_get_pixelsize(upng));
      // Serial.printf("Image_COMPONENTS: %d\n",upng_get_components(upng));
      // Serial.printf("Image_FORMAT: %d\n",upng_get_format(upng));
      // Serial.println("======================");
      for (int i = 0; i < 64; i++)
      {
        uint8_t r, g, b, a;
        r = *(PNGBUF(upng) + i * 4);
        g = *(PNGBUF(upng) + i * 4 + 1);
        b = *(PNGBUF(upng) + i * 4 + 2);
        a = *(PNGBUF(upng) + i * 4 + 3);
        RGBA pxl = {0};
        if (a == 0)
        {
          pxl.rgba = getColor(0, 0, 0);
        }
        else
        {
          pxl.rgba = getColor(r, g, b);
        }

        //  Serial.printf("Pos: %d:%d\n",i%8,i/8);
        //  Serial.printf("%d %d %d %d\n",r,g,b,a);
        img[i % 8][i / 8] = pxl;
      }
    }

    upng_free(upng);
    upng = NULL;
  }
}



// bool fileSeekCallback(unsigned long position)
// {
//   ptrCursor = position;
//   ptrCursor %= image_size;
//   return true;
// }

// unsigned long filePositionCallback(void)
// {
//   ptrCursor %= image_size;
//   return ptrCursor;
// }

// int fileReadCallback(void)
// {
//   ptrCursor %= image_size;
//   return *(ptrimagebuf + ptrCursor++);
// }

// int fileReadBlockCallback(void *buffer, int numberOfBytes)
// {
//   int readBytes = 0;

//   char *dbuf = (char *)buffer;
//   char *sbuf = (char *)ptrimagebuf;

//   for (; readBytes < numberOfBytes; readBytes++)
//   {
//     dbuf[readBytes] = sbuf[ptrCursor++];
//   }
//   ptrCursor %= image_size;
//   return readBytes;
// }

// void updateScreenCallback(void) {}

// void screenClearCallback(void) {}

// void drawPixelCallback(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue)
// {
// }
