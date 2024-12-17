#include <Arduino.h>

#define LedRedPin 13
#define LedOrangePin 12
#define LedGreenPin 11

#define RedPhaseTime 5000
#define RedOrangePhaseTime 5000
#define GreenPhaseTime 5000
#define GreenBlinkCount 4
#define GreenBlinkTime 500
#define OrangePhaseTime 2000


enum TrafficLightStates {
  RedPhase,
  RedOrangePhase,
  GreenPhase,
  GreenBlinkPhase,
  OrangeAfterGreenPhase,
  UndefinedState
};

void setup() {
  pinMode(LedRedPin, OUTPUT);
  pinMode(LedOrangePin, OUTPUT);
  pinMode(LedGreenPin, OUTPUT);

  digitalWrite(LedRedPin, HIGH);
  digitalWrite(LedOrangePin, LOW);
  digitalWrite(LedGreenPin, LOW);
}

uint8_t TrafficLightState = RedPhase;

void loop() {
  switch (TrafficLightState) {
    case RedPhase:
      digitalWrite(LedRedPin, HIGH);
      digitalWrite(LedOrangePin, LOW);
      digitalWrite(LedGreenPin, LOW);
      delay(RedPhaseTime);
      TrafficLightState = RedOrangePhase;
      break;
    case RedOrangePhase:
      digitalWrite(LedRedPin, HIGH);
      digitalWrite(LedOrangePin, HIGH);
      digitalWrite(LedGreenPin, LOW);
      delay(RedOrangePhaseTime);
      TrafficLightState = GreenPhase;
      break;
    case GreenPhase:
      digitalWrite(LedRedPin, LOW);
      digitalWrite(LedOrangePin, LOW);
      digitalWrite(LedGreenPin, HIGH);
      delay(GreenPhaseTime);
      TrafficLightState = GreenBlinkPhase;
      break;
    case GreenBlinkPhase:
      for (int i = 0; i <= GreenBlinkCount; i++) {
        digitalWrite(LedGreenPin, HIGH);
        digitalWrite(LedRedPin, LOW);
        digitalWrite(LedOrangePin, LOW);
        delay(GreenBlinkTime);
        digitalWrite(LedGreenPin, LOW);
        delay(GreenBlinkTime);
      }
      TrafficLightState = OrangeAfterGreenPhase;
      break;
    case OrangeAfterGreenPhase:
      digitalWrite(LedRedPin, LOW);
      digitalWrite(LedOrangePin, HIGH);
      digitalWrite(LedGreenPin, LOW);
      delay(OrangePhaseTime);
      TrafficLightState = RedPhase;
      break;
    case UndefinedState:
      digitalWrite(LedRedPin, HIGH);
      digitalWrite(LedOrangePin, LOW);
      digitalWrite(LedGreenPin, LOW);
      TrafficLightState = GreenPhase;
      break;
    default:
      digitalWrite(LedRedPin, HIGH);
      digitalWrite(LedOrangePin, HIGH);
      digitalWrite(LedGreenPin, HIGH);
      TrafficLightState = RedPhase;
  }
}