#include <WiFi.h>
#include <cstdint>
#include "remote_xanlite_rgb.h"
#include "remote_xanlite_rgb_webui.h"
#include "irUtils.h"

void XanliteRgbRemote::serve_page(WiFiClient& client){
    client.printf(xanlite_rgb_webui);
}

void XanliteRgbRemote::transmit_cmdstr(const String& cmdstr){
    using Cmd = XanliteRgbRemote::Command; 
    Cmd cmd;

    if      (cmdstr == "ON"        ) cmd = Cmd::ON;
    else if (cmdstr == "OFF"       ) cmd = Cmd::OFF;
    else if (cmdstr == "BRIGHTER"  ) cmd = Cmd::BRIGHTER;
    else if (cmdstr == "DIMMER"    ) cmd = Cmd::DIMMER;
    else if (cmdstr == "FLASH"     ) cmd = Cmd::FLASH;
    else if (cmdstr == "STROBE"    ) cmd = Cmd::STROBE;
    else if (cmdstr == "FADE"      ) cmd = Cmd::FADE;
    else if (cmdstr == "SMOOTH"    ) cmd = Cmd::SMOOTH;
    else if (cmdstr == "RED"       ) cmd = Cmd::RED;
    else if (cmdstr == "GREEN"     ) cmd = Cmd::GREEN;
    else if (cmdstr == "WHITE"     ) cmd = Cmd::WHITE;
    else if (cmdstr == "BLUE"      ) cmd = Cmd::BLUE;
    else if (cmdstr == "ORANGE"    ) cmd = Cmd::ORANGE;
    else if (cmdstr == "TEAL"      ) cmd = Cmd::TEAL;
    else if (cmdstr == "INDIGO"    ) cmd = Cmd::INDIGO;
    else if (cmdstr == "YELLOW"    ) cmd = Cmd::YELLOW;
    else if (cmdstr == "CYAN"      ) cmd = Cmd::CYAN;
    else if (cmdstr == "LAVENDER"  ) cmd = Cmd::LAVENDER;
    else if (cmdstr == "LIME"      ) cmd = Cmd::LIME;
    else if (cmdstr == "SKYBLUE"   ) cmd = Cmd::SKYBLUE;
    else if (cmdstr == "PURPLE"    ) cmd = Cmd::PURPLE;
    else if (cmdstr == "LIGHTGREEN") cmd = Cmd::LIGHTGREEN;
    else if (cmdstr == "LIGHTBLUE" ) cmd = Cmd::LIGHTBLUE;
    else if (cmdstr == "MAGENTA"   ) cmd = Cmd::MAGENTA;
    else return;

    transmitNEC(build(cmd));
}

int XanliteRgbRemote::handle_requests(const String& request, WiFiClient& client){
    if (request.indexOf("GET /remote-xanlite-rgb?cmd=") >= 0) {

        int cmdIndex = request.indexOf("cmd=") + 4;
        int endIndex = request.indexOf(" ", cmdIndex);

        String cmdstr = request.substring(cmdIndex, endIndex);

        transmit_cmdstr(cmdstr);

        // Send simple JSON response
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: application/json");
        client.println("Connection: close");
        client.println();
        client.println("{\"status\":\"ok\"}");
        return 1;
    }
    else if (request.indexOf("GET /remote-xanlite-rgb") >= 0) {
        serve_page(client);
        return 1;
    }
    return 0;
}
