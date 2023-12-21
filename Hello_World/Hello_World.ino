#include <Encoder.h>
#include <U8g2lib.h>

//IO Declarations
const int encoderPinA = 2; 
const int encoderPinB = 3;
const int encoderButtonPin = 4; // Encoder Button pin (SW)
const int estopPin = 5; // ESTOP button pin
const int beeperPin = 6; // Beeper pin
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10);

//Beep Logic
bool showBeepMessage = false; // Flag to indicate beep message should be shown
unsigned long beepMessageStartTime = 0; // Time when beep message started showing

//Encoder Tracking
unsigned long lastButtonPressTime = 0; 
Encoder myEnc(encoderPinA, encoderPinB);
long oldEncoderPos = -1; // Set to -1 to ensure the initial display update

void setup(void) {
  Serial.begin(9600); // Start serial communication at 9600 baud
  Serial.println("Starting...");

  u8g2.begin();
  u8g2.setContrast(100);
  
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderButtonPin, INPUT_PULLUP);
  pinMode(estopPin, INPUT_PULLUP);
  pinMode(beeperPin, OUTPUT);

  Serial.println("Setup complete.");
}

void loop(void) {
  unsigned long currentTime = millis();

  // Check if the e-stop button is pressed
  if (digitalRead(estopPin) == LOW) {
    // Reset the encoder position and update the display
    myEnc.write(0); // Reset the position in the encoder library
    oldEncoderPos = -1; // Force the display to update
    showBeepMessage = false; // Make sure the beep message is not displayed
    displayUpdate(0); // Update the display with the reset position
    Serial.println("E-stop pressed - counters reset.");
  }

  // Handle encoder position change
  long newEncoderPos = myEnc.read();
  if (newEncoderPos != oldEncoderPos) {
    oldEncoderPos = newEncoderPos;
    // Update the display with the new encoder position
    displayUpdate(newEncoderPos);
  }

  // Handle encoder button press
  if (digitalRead(encoderButtonPin) == LOW && currentTime - lastButtonPressTime > 200) { // Debounce the button
    lastButtonPressTime = currentTime;
    tone(beeperPin, 1000, 200); // Activate the beeper
    showBeepMessage = true; // Show beep message
    beepMessageStartTime = currentTime; // Record the time the beep message started
    Serial.println("Encoder button pressed - beep.");
    displayUpdate(newEncoderPos); // Update the display immediately
  }

  // Clear beep message after a delay without blocking
  if (showBeepMessage && currentTime - beepMessageStartTime > 200) {
    showBeepMessage = false; // Stop showing beep message after 1/5 second
    displayUpdate(newEncoderPos); // Update the display to clear the beep message
  }
}

void displayUpdate(long encoderPos) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(5, 10, "Melzi LCD Assembly");
  u8g2.drawStr(8, 25, "Hello World Demo");
  u8g2.drawStr(15, 40, " - CodyTheDoer");

  if (showBeepMessage) {
    u8g2.drawStr(25, 55, "Beep"); // Draw "Beep" on the screen
  }

  char encoderPosStr[10];
  sprintf(encoderPosStr, "%ld", encoderPos / 4); // Assuming 4 steps per notch
  u8g2.drawStr(100, 50, encoderPosStr); // Update encoder position
  u8g2.sendBuffer(); // Send buffer to the display
}