#include <WiFi.h>
#include <cstdint>
#include "remote_driggs_wc.h"
#include "remote_driggs_wc_webui.h"
#include "irUtils.h"

void DriggsWcRemote::serve_page(WiFiClient& client){
    client.printf(driggs_wc_webui);
}

void DriggsWcRemote::transmit_cmdstr(const String& cmdstr){
    using Cmd = DriggsWcRemote::Command; 
    Cmd cmd;

    if      (cmdstr == "ON"          ) cmd = Cmd::ON;
    else if (cmdstr == "OFF"         ) cmd = Cmd::OFF;
    else if (cmdstr == "BRIGHTER"    ) cmd = Cmd::BRIGHTER;
    else if (cmdstr == "DIMMER"      ) cmd = Cmd::DIMMER;
    else if (cmdstr == "COLOR_BLUE"  ) cmd = Cmd::COLOR_BLUE;
    else if (cmdstr == "COLOR_YELLOW") cmd = Cmd::COLOR_YELLOW;
    else if (cmdstr == "COLOR_WHITE" ) cmd = Cmd::COLOR_WHITE;
    else return;

    transmit(build(cmd));
}

int DriggsWcRemote::handle_requests(const String& request, WiFiClient& client){
    if (request.indexOf("GET /remote-driggs-wc?cmd=") >= 0) {

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
    else if (request.indexOf("GET /remote-driggs-wc") >= 0) {
        serve_page(client);
        return 1;
    }
    return 0;
}
