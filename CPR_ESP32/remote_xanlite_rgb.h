#ifndef XANLITERGB_H
#define XANLITERGB_H

#include "remotes.h"

class XanliteRgbRemote : public RemoteNEC {
public:
    enum class Command : uint8_t {
        ON          = 0x03,
        OFF         = 0x02,
        BRIGHTER    = 0x00,
        DIMMER      = 0x01,
        FLASH       = 0x0B,
        STROBE      = 0x0F,
        FADE        = 0x13,
        SMOOTH      = 0x17,

        RED         = 0x04,
        GREEN       = 0x05,
        WHITE       = 0x07,
        BLUE        = 0x06,
        ORANGE      = 0x08,
        TEAL        = 0x09,
        INDIGO      = 0x0A,
        YELLOW      = 0x0C,
        CYAN        = 0x0D,
        LAVENDER    = 0x0E,
        LIME        = 0x10,
        SKYBLUE     = 0x11,
        PURPLE      = 0x12,
        LIGHTGREEN  = 0x14,
        LIGHTBLUE   = 0x15,
        MAGENTA     = 0x16
    };

    XanliteRgbRemote()
        : RemoteNEC(0xEF00) {}

    IrCommand build(Command cmd) const {
        return buildCommand(static_cast<uint8_t>(cmd));
    }

    void serve_page(WiFiClient &client) override;
    void transmit_cmdstr(const String& cmdstr) override;
    int handle_requests(const String& request, WiFiClient& client) override;
};

#endif