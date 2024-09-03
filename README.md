# High security safe

This repo contains the all files for the high security safe project in my school lessons.


## Project description


## Hardware List
 - Nucleo-F401RE
 - 4x4 KeyPad
 - RFID-Reader
 - Some Buttons, LEDs, Resistors for testing

## Block diagramm
![Loading Block-Diagram](./assets/safeBlockDiagramm.png)

## State machine
![Loading State-Diagram](./assets/safeStateDiagramm.png)

## Teil - Projektanforderung

# Entsperrung mit einem RFID Chip

Es gelten folgende Anforderungen.
- Der RFID Chip ist die letzte Stufe der Entriegelung.
- Nur Chips mit bestimmten IDs sollen die Entsperrung zulassen.
- Wird ein falscher Chip vor den Leser gehalten soll dies mit einem Piepser signalisiert werden.