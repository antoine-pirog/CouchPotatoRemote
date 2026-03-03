/* RECEIVER */
#define RX_DATA_PIN 14
#define RX_VDD_PIN  12
#define RX_GND_PIN  13

/* EMITTER */
#define IR_SEND_PIN 4
#define REPEATS 1

/* INCLUSIONS */
#include <Arduino.h> 
#include <IRremote.hpp>
#include <cstdint>
#include "irUtils.h"
#include "remotes.h"
#include "context.h"

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
        // Exhaustive serial print
        Serial.print("Raw data : ");
        Serial.println (IrReceiver.decodedIRData.decodedRawData, HEX);
        Serial.println("All fields : ");
        IrReceiver.printIRResultShort(&Serial);
        Serial.println("Raw timing data : ");
        IrReceiver.printIRResultRawFormatted(&Serial, true);
        Serial.println("Usage : ");
        IrReceiver.printIRSendUsage(&Serial);
        Serial.println("---------------");
        // Summary string
        last_ir_command = "Protocol: " +
                          String(getProtocolString(IrReceiver.decodedIRData.protocol)) + "\n" +
                          "Address : 0x" +
                          String(IrReceiver.decodedIRData.address, HEX) + "\n" +
                          "Command : 0x" +
                          String(IrReceiver.decodedIRData.command, HEX);
        irrecv.resume ();
    }
}


void irTransmitter_init(void){  
    IrSender.begin();
}

void transmitNEC(IrCommand cmd){
    IrSender.sendNEC(cmd.address, cmd.command, REPEATS);
}