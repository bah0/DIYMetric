#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino.h>

const int buf_size = 4096;
int image_size = 0;
unsigned char image_buffer[buf_size];
unsigned char* ptrimagebuf;
String contentType = "";

const char* headerKeys[] = {"Content-Type"};
const size_t numHeaders = 1;


/*int downloadBitmap(String path) {
  WiFiClient client;
  HTTPClient http;

  // Serial.println("Begin HTTP..");
  if (http.begin(client, path)) {


    http.collectHeaders(headerKeys, numHeaders);
    int httpCode = http.GET();

    if (httpCode > 0) {

      // Serial.printf("HTTP GET Code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK || HTTP_CODE_MOVED_PERMANENTLY) {

        image_size = http.getSize();
        contentType = http.header("Content-Type");

        Serial.printf("Content-Length: %d bytes\n", image_size);
        Serial.printf("Content-Type: %s\n",contentType.c_str());
        


        // PAYLOAD
        WiFiClient* stream = http.getStreamPtr();

        int len = image_size; int index = 0;
        uint8_t readByte;

        if(buf_size < image_size) Serial.println("ERROR: image bigger than download buffer size");

        while (http.connected() && (len > 0 || len == -1)) {
          size_t size = stream->available();
          if (size) {
            readByte = stream->read();
           
            image_buffer[index++] = readByte;

            if (len > 0) len--;
          }
        }

        
        //delay(10);
        ptrimagebuf = image_buffer;
      }

    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();

  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }

  return image_size;
}
*/