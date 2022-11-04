#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <Arduino.h>
#include "Vector.hpp"
#include "../matrix.h"

class ImageCallback{
    public:
        virtual bool fileSeekCallback(unsigned long position) = 0;
        virtual unsigned long filePositionCallback(void) = 0;
        virtual int fileReadCallback(void) = 0;
        virtual int fileReadBlockCallback(void *buffer, int numberOfBytes) = 0;
        virtual void updateScreenCallback(void) = 0;
        virtual void screenClearCallback(void) = 0;
        virtual void drawPixelCallback(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) = 0;

};

class Image {
    private:
        
    protected:
        unsigned char* p_imageData;
        unsigned char imageBuffer[4096];
        uint16_t p_imageSize;

        Vector2 startPosition, size;
        Vector2 referenceTo, maxSize; // referenceTo = reference position to calculate from ?
        enum ImageType {
            GIF,
            PNG
        };
        ImageType fileType;


    public:
        Image();
        virtual ~Image();
        virtual void Init();
        virtual void Update();
        virtual void Render();
        virtual void setImagePtr(unsigned char * pointer, uint8_t size);
        void setImageSize(uint16_t size) { p_imageSize = size < 4096 ? size : 4096; }
        unsigned char* getImagePtr(); 

};

Image::Image(){
    startPosition = Vector2{0.0f,0.0f};
    size = Vector2{0.0f,0.0f};

}
Image::~Image(){
    if(p_imageData){
        free(p_imageData);
        p_imageData = nullptr;
    }    

}


void Image::Init(){

}

void Image::Update(){

}

void Image::Render(){

}

void Image::setImagePtr(unsigned char * pointer, uint8_t size){
    p_imageData = pointer;
    p_imageSize = size;
}

unsigned char* Image::getImagePtr(){
    return imageBuffer;
}

#endif