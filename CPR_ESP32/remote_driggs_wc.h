#ifndef DRIGGS_WC_H
#define DRIGGS_WC_H

#include "remotes.h"

class DriggsWcRemote : public Remote {
public:
    enum class Command : uint8_t {
        ON            = 0x61,
        OFF           = 0xA1,
        BRIGHTER      = 0x41,
        DIMMER        = 0x21,
        COLOR_COLD    = 0xC1,
        COLOR_NEUTRAL = 0x81,
        COLOR_WARM    = 0x08
    };

    DriggsWcRemote()
        : Remote(0x0000) {}

    IrCommand build(Command cmd) const {
        return buildCommand(static_cast<uint8_t>(cmd));
    }

    void serve_page(WiFiClient &client) override;
    void transmit_cmdstr(const String& cmdstr) override;
    int handle_requests(const String& request, WiFiClient& client) override;
};

#endif