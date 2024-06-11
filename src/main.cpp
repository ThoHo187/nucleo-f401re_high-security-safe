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


// Define PIN´s for the rows on Nucleo F401RE
#define ROW1 PA12
#define ROW2 PC5
#define ROW3 PC6
#define ROW4 PC8


// Define PIN´s for the cols on Nucleo F401RE
#define COL1 PC0
#define COL2 PC1
#define COL3 PC2
#define COL4 PC3


// Define the key values in a two-dimensional array
char keys[4][4] = 
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


// Declare prototypes
void pinSetup();
void pinKeypad();
void checkBTNs();
void checkStates();
char read_keys();


void setup()
{
    // Initialize PIN setup
    pinSetup();
    pinKeypad();
}


void loop()
{
    checkBTNs();
    checkStates();

    char key = read_keys(); // Lese die gedrückte Taste
    if (key != 0) {
        // Hier kannst du die erkannte Taste verarbeiten
        Serial.print("Taste gedrückt: ");
        Serial.println(key);
    }
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


// Function for Pin Setup on Keybad
void pinKeypad()
{
// Initialize row pins as input with pull-up resistors
  pinMode(ROW1, INPUT_PULLUP);
  pinMode(ROW2, INPUT_PULLUP);
  pinMode(ROW3, INPUT_PULLUP);
  pinMode(ROW4, INPUT_PULLUP);

  // Initialize column pins as output
  pinMode(COL1, OUTPUT);
  pinMode(COL2, OUTPUT);
  pinMode(COL3, OUTPUT);
  pinMode(COL4, OUTPUT);

  // Set all column pins HIGH
  digitalWrite(COL1, HIGH);
  digitalWrite(COL2, HIGH);
  digitalWrite(COL3, HIGH);
  digitalWrite(COL4, HIGH);
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


// Function to implement the algorithm of the Keypad
char read_keys()
{
    // Erste Spalte auf LOW setzen
    digitalWrite(COL1, LOW);
    if (digitalRead(ROW1) == LOW) 
    {
        digitalWrite(COL1, HIGH);
        return keys[0][0];
    } else if (digitalRead(ROW2) == LOW) 
    {
        digitalWrite(COL1, HIGH);
        return keys[1][0];
    } else if (digitalRead(ROW3) == LOW) 
    {
        digitalWrite(COL1, HIGH);
        return keys[2][0];
    } else if (digitalRead(ROW4) == LOW) 
    {
        digitalWrite(COL1, HIGH);
        return keys[3][0];
    }
    digitalWrite(COL1, HIGH);

    // Zweite Spalte auf LOW setzen
    digitalWrite(COL2, LOW);
    if (digitalRead(ROW1) == LOW) 
    {
        digitalWrite(COL2, HIGH);
        return keys[0][1];
    } else if (digitalRead(ROW2) == LOW) 
    {
        digitalWrite(COL2, HIGH);
        return keys[1][1];
    } else if (digitalRead(ROW3) == LOW) 
    {
        digitalWrite(COL2, HIGH);
        return keys[2][1];
    } else if (digitalRead(ROW4) == LOW) 
    {
        digitalWrite(COL2, HIGH);
        return keys[3][1];
    }
    digitalWrite(COL2, HIGH);

    // Dritte Spalte auf LOW setzen
    digitalWrite(COL3, LOW);
    if (digitalRead(ROW1) == LOW) 
    {
        digitalWrite(COL3, HIGH);
        return keys[0][2];
    } else if (digitalRead(ROW2) == LOW) 
    {
        digitalWrite(COL3, HIGH);
        return keys[1][2];
    } else if (digitalRead(ROW3) == LOW) 
    {
        digitalWrite(COL3, HIGH);
        return keys[2][2];
    } else if (digitalRead(ROW4) == LOW) 
    {
        digitalWrite(COL3, HIGH);
        return keys[3][2];
    }
    digitalWrite(COL3, HIGH);

    // Vierte Spalte auf LOW setzen
    digitalWrite(COL4, LOW);
    if (digitalRead(ROW1) == LOW) 
    {
        digitalWrite(COL4, HIGH);
        return keys[0][3];
    } else if (digitalRead(ROW2) == LOW) 
    {
        digitalWrite(COL4, HIGH);
        return keys[1][3];
    } else if (digitalRead(ROW3) == LOW) 
    {
        digitalWrite(COL4, HIGH);
        return keys[2][3];
    } else if (digitalRead(ROW4) == LOW) 
    {
        digitalWrite(COL4, HIGH);
        return keys[3][3];
    }
    digitalWrite(COL4, HIGH);

    // Wenn keine Taste gedrückt ist, gib einen speziellen Wert zurück, z.B. 0
    return 0;
}

