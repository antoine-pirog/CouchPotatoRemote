#include <IRremote.h>
#include <cstdint>
#include "irUtils.h"
#include "remotes.h"

/* RECEIVER */
#define RX_DATA_PIN 14
#define RX_VDD_PIN  12
#define RX_GND_PIN  13

/* EMITTER */
#define TX_DATA_PIN 4

#define REPEATS 1

/* Globals */
IRrecv irrecv (RX_DATA_PIN);
decode_results results;

void irReceiver_init(void){  
    /* IR Receiver initialization */
    pinMode(RX_DATA_PIN, INPUT);
    pinMode(RX_VDD_PIN, OUTPUT);
    pinMode(RX_GND_PIN, OUTPUT);
    
    digitalWrite(RX_VDD_PIN, HIGH);
    digitalWrite(RX_GND_PIN, LOW);
    
    irrecv.enableIRIn ();
}

void irReceiver_handler(void){
    if (IrReceiver.decode()) {
        Serial.print("Raw data : ");
        Serial.println (IrReceiver.decodedIRData.decodedRawData, HEX);
        Serial.println("All fields : ");
        IrReceiver.printIRResultShort(&Serial);
        Serial.println("Raw timing data : ");
        IrReceiver.printIRResultRawFormatted(&Serial, true);
        Serial.println("Usage : ");
        IrReceiver.printIRSendUsage(&Serial);
        Serial.println("---------------");
        irrecv.resume ();
    }
}


IRsend irsend(TX_DATA_PIN);

void irTransmitter_init(void){  
    /* IR Transmitter initialization */
    pinMode(TX_DATA_PIN, OUTPUT);
}

void transmit(IrCommand cmd){
    irsend.sendNEC(cmd.address, cmd.command, REPEATS);
    Serial.print("Transmitted : @0x");
    Serial.print(cmd.address, HEX);
    Serial.print(" - 0x");
    Serial.println(cmd.command, HEX);
}