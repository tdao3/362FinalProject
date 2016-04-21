/****************************************
Example Sound Level Sketch for the 
Adafruit Microphone Amplifier

also led matrix control
****************************************/

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
 
void setup() 
{
   Serial.begin(9600);
}

int val;
void loop()  
{
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings, 1024 aka 5V is the max 
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 3.3) / 1024;  // convert to peakToPeak
    
//   if(peakToPeak > 0 && peakToPeak < 130)
//   {
//    Serial.print(1);
//   }
//   else if (peakToPeak > 140  && peakToPeak < 180)
//   {
//    Serial.print(2);
//   }
//   else if (peakToPeak > 179 && peakToPeak < 200)
//   {
//    Serial.print(3);
//   }
//   else if (peakToPeak > 199)
//   {
//    Serial.print(4);
//   }
//   Serial.println(peakToPeak);

     val = map(peakToPeak, 0, 1023, 0, 8);
     Serial.print(val);
}

