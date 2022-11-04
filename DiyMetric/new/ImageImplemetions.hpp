#ifndef _IMAGE_IMPL_H_
#define _IMAGE_IMPL_H_

#include <Arduino.h>
#include "Image.hpp"
#include "GIFDecoder/GifDecoder.h"
#include "Time.hpp"


class GIFImage : public Image, public ImageCallback {
    private:
        uint16_t ptr_Cursor;
        uint16_t currentDelay; // for Frame Animations
        uint8_t currentFrame, lastFrame;
        uint8_t currentFrameDuration;
        bool decodingStarted;

        bool fileSeekCallback(unsigned long position);
        unsigned long filePositionCallback(void);
        int fileReadCallback(void);
        int fileReadBlockCallback(void *buffer, int numberOfBytes);
        void updateScreenCallback(void);
        void screenClearCallback(void);
        void drawPixelCallback(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue);

        GifDecoder<9, 9, 11> gifDecoder;
        
        void startDecoding();

    protected:

    public:
        GIFImage();
        //virtual ~GIFImage();
        void Init();
        void Update();
        void Render();
};

GIFImage::GIFImage(){
    fileType = Image::ImageType::GIF;
}

void GIFImage::Init(){
    p_imageData = imageBuffer;
    
    gifDecoder.setImageCallback(this);

    decodingStarted = false;
    startDecoding();    


}

void GIFImage::Update(){ 
}

void GIFImage::Render(){
    // TODO: any timing issues here?
    currentDelay += Time::getDeltaTime();
    if(currentDelay > gifDecoder.getFrameDelay_ms()) {
        gifDecoder.decodeFrame();
        currentFrame = gifDecoder.getFrameNo();
        if(currentFrame == lastFrame) {
            gifDecoder.decodeFrame();
            currentFrame = gifDecoder.getFrameNo();
        }
        lastFrame = currentFrame;
        currentDelay -= gifDecoder.getFrameDelay_ms();
        currentDelay = 0;
        
    }
    //drawScreen();
}

void GIFImage::startDecoding(){
    if (!decodingStarted) {
        decodingStarted = true;
        gifDecoder.startDecoding();
    }
}

bool GIFImage::fileSeekCallback(unsigned long position){
    ptr_Cursor = position; 
    ptr_Cursor %= p_imageSize; 
    return true;
}

unsigned long GIFImage::filePositionCallback(void){
    ptr_Cursor %= p_imageSize;
    return ptr_Cursor;
}

int GIFImage::fileReadCallback(void){
    ptr_Cursor %= p_imageSize;
    return *(p_imageData + ptr_Cursor++);
}

int GIFImage::fileReadBlockCallback(void *buffer, int numberOfBytes){
    int readBytes = 0;

    char *destinationBuffer = (char*)buffer;

    for(; readBytes < numberOfBytes; readBytes++){
        destinationBuffer[readBytes] = p_imageData[ptr_Cursor++];
    }

    ptr_Cursor %= p_imageSize;
    return readBytes;

}

void GIFImage::updateScreenCallback(void){
}

void GIFImage::screenClearCallback(void){
}

void GIFImage::drawPixelCallback(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue){

    ledMatrix.drawPixel(x, y, getColor(red, green, blue));
}


#endif 