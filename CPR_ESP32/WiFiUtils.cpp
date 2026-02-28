#include <WiFi.h>
#include "WiFiUtils.h"
#include "secret.h"
#include "remote_xanlite_rgb.h"
#include "remote_driggs_wc.h"
#include "index_webui.h"
#include "context.h"

WiFiServer server(80); // Set web server port number to 80  
String header; // Variable to store the HTTP request
String output26State = "off"; // Auxiliar variable to store the current output state
String output27State = "off"; // Auxiliar variable to store the current output state
unsigned long currentTime = millis(); // Current time
unsigned long previousTime = 0; // Previous time
const long timeoutTime = 2000; // Define timeout time in milliseconds (example: 2000ms = 2s)

XanliteRgbRemote xanlite_rgb_remote;
DriggsWcRemote driggs_wc_remote;

void WiFi_init(void){
    /* WiFi server initialization */
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
}

void handle_requests(const String& request, WiFiClient& client) {
    if      (xanlite_rgb_remote.handle_requests(request, client)){}
    else if (driggs_wc_remote.handle_requests(request, client)){}
    else if (request.indexOf("GET /recvir") >= 0) {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/plain");
        client.println("Connection: close");
        client.println();
        client.println(last_ir_command);
        }
    else {
        // Serve main page
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();
        client.printf("%s", index_webui); // index_webui defined in index_webui.h
    }
}

void WiFiClient_handler(void){
    WiFiClient client = server.available();     // Listen for incoming clients
    if (client) {
        while (!client.available()) {
        delay(1);
    }

    String request = client.readStringUntil('\r');
    client.readStringUntil('\n'); // consume newline

    handle_requests(request, client);

    delay(1);
    client.stop();
    }
}