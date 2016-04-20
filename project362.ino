#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() {
  matrix.setIntensity(0);
  randomSeed(analogRead(0));

}

int wait = 50;
int inc = -2;

void loop() {

  //    HIGH = On. LOW = Off.
  //                       (firstPoint)   (SecPoint)    (HIGH OR LOW)
  //draw line paramater (xAxis, yAxis, x2Axis, y2Axis, Color)
/*
  int randFreq = random(0,8);
  int randInten = random(0,8);
  test(randInten, randFreq);
  drawRest(randFreq, randInten);
  matrix.write();
  delay(100);
  matrix.fillScreen(LOW);
*/

  beatDropBar();
}


void drawRest(int xPos, int yPos)
{
  int newY = yPos - 2;
  for(int i = xPos+1; i < 8; i++)
  {
    matrix.drawLine(i, 0, i, newY, HIGH);
    newY -= 2;
  }

  newY = yPos - 2;
  for(int i = xPos-1; i > 0; i--)
  {
    matrix.drawLine(i,0,i, newY, HIGH);
    newY -=2;
  }
}

void test(int inten, int freq)
{
  matrix.drawLine(freq, 0, freq, inten, HIGH);
}

void beatDropIntensity(int inten, int freq)
{
  int ranY = random(0,2);
  for(int x = 0; x < 8; x++)
  {
    if(freq > 90)
    {
      int newInten = map(inten, 0, 100, 0, 8);
      matrix.drawLine(x, 0, x, newInten, HIGH);
      x++;
    }
    
    matrix.drawLine(x, 0, x, ranY, HIGH);
    
  }
}


//Example
void beatDropBar()
{
  
  int ranX = random(0,8);
  matrix.fillScreen(LOW);
  for(int x = 0; x < 8; x++)
  { 
    int ranY = random(0,8);
    matrix.drawLine(x,0, x, ranY, HIGH);
    
    
  }
  matrix.write();
  delay(100);


}
