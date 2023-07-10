/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/admin/Desktop/Remys_Labs/Lab8/src/Lab8.ino"
#include <blynk.h>
#include <oled-wing-adafruit.h>
#include "env.h"

void setup();
void loop();
void readSensors();
#line 5 "/Users/admin/Desktop/Remys_Labs/Lab8/src/Lab8.ino"
#define PROX D0
#define GREEN D5
#define YELLOW D6
#define BLUE D7

bool displayOnOLED = true;
bool displayProximity = false;
bool displayLightLevel = false;
bool useBlynk = false;


SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;

void setup()
{
  display.setup();
  display.clearDisplay();
  display.display();
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(PROX, INPUT);

  Serial.begin(9600);

  // Blynk.begin(BLYNK_AUTH_TOKEN);
}

void loop()
{
  Blynk.run();
  display.loop();
  readSensors();
  BLYNK_WRITE(V0);
  BLYNK_WRITE(V2);
}
void readSensors()
{
  int proximityValue = analogRead(PROX);

  if (displayProximity)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Proximity:");
    display.setCursor(0, 10);
    display.print("Value: ");
    display.println(proximityValue);
    display.display();

    if (proximityValue < 200)
    {
      display.setTextColor(WHITE);
      display.println("BLUE LED: Very Close");
      display.display();
      digitalWrite(BLUE, HIGH);
      digitalWrite(YELLOW, LOW);
      digitalWrite(GREEN, LOW);
    }
    else if (proximityValue >= 200 && proximityValue < 600)
    {
      display.setTextColor(WHITE);
      display.println("YELLOW LED: Medium Distance");
      display.display();
      digitalWrite(BLUE, LOW);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(GREEN, LOW);
    }
    else
    {
      display.setTextColor(WHITE);
      display.println("GREEN LED: Far Away");
      display.display();
      digitalWrite(BLUE, LOW);
      digitalWrite(YELLOW, LOW);
      digitalWrite(GREEN, HIGH);
    }

    display.display();
  }

  if (display.pressedA())
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(proximityValue);
    display.display();
  }

  if (useBlynk)
  {
    Blynk.virtualWrite(V1, proximityValue);
  }
}

BLYNK_WRITE(V0)
{
  int buttonState = param.asInt();

  if (buttonState == LOW)
  {
    displayProximity = true;
    displayLightLevel = false;
    useBlynk = false;
    displayOnOLED = true;
  }
}

BLYNK_WRITE(V2)
{
  int buttonState = param.asInt();

  if (buttonState == LOW)
  {
    displayProximity = false;
    displayLightLevel = true;
    useBlynk = false;
    displayOnOLED = true;
  }
}
