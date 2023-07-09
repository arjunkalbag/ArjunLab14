#define PIN D2
#define IPIN D3

#include "oled-wing-adafruit.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

volatile uint16_t counter = 0;
volatile bool interruptOccured = false;
volatile bool InterruptsOn = true;
volatile bool buttonState = false;

OledWingAdafruit display;

void setup()
{
  display.setup();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  Serial.begin(9600);
  resetDisplay();
  display.display();
  pinMode(PIN, INPUT_PULLUP);
  pinMode(IPIN, INPUT_PULLUP);
  attachInterrupt(PIN, isr, FALLING);
}
void loop()
{
  display.loop();

  if (interruptOccured)
  {
    counter++;
    resetDisplay();
    display.println(counter);
    Serial.println(counter);
    display.display();
    interruptOccured = false;
  }
  if ((!digitalRead(IPIN)))
  {
    buttonState = true;
  }
  else if (buttonState)
  {
    InterruptsOn = !InterruptsOn;
    if (InterruptsOn)
    {
      interrupts();
    }
    else
    {
      noInterrupts();
    }
    buttonState = false;
  }
}
void resetDisplay()
{
  display.clearDisplay();
  display.setCursor(0, 0);
}
void isr()
{
  noInterrupts();
  interruptOccured = true;
  interrupts();
}