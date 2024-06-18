#include <Arduino.h>
#include "state_machine.h"
#include "keypad.h"

// Define LED - PIN´s on Nucleo F401RE
#define LED_RED_LOCKED_PIN PC9
#define LED_GREEN_LOCK_1_PIN PC8
#define LED_GREEN_LOCK_2_PIN PC6
#define LED_GREEN_LOCK_3_PIN PC5

// Define BTN - PIN´s on Nucleo F401RE
#define BTN_1_PIN PC0
#define BTN_2_PIN PC1
#define BTN_3_PIN PB0
#define BTN_4_PIN PA4

// Declare prototypes
void led_setup();
void button_setup();
void check_buttons();
void check_states();

void setup()
{
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize PIN setup
  led_setup();
  button_setup();
  keypad_setup_pins();
}

void loop()
{
  check_buttons();
  check_states();
}

// Function for LED - PIN setup
void led_setup()
{
  // Define all leds as output
  pinMode(LED_RED_LOCKED_PIN, OUTPUT);
  pinMode(LED_GREEN_LOCK_1_PIN, OUTPUT);
  pinMode(LED_GREEN_LOCK_2_PIN, OUTPUT);
  pinMode(LED_GREEN_LOCK_3_PIN, OUTPUT);
}

// Function for BTN - PIN setup
void button_setup()
{
  // Define all buttons as input. PULLUPs are used external
  pinMode(BTN_1_PIN, INPUT);
  pinMode(BTN_2_PIN, INPUT);
  pinMode(BTN_3_PIN, INPUT);
  pinMode(BTN_4_PIN, INPUT);
}

// Function for the test program with LED´s and BTN´s
void check_buttons()
{
  if (LOW == digitalRead(BTN_1_PIN))
  {
    state_machine(INPUT_1_ACCEPTED);
  }

  if (LOW == digitalRead(BTN_2_PIN))
  {
    state_machine(INPUT_2_ACCEPTED);
  }

  if (LOW == digitalRead(BTN_3_PIN))
  {
    state_machine(INPUT_3_ACCEPTED);
  }

  if (LOW == digitalRead(BTN_4_PIN))
  {
    state_machine(INPUT_REFUSED);
    state_machine(OPEN_DOOR);
    state_machine(CLOSE_DOOR);
  }
}

// Function to put LED states HIGH or LOW
void check_states()
{
  switch (state)
  {
  case SAFE_LOCKED:
    digitalWrite(LED_RED_LOCKED_PIN, HIGH);
    digitalWrite(LED_GREEN_LOCK_1_PIN, LOW);
    digitalWrite(LED_GREEN_LOCK_2_PIN, LOW);
    digitalWrite(LED_GREEN_LOCK_3_PIN, LOW);
    break;
  case LEVEL_1_UNLOCKED:
    digitalWrite(LED_RED_LOCKED_PIN, LOW);
    digitalWrite(LED_GREEN_LOCK_1_PIN, HIGH);
    digitalWrite(LED_GREEN_LOCK_2_PIN, LOW);
    digitalWrite(LED_GREEN_LOCK_3_PIN, LOW);
    
    if (char key = get_key())
    {
      Serial.printf("Key: %c \n", key);
    }
    break;
  case LEVEL_2_UNLOCKED:
    digitalWrite(LED_RED_LOCKED_PIN, LOW);
    digitalWrite(LED_GREEN_LOCK_1_PIN, HIGH);
    digitalWrite(LED_GREEN_LOCK_2_PIN, HIGH);
    digitalWrite(LED_GREEN_LOCK_3_PIN, LOW);
    break;
  case LEVEL_3_UNLOCKED:
    digitalWrite(LED_RED_LOCKED_PIN, LOW);
    digitalWrite(LED_GREEN_LOCK_1_PIN, HIGH);
    digitalWrite(LED_GREEN_LOCK_2_PIN, HIGH);
    digitalWrite(LED_GREEN_LOCK_3_PIN, HIGH);
    break;
  default:
    break;
  }
}