#include <Encoder.h>

// Array of encoders
Encoder enc[] = {Encoder(3,2), Encoder(6,5)};
int encSize = sizeof(enc)/sizeof(Encoder);

// smol class for encoder button pin and state
class Button 
{
  public:
    Button();
    int pin;
    bool pressed;
    
  Button(int pin)
  {
    this->pin = pin;
    this->pressed = false;
  }
};

// gotta put this in the same order as encoder array
// e.g Button(4) is the button on Encoder(3,2)
// hopefully encSize will be reliable enough to use for this also
Button btn[] = {Button(4), Button(7)};


bool pressed = false;

void setup()
{
  Serial.begin(115200); //open a serial port
  
  for (int i = 0; i < encSize; i++) {
    pinMode(btn[i].pin, INPUT_PULLUP);
  }
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

  // Loop through buttons
  for (int i = 0; i < encSize; i++) {
    // if read button press and state was not pressed
    if (digitalRead(btn[i].pin) == LOW && !btn[i].pressed) {
      Serial.print(String(i) + "2");
      btn[i].pressed = true;
    }

    // if read button release and state was pressed
    if (digitalRead(btn[i].pin) == HIGH && btn[i].pressed) {
      Serial.print(String(i) + "3");
      btn[i].pressed = false;
    }
  }
  
  delay(1); //delay for stability
}
