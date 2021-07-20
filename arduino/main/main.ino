#include <Encoder.h>

// Array of encoders
Encoder enc[] = {Encoder(3,2), Encoder(6,5)};
int encSize = sizeof(enc)/sizeof(Encoder);

void setup()
{
  Serial.begin(115200); //open a serial port
}

void loop()
{
  // Loop through encoders
  for (int i = 0; i < encSize; i++) {

    // Read encoder value - relative to reset value
    int pos = enc[i].read()/2;
    
    // Check if value is different to reset value
    if (pos != 0) {
      // -- DEBUG --
      // Serial.println(i);
      // Serial.println(pos);
      // Serial.println("");
      // ------------

      // Send encoder index and value (direction)
      switch (pos) {
        case -1:
          Serial.print(String(i) + "0");
          break;
        case 1:
          Serial.print(String(i) + "1");
          break;
      }

      // Reset encoder value
      enc[i].write(0);
    }
  }
  
  delay(1); //delay for stability
}
