#ifndef RFID_READER_H
#define RFID_READER_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

void rfid_reader_setup();
void check_rfid();

#endif // RFID_READER_H
