#include <Encoder.h>

/* 
 *  https://core-electronics.com.au/tutorials/how-to-use-rotary-encoders.html
*/
long posEnc1;

Encoder enc1(2,3);  //create an object for the encoder

void setup()
{
  Serial.begin(115200); //open a serial port
}

void loop()
{
  long newEnc1; //create variable for holding new encoder value
  newEnc1 = enc1.read()/2;  //read the encoder values, and divide by four to get a single increment/notch
  if (newEnc1 != posEnc1) //if there is a change between the current reading and the last reading
  {
    Serial.println(newEnc1);  //print the current counter
    posEnc1 = newEnc1;  //update the last position to the current position
  }
  delay(1); //delay for stability
}
