#include <Arduino.h>
#include "matrix.h"

class View {
    protected:
      int16_t x = 0,y = 0,targetX = 0, targetY = 0;
      uint16_t w = 0, h = 0;
    public:
      virtual void update(double dT) = 0;
      virtual void render() = 0;
        
};

class TextOnly : public View{
    private:
      String Text = "";
      const byte leftPadding = 1, 
                rightPadding = 1;
      enum Modes {Center,Scroll};
      enum Modes renderMode;

      void renderCenter();
      void renderScroll(double dT);

      long timePassed = 0, bufferTime = 0;
      int startX,startY;
      bool delayModeBefore = true;
      bool delayModeAfter = false;
      
    public:
      TextOnly(String text, int16_t x, int16_t y);
      virtual void update(double dT);
      virtual void render();
      void updateText(String ntext);
      
      
      
};

class FrameText : public View{
    private:
      String Text = "";
      const byte leftPadding = 9, 
                rightPadding = 1;
      enum Modes {Center,Scroll};
      enum Modes renderMode;

      void renderCenter();
      void renderScroll(double dT);

      long timePassed = 0, bufferTime = 0;
      int startX,startY;
      bool delayModeBefore = true;
      bool delayModeAfter = false;

      uint32_t defaultColor;
      
    public:
      FrameText(String text, int16_t x, int16_t y);
      virtual void update(double dT);
      virtual void render();
      void updateText(String ntext);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FrameText::FrameText(String text, int16_t x, int16_t y){
      this->x = x;
      this->y = y;
      startX = x;
      startY = y;
      
      this->Text = text;

      this->w = getTextWidth(Text);
      this->h = getTextHeight(Text);

      defaultColor = getColor(0,255,255);
}

void FrameText::updateText(String ntext){
    Text = ntext;
    this->w = getTextWidth(Text);
    this->h = getTextHeight(Text);
    
    x = 0;
    timePassed += bufferTime;
    bufferTime = 0;
    delayModeAfter = false;
    delayModeBefore = true;

    int views = w/32;
    int modulo = w%32;
    targetX = (views-1)*(-32)-(modulo+leftPadding+rightPadding);
    
}

void FrameText::update(double dT){
    if(w + leftPadding - rightPadding <= 32 ){
        renderMode = Center;
      }
      else {
        
        renderMode = Scroll;  
      }
      
      
    switch(renderMode){
        case Center: renderCenter(); break;
        case Scroll: renderScroll(dT); break;
    }
}

void FrameText::render(){

    ledMatrix.print(Text);
    
    //for(int i=0;i<8;i++)
    //  for(int j=0;j<8;j++)
    //    ledMatrix.drawPixel(i,j,defaultColor);

    ledMatrix.drawLine(8,0,8,8,getColor(0,0,0));
}

void FrameText::renderCenter(){
    x = 24/2 - w/2;
    ledMatrix.setCursor(x+leftPadding-1, 5);
}

void FrameText::renderScroll(double dT){
      bufferTime += dT;
      int distance = startX - targetX;
      int steps = 1;
      int splitMS = 40;

      
      int delayMS = 2000;

      if(delayModeBefore){
        x=0;
         if(bufferTime > delayMS){
            timePassed += bufferTime;
            bufferTime = 0;   
            delayModeAfter = false;
            delayModeBefore = false;
         }
      }
      else if(delayModeAfter){
        if(bufferTime > delayMS){
            timePassed += bufferTime;
            bufferTime = 0;   
            delayModeAfter = false;
            delayModeBefore = true;
         }
      }
      else{
          
          if(x<=targetX){
            delayModeAfter = true;
            delayModeBefore = false;
          }
          else{
              if(bufferTime > splitMS){
                //x--;
                x-=steps;
                timePassed += bufferTime;
                bufferTime = 0;      
                
              }
          }  
      }

      
    ledMatrix.setCursor(x+leftPadding, 5);   
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextOnly::TextOnly(String text, int16_t x, int16_t y){
      this->x = x;
      this->y = y;
      startX = x;
      startY = y;
      
      this->Text = text;

      this->w = getTextWidth(Text);
      this->h = getTextHeight(Text);
}

void TextOnly::updateText(String ntext){
    Text = ntext;
    this->w = getTextWidth(Text);
    this->h = getTextHeight(Text);
    
    x = 0;
    timePassed += bufferTime;
    bufferTime = 0;
    delayModeAfter = false;
    delayModeBefore = true;

    int views = w/32;
    int modulo = w%32;
    targetX = (views-1)*(-32)-(modulo+leftPadding+rightPadding);
    
}

void TextOnly::update(double dT){
    if(w + leftPadding <= 32 ){
        renderMode = Center;
      }
      else {
        
        renderMode = Scroll;  
      }
      
      
    switch(renderMode){
        case Center: renderCenter(); break;
        case Scroll: renderScroll(dT); break;
    }
}

void TextOnly::render(){
    ledMatrix.print(Text);
    
}

void TextOnly::renderCenter(){
    x = WIDTH/2 - w/2;
    ledMatrix.setCursor(x, 5);
}

void TextOnly::renderScroll(double dT){
      bufferTime += dT;
      int distance = startX - targetX;
      int steps = 1;
      int splitMS = 40;

      
      int delayMS = 2000;

      if(delayModeBefore){
        x=0;
         if(bufferTime > delayMS){
            timePassed += bufferTime;
            bufferTime = 0;   
            delayModeAfter = false;
            delayModeBefore = false;
         }
      }
      else if(delayModeAfter){
        if(bufferTime > delayMS){
            timePassed += bufferTime;
            bufferTime = 0;   
            delayModeAfter = false;
            delayModeBefore = true;
         }
      }
      else{
          
          if(x<=targetX){
            delayModeAfter = true;
            delayModeBefore = false;
          }
          else{
              if(bufferTime > splitMS){
                //x--;
                x-=steps;
                timePassed += bufferTime;
                bufferTime = 0;      
                
              }
          }  
      }

      
    ledMatrix.setCursor(x+leftPadding, 5);   
}
/////////////////////////////////////////////////////////////////////////////////////
