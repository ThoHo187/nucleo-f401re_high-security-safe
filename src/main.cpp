#include <Arduino.h>
#include "state_machine.h"


// Define BTN -  PIN´s on Nucleo F401RE
#define btn1Pin PA5
#define btn2Pin PA6
#define btn3Pin PA7
#define btn4Pin PA8


// Define LED - PIN´s on Nucleo F401RE
#define ledRedPin PB12   // LED indicating SAFE_LOCKED
#define led1Pin PB13     // LED indicating LEVEL_1_UNLOCKED
#define led2Pin PB14     // LED indicating LEVEL_2_UNLOCKED
#define led3Pin PB15     // LED indicating LEVEL_3_UNLOCKED


// Declare prototypes
void pinSetup();
void checkBTNs();
void checkStates();


void setup()
{
    // Initialize PIN setup
    pinSetup();
}


void loop()
{
    checkBTNs();
    checkStates();
}


// Function for PIN Setup
void pinSetup()
{
    // Initialize button pins
    pinMode(btn1Pin, INPUT_PULLUP);
    pinMode(btn2Pin, INPUT_PULLUP);
    pinMode(btn3Pin, INPUT_PULLUP);
    pinMode(btn4Pin, INPUT_PULLUP);

    // Initialize LED pins
    pinMode(ledRedPin, OUTPUT);
    pinMode(led1Pin, OUTPUT);
    pinMode(led2Pin, OUTPUT);
    pinMode(led3Pin, OUTPUT);

    // Ensure all LEDs are initially off
    digitalWrite(ledRedPin, LOW);
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
}


// Function for the test program with LED´s and BTN´s
void checkBTNs()
{
    if (digitalRead(btn1Pin) == LOW) 
    {
    state_machine(INPUT_1_ACCEPTED);
    delay(200); // Debounce delay
    } 
    else if (digitalRead(btn2Pin) == LOW) 
    {
    state_machine(INPUT_2_ACCEPTED);
    delay(200); // Debounce delay
    } 
    else if (digitalRead(btn3Pin) == LOW) 
    {
    state_machine(INPUT_3_ACCEPTED);
    delay(200); // Debounce delay
    } 
    else if (digitalRead(btn4Pin) == LOW) 
    {
    state_machine(INPUT_REFUSED);
    delay(200); // Debounce delay
    }
}


// Function to put LED states HIGH or LOW
void checkStates()
{
    switch(state)
    {
    case SAFE_LOCKED:
        digitalWrite(ledRedPin, HIGH);
        digitalWrite(led1Pin, LOW);
        digitalWrite(led2Pin, LOW);
        digitalWrite(led3Pin, LOW);
        break;
    case LEVEL_1_UNLOCKED:
        digitalWrite(ledRedPin, LOW);
        digitalWrite(led1Pin, HIGH);
        digitalWrite(led2Pin, LOW);
        digitalWrite(led3Pin, LOW);
        break;
    case LEVEL_2_UNLOCKED:
        digitalWrite(ledRedPin, LOW);
        digitalWrite(led1Pin, HIGH);
        digitalWrite(led2Pin, HIGH);
        digitalWrite(led3Pin, LOW);
        break;
    case LEVEL_3_UNLOCKED:
        digitalWrite(ledRedPin, LOW);
        digitalWrite(led1Pin, HIGH);
        digitalWrite(led2Pin, HIGH);
        digitalWrite(led3Pin, HIGH);
        break;
    default:
        break;
    }
}
