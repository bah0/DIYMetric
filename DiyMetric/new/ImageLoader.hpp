#ifndef _IMAGE_LOADER_H_
#define _IMAGE_LOADER_H_

#define IL_ARRAYSIZE 6

#include <Arduino.h>
#include "ImageImplementations.hpp"
#include "WifiConnection.hpp"


class ImageLoader {
    private:
        //Image ImageArray[IL_ARRAYSIZE];

    protected:

    public:
        ImageLoader();
        //virtual ~ImageLoader(); causes some sort of issues
        void LoadImageFromURL(String url);
        void LoadImageFromFS(String path);
        void SaveImage(String path);
        void Update();
        void Render();
        void UnloadImage();
        int DownloadBitmap(String url, unsigned char* data);
        bool imageLoaded;

        GIFImage image;

};

ImageLoader::ImageLoader(){
    imageLoaded = false;
}


int ImageLoader::DownloadBitmap(String url, unsigned char* data ){
    WiFiClient client;
    HTTPClient http;

    const char* headerKeys[] = {"Content-Type"};
    const size_t numHeaders = 1;
    
    const int bufferSize = 4096;
    String contentType = "";

    // stuff to return
    int imageSize = 0;

  if (http.begin(client, url)) {

    http.collectHeaders(headerKeys, numHeaders);
    int httpCode = http.GET();

    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK || HTTP_CODE_MOVED_PERMANENTLY) {

        imageSize = http.getSize();
        contentType = http.header("Content-Type");

        WiFiClient* stream = http.getStreamPtr();
        Serial.printf("Content-Length: %d bytes\n", imageSize);
        Serial.printf("Content-Type: %s\n",contentType.c_str());
        
        int len = imageSize; int index = 0;
        uint8_t bytesRead;

        if(bufferSize < imageSize) Serial.println("ERROR: image bigger than download buffer size");

        while (http.connected() && (len > 0 || len == -1)) {
          size_t size = stream->available();
          if (size) {
            bytesRead = stream->read();
           
            data[index++] = bytesRead;

            if (len > 0) len--;
          }
        }
        
        //delay(10);
        //p_imageBuffer = imageBuffer;
      }

    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();

  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }


    Serial.println(data[0]);

  return imageSize;
}

void ImageLoader::LoadImageFromURL(String url){
  if(!imageLoaded){

    int len = DownloadBitmap(url, image.getImagePtr());
    image.setImageSize(len);
    image.Init();
    imageLoaded = true;

  }
    
}

void ImageLoader::LoadImageFromFS(String path){

}

void ImageLoader::SaveImage(String path){

}

void ImageLoader::Update(){
  if(imageLoaded) image.Update();
}

void ImageLoader::Render(){
  if(imageLoaded) image.Render();
}

void ImageLoader::UnloadImage(){

}



#endif