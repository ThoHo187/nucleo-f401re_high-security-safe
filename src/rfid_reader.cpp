#include "rfid_reader.h"
#include "pin_defs.h"
#include "state_machine.h"

// RFID-Setup
MFRC522 rfid(SS_PIN, RST_PIN);

// Zulässige UIDs (Beispiel-UIDs, passe sie nach Bedarf an)
const byte allowedUIDs[][4] = {
    {0x37, 0xCB, 0x52, 0xB4}, // UID der Karte
    {0xCA, 0x8B, 0x8F, 0x81}  // UID des Chips
};
const int numAllowedUIDs = sizeof(allowedUIDs) / sizeof(allowedUIDs[0]);

void rfid_reader_setup()
{
    SPI.begin();
    rfid.PCD_Init();
}

void check_rfid()
{
    if (!rfid.PICC_IsNewCardPresent()) {
        return;  // Keine neue Karte vorhanden
    }

    if (!rfid.PICC_ReadCardSerial()) {
        return;  // Karte nicht gelesen
    }

    // UID der Karte anzeigen
    Serial.print("UID: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();

    // UID überprüfen
    bool uidAuthorized = false;
    for (int i = 0; i < numAllowedUIDs; i++) {
        if (memcmp(rfid.uid.uidByte, allowedUIDs[i], 4) == 0) {
            uidAuthorized = true;
            break;
        }
    }

    if (uidAuthorized) {
        Serial.println("Authorized UID detected.");
        state_machine(INPUT_3_ACCEPTED);
    } else {
        Serial.println("Unauthorized UID detected.");
        digitalWrite(BUZZER_PIN, HIGH);           // Buzzer einschalten
        delay(1500);                              // Buzzer während delay aktiv halten
        digitalWrite(BUZZER_PIN, LOW);            // Buzzer ausschalten
        state_machine(INPUT_REFUSED);
    }

    // Karte deaktivieren
    rfid.PICC_HaltA();

}
