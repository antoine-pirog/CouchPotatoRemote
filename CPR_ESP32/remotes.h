#ifndef REMOTES_H
#define REMOTES_H

#include <cstdint>
#include <WiFi.h>

// IRCommand : full IR command packet
struct IrCommand {
    uint16_t address;      // 16-bit device address (which remote/device)
    uint8_t  command;      // 8-bit command code (button pressed)
};

// Base class for all remotes
class RemoteNEC {
protected:
    uint16_t address_;     // The IR address for this specific remote (accessible inside class, inside derived classes, inaccessible by others)

public:
    // Constructor
    explicit RemoteNEC(uint16_t addr) : address_(addr){} // Prevent accidental implicit conversions
        
    // Destructor
    virtual ~RemoteNEC() = default;

    // Virtual function to build an IR command
    virtual IrCommand buildCommand(uint8_t cmd) const { return { address_, cmd }; }

    virtual void serve_page(WiFiClient &client) = 0;
    virtual void transmit_cmdstr(const String& cmdstr) = 0;
    virtual int handle_requests(const String& request, WiFiClient& client) = 0;
};

#endif