#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 1;

int brightness = 0; // for photoresistor

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() {
  Serial.begin(9600);
  matrix.setIntensity(0);
  randomSeed(analogRead(0));

}

int wait = 50;
int inc = -2;
byte byteRead = 0;

void loop() {

  if(Serial.available() > 0)
  {
    byteRead = Serial.read() - '0';
    Serial.println(byteRead);

    //Test is assuming byteRead is already mapped between 0-7
    matrix.fillScreen(LOW);
    test(byteRead);
    matrix.write();
    
  }

   // dim display if dark, brighten if bright 
   brightness = map(analogRead(1), 0, 1023, 0, 3);
   matrix.setIntensity(brightness);


  //    HIGH = On. LOW = Off.
  //                       (firstPoint)   (SecPoint)    (HIGH OR LOW)
  //draw line paramater (xAxis, yAxis, x2Axis, y2Axis, Color)
//
//  int randFreq = random(0,8);
//  int randInten = random(0,8);
//  test(randInten, randFreq);
//  drawRest(randFreq, randInten);
//  matrix.write();
//  delay(100);
//  matrix.fillScreen(LOW);
//
//
//  beatDropBar();

/*
int tester = random(0,8);

matrix.fillScreen(LOW);
test(6);
matrix.write();
delay(40);
*/
}

void test(int input)
{
  //Low Volume
  if(input == 0)
  {
    drawBar(0, input);
    drawRemainder(0, input);
  }
  if(input == 1)
  {
    drawBar(1, input);
    drawRemainder(1, input);
  }
  if(input == 2)
  {
    drawBar(2, input);
    drawRemainder(2, input);
  }
  //Medium Volume
  if(input == 3)
  {
    drawBar(3, input);
    drawRemainder(3, input);
  }
  if(input == 4)
  {
    drawBar(4, input);
    drawRemainder(4, input);
  }
  if(input == 5)
  {
    drawBar(5, input);
    drawRemainder(5, input);
  }
  if(input == 6)
  {
    drawBar(6, input);
    drawRemainder(6, input);
  }
  //High Volume
  if(input == 7)
  {
    drawBar(7, input);
    drawRemainder(7, input);
  }
}

void drawBar(int row, int input)
{
  matrix.drawLine(row, 0, row, input, HIGH);
}

void drawRemainder(int row, int input)
{
  int newY;
  int counter = 1;
  for(int i = row+1; i < 8; i++)
  {
    newY = random(0,input-counter);
    matrix.drawLine(i, 0, i, newY, HIGH);
    counter+=1;
  }

  counter = 1;
  
  for(int i = row-1; i >= 0; i--)
  {
    int newY = random(0,input-counter);
    matrix.drawLine(i, 0, i, newY, HIGH);
    counter+=1;
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
