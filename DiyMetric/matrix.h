#ifndef _MATRIX_H
    #define _MATRIX_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>

#include "font.h"

#define PIN 5
#define WIDTH 32
#define HEIGHT 8

Adafruit_NeoMatrix ledMatrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, PIN, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG, NEO_GRB + NEO_KHZ800);

uint32_t getColor(byte r,byte g,byte b){
    return ledMatrix.Color(r,g,b);  
}

byte brightness = 40;
uint32_t defaultFontColor = getColor(255,0,0);


// TEXT STUFF
String Text = "";
int16_t textX,textY;
uint16_t textWidth, textHeight;
////////////////////////////

void clearScreen(){
    ledMatrix.fillScreen(0);
    
}

void drawScreen(){
    ledMatrix.show();  
}

void initMatrix(){
    ledMatrix.setFont(&Picopixel);
    ledMatrix.begin();
    ledMatrix.setTextWrap(false);
    ledMatrix.setBrightness(brightness);
    ledMatrix.setTextColor(defaultFontColor);
}

uint16_t getTextWidth(String text){
    int16_t x2,y2;
    uint16_t w2,h2;
    ledMatrix.getTextBounds(text,0,0,&x2,&y2,&w2,&h2);
    return w2;
}

uint16_t getTextHeight(String text){
    int16_t x2,y2;
    uint16_t w2,h2;
    ledMatrix.getTextBounds(text,0,0,&x2,&y2,&w2,&h2);
    return h2;
}

#endif
