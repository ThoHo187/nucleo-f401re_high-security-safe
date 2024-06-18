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

// Define external interrupt PIN´s
#define RE_PIN_A PC10
#define RE_PIN_B PC12

// Declare prototypes
void led_setup();
void button_setup();
void interrupt_setup();
void isr_re();
void check_buttons();
void check_states();


// Variablenübergabe an globale Variable
volatile int32_t counter = 0;


void setup()
{
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize PIN setup
  led_setup();
  button_setup();
  interrupt_setup();
  keypad_setup_pins();
}

void loop()
{
  check_buttons();
  check_states();
  
  Serial.printf("Counter: %dc\n", counter);
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
  // Define all buttons as input
  pinMode(BTN_1_PIN, INPUT_PULLUP);
  pinMode(BTN_2_PIN, INPUT_PULLUP);
  pinMode(BTN_3_PIN, INPUT_PULLUP);
  pinMode(BTN_4_PIN, INPUT_PULLUP);
}

// Function for interrupt setup
void interrupt_setup()
{
    pinMode(RE_PIN_A, INPUT_PULLUP);
    pinMode(RE_PIN_B, INPUT_PULLUP);

    // Attach interrupt to PIN_A, triggering on RISING edge
    attachInterrupt(RE_PIN_A, isr_re, RISING);
}

// Function for interrupt service routine (ISR) for PIN_A
void isr_re()
{
    // Determine the direction based on the state of PIN_B
    if (digitalRead(RE_PIN_B) == HIGH)
    {
        // counter clockwise (Gegen Uhrzeigersinn)
        counter--;
    }
    else
    {
        // clockwise (Im Uhrzeigersinn)
        counter++;
    }
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