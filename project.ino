#include <LedControl.h>

int DIN = 12;
int CS =  11;
int CLK = 10;

LedControl lc=LedControl(DIN,CLK,CS,0);

byte temp[8]={B11111111,B11111110,B11111100,B11111000,B11110000, B11100000, B11000000, B10000000}; 

int moveCounter = 0;
boolean moveBack = false;

void setup(){
 lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
 lc.setIntensity(0,1);      // Set the brightness to maximum value
 lc.clearDisplay(0);         // and clear the display
}

void loop(){ 
    //int randNumber = random(256);

    somethingWorks();
    delay(100);
}

void doSomething()
{
  for(int i = 0; i < 8; i++)
  {
    
    lc.setColumn(0,i, temp[i]);
  }
}

void somethingWorks()
{
  byte tempHolder;

  if(moveCounter == 8)
  {
    moveBack = true;
    moveCounter--;
  }
  else if(moveCounter == -1)
  {
    moveBack = false;
    moveCounter++;
  }


  for(int i = 0; i < moveCounter; i++)
  {
    lc.setColumn(0, i, temp[7-i]);
  }

  for(int i = moveCounter; i < 8; i++)
  {
    lc.setColumn(0, i, temp[i-moveCounter]);
  }

  if(moveBack)
  {
    moveCounter--;
  }
  else
  {
    moveCounter++;
  }
  
}

