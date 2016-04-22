#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 1;

int buttonPin = 4;
int testNum = 1;

int buttonState = 0; //Button state
int lastButtonState = LOW; 
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 100;

int brightness = 0; // for photoresistor

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() {
  Serial.begin(9600);
  matrix.setIntensity(0);
  randomSeed(analogRead(0));
  pinMode(buttonPin, INPUT_PULLUP);    // no need for resistors
}

int wait = 50;
int inc = -2;
byte byteRead = 0;
void loop() {
/*
  if(Serial.available() > 0)
  {
    byteRead = Serial.read() - '0';
    Serial.println(byteRead);

    //Test is assuming byteRead is already mapped between 0-7
    matrix.fillScreen(LOW);
    //test3(byteRead);
    pick_pattern(byteRead);
    matrix.write();
    
  }
*/
 int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
          testNum++;
          checkNum();
      }
    }
  }
 
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;


  int temp = random(0,8);

  matrix.fillScreen(LOW);

  playTest(testNum, temp);

  matrix.write();

  delay(50);
  
  // dim display if dark, brighten if bright 
  brightness = map(analogRead(1), 0, 1023, 0, 3);
  matrix.setIntensity(brightness);
}

void playTest(int testNumber, int input)
{
  if(testNumber == 1)
  {
    test(input);
  }
  else if(testNumber == 2)
  {
    test2(input);
  }
  else if(testNumber == 3)
  {
    test3(input);
  }
}


void checkNum()
{
  if(testNum >= 4)
  {
    testNum = 0;
  }
}

void test(int input)
{
  testNum = 1;
  
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

//Draws ONE bar onto the led matrix (Main Bar)
void drawBar(int row, int input)
{
  matrix.drawLine(row, 0, row, input, HIGH);
}

//Draws the remaining columns onto the led matrix
void drawRemainder(int row, int input)
{
  int newY;         //Y Axis
  int counter = 1;  //Counter used to modify how high the bar is

  //Loops through each possible rows (Moving to the right)
  for(int i = row+1; i < 8; i++)
  {
    //New random y-axis depending on its x-axis location + counter
    newY = random(0,input-counter);
    matrix.drawLine(i, 0, i, newY, HIGH);
    counter+=1;
  }

  //Resets counter
  counter = 1;

  //Loops through (Moving to the left)
  for(int i = row-1; i >= 0; i--)
  {
    //Same as above
    int newY = random(0,input-counter);
    matrix.drawLine(i, 0, i, newY, HIGH);
    counter+=1;
  }
}

void test2(int input)
{
  testNum = 2;
  
  //Low Volume
  if(input == 0)
  {
    drawBar2(0, input);    
  }
  if(input == 1)
  {
    drawBar2(1, input);
  }
  if(input == 2)
  {
    drawBar2(2, input);
  }
  //Medium Volume
  if(input == 3)
  {
    drawBar2(3, input);
  }
  if(input == 4)
  {
    drawBar2(4, input);
  }
  if(input == 5)
  {
    drawBar2(5, input);
  }
  if(input == 6)
  {
    drawBar2(6, input);
  }
  //High Volume
  if(input == 7)
  {
    drawBar2(7, input);
  }
}

void drawBar2(int row, int input)
{
  for(int i = 0; i < 8; i++)
  {
    matrix.fillScreen(LOW);
    matrix.drawLine(0,0 , i-input, input, HIGH);
    matrix.write();
  }
}


void test3(int input)
{
  testNum = 3;
  
  //Low Volume
  if(input == 0)
  {
    drawRectBeat(0, input);    
  }
  if(input == 1)
  {
    drawRectBeat(1, input);
  }
  if(input == 2)
  {
    drawRectBeat(2, input);
  }
  //Medium Volume
  if(input == 3)
  {
    drawRectBeat(3, input);
  }
  if(input == 4)
  {
    drawRectBeat(4, input);
  }
  if(input == 5)
  {
    drawRectBeat(5, input);
  }
  if(input == 6)
  {
    drawRectBeat(6, input);
  }
  //High Volume
  if(input == 7)
  {
    drawRectBeat(7, input);
  }
}

void drawRectBeat(int row, int input)
{
  int newRow = 8-row;
  matrix.drawRect(newRow, newRow, input, input, HIGH);
}
