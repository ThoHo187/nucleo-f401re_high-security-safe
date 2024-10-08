#include <Arduino.h>
#include "state_machine.h"
#include "keypad.h"
#include "rotary_encoder.h"
#include "pin_defs.h"
#include "rfid_reader.h"  

void led_setup();
void button_setup();
void check_buttons();
void check_states();

void setup()
{
    led_setup();
    button_setup();
    setup_encoder(RE_PIN_A, RE_PIN_B, RE_SW);
    keypad_setup_pins();
    rfid_reader_setup();  // RFID-Reader initialisieren
    Serial.begin(9600);
}

int32_t last_encoder_state = 0;

void loop()
{
    check_buttons();
    check_states();
    check_rfid();  // RFID-Überprüfung ausführen

    if (Serial.available()) {
        uint8_t buf = Serial.read();
        if (buf == '1') {
            state_machine(INPUT_1_ACCEPTED);
        }
        if (buf == '2') {
            state_machine(INPUT_2_ACCEPTED);
        }
        if (buf == '3') {
            state_machine(INPUT_REFUSED);
        }
    }

    int32_t encoder_state = get_encoder_state();
    if (encoder_state != last_encoder_state) {
        Serial.printf("Encoder state: %d \n", encoder_state);
        last_encoder_state = encoder_state;
    }
}

void led_setup()
{
    // Define all LEDs as output
    pinMode(LED_RED_LOCKED_PIN, OUTPUT);
    pinMode(LED_GREEN_LOCK_1_PIN, OUTPUT);
    pinMode(LED_GREEN_LOCK_2_PIN, OUTPUT);
    pinMode(LED_GREEN_LOCK_3_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT); // Buzzer als Ausgang festlegen
}

void button_setup()
{
    // Define all buttons as input with internal pull-ups
    pinMode(BTN_1_PIN, INPUT_PULLUP);
    pinMode(BTN_2_PIN, INPUT_PULLUP);
    pinMode(BTN_3_PIN, INPUT_PULLUP);
    pinMode(BTN_4_PIN, INPUT_PULLUP);
}

void check_buttons()
{
    if (LOW == digitalRead(BTN_1_PIN)) {
        state_machine(INPUT_1_ACCEPTED);
    }

    if (LOW == digitalRead(BTN_2_PIN)) {
        state_machine(INPUT_2_ACCEPTED);
    }

    if (LOW == digitalRead(BTN_3_PIN)) {
        state_machine(INPUT_3_ACCEPTED);
    }

    if (LOW == digitalRead(BTN_4_PIN)) {
        state_machine(INPUT_REFUSED);
        state_machine(OPEN_DOOR);
        state_machine(CLOSE_DOOR);
    }
}

void check_states()
{
    switch (state) {
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

        if (char key = get_key()) {
            Serial.printf("Keypad Key: %c \n", key);
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
