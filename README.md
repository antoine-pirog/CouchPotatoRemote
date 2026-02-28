# Couch Potato Remote

**CouchPotatoRemote** is an ESP32-based WiFi infrared remote control. 
Because I keep losing my remotes. And when I do find them, their batteries are dead anyway.

The ESP32 acts as a small HTTP server and serves web-based remote control interfaces.  
Each remote has its own page and command handler.

## Features

- Web UIs served directly from ESP32 :
  - Hub page to supported remotes
  - Remote UIs
- Modular remote architecture
- IR transmit (currently using NEC protocol)
- Helpers for new remote definition :
  - Live display of last received IR command (`/recvir` endpoint)

## Hardware

* Uses a ESP32 WROOM Devkit rev2
* IR emitter : 850nm IR LED
  * `TX_DATA_PIN` :  4
  * Driven with a 2n2222 transistor with 150R current limiting resistor
* IR receiver : KY-022 module
  * `RX_DATA_PIN` : 14
  * `RX_VDD_PIN` : 12
  * `RX_GND_PIN` : 13

## Project structure

The project structure is admittedly kind of flat because the Arduino IDE is restrictive in terms of subfolder structure ...

```
📦CouchPotatoRemote
 ┣ 📂CPR_ESP32
 ┃ ┃ ℹ️ ### Embedded sources ###
 ┃ ┣ 📜CPR_ESP32.ino                # Main .ino project file
 ┃ ┣ 📜context.cpp                  # Shared variables
 ┃ ┣ 📜context.h                    #
 ┃ ┣ 📜remotes.h                    # Remote base structures
 ┃ ┣ 📜irUtils.cpp                  # IR receive/transmit utils
 ┃ ┣ 📜irUtils.h                    #
 ┃ ┣ 📜WiFiUtils.cpp                # HTTP server + routing
 ┃ ┣ 📜WiFiUtils.h                  #
 ┃ ┣ 📜secret.h                     # WiFi SSID + password
 ┃ ┃ ℹ️ ### Webui index page ###
 ┃ ┣ 📜index.html                   # Base index web sources
 ┃ ┣ 📜index_webui.h                # Generated index web sources
 ┃ ┣ 📜index_webui.json             # Definition of .html -> .h generation settings
 ┃ ┃ ℹ️ ### Remotes ###
 ┃ ┣ 📜remote_xanlite_rgb.cpp       # Remote class definition (inherited from remotes.h)
 ┃ ┣ 📜remote_xanlite_rgb.h         # Generated webui remote sources
 ┃ ┣ 📜remote_xanlite_rgb.html      # Base webui remote sources
 ┃ ┣ 📜remote_xanlite_rgb.json      # Definition of .html -> .h generation settings of remote webui
 ┃ ┗ 📜remote_xanlite_rgb_webui.h   # Generate remote webui
 ┃ ℹ️ ### Helper scripts ###
 ┣ 📜generate_webui_pages.py        # .h webui sources generation script
 ┃ ℹ️ ### README ###
 ┗ 📜README.md                      #
```

## Remote webuis & index page

Html pages for the browser UI are included as `.html` files alongside the `.ino`, `.cpp`, and `.h` sources, but they **must be be packed into the embedded sources before compiling them**. To that end, the `generate_webui_pages.py` script will seek webui files and programatically generate the required `.h` files. To properly integrate new html files to the project, they must include:

- A `.json` file that describes `.h` file generation settings
- A html file that will be served by the ESP32

For example :

In `my_new_webui.json` :
```json
{
    "webui" : {
        "filename_html"   : "my_new_webui.html",        // input path to the html file to convert
        "filename_h"      : "my_new_webui.h",           // output path to the generated header file 
        "htmlstring_name" : "my_new_webui_html_string", // name of the constant containing the html code to serve
        "h_guard_block"   : "MY_NEW_WEBUI_H"            // guard block used in the generated header file
    }
}
```

In `my_new_webui.html` :
```html
<html>
	<head>
		<!-- my new webui information -->
        <!-- my new webui css -->
        <!-- my new webui js -->
	</head>
	<body>
		<!-- my new webui body html -->	
	</body>
</html>
```

The, run the `.h` file generation script :
```shell
python ./generate_webui_pages.py
```
```
Generating h file for ./CPR_ESP32/index_webui.json ...
Generating h file for ./CPR_ESP32/my_new_webui.json ...
Generating h file for ./CPR_ESP32/remote_xanlite_rgb.json ...
All done.
```

Contents of generated `my_new_webui.h` file :

```h
#ifndef MY_NEW_WEBUI_H
#define MY_NEW_WEBUI_H
const char* my_new_webui_html_string = "<html>\n<head>\n<!-- my new webui information -->\n<!-- my new webui css -->\n<!-- my new webui js -->\n</head>\n<body>\n<!-- my new webui body html -->\n</body>\n</html>";
#endif
``` 

## Dependencies

### Arduino libraries

* Must use ESP32 by Espressif v2.0.17
* Must use IRremote library v3.9.0