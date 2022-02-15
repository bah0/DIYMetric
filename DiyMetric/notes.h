/*Info:
 * #define WIFI_LED 16 -> D0 GPIO16 <- LED on the MCU Board
 * #define WIFI_LED 2 -> D4 GPIO2 <- LED on the MCU Board
 * the onboard leds are inverted, low means the led will light up and low means the led will be turned off
 * 
 * Fonts
 * http://oleddisplay.squix.ch/ 
 * or
 * https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts
 * and
 * https://github.com/adafruit/Adafruit-GFX-Library
 * maybe
 * https://maxpromer.github.io/LCD-Character-Creator/
 * https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives
 * https://learn.adafruit.com/adafruit-gfx-graphics-library/loading-images
 * https://learn.adafruit.com/adafruit-2-8-tft-touch-shield-v2/drawing-bitmaps
 * 
 * timer
 * https://www.arduino.cc/reference/de/language/functions/time/millis/
 * 
 * bmp decoder
 * https://github.com/Bodmer/JPEGDecoder
 * https://github.com/MakotoKurauchi/JPEGDecoder
 * 
 * 
 * https://developer.lametric.com/
 * https://lametric-documentation.readthedocs.io/en/latest/reference-docs/device-display.html
 * https://lametric-documentation.readthedocs.io/en/latest/guides/first-steps/first-lametric-indicator-app.html
 * https://readthedocs.org/projects/lametric-documentation/downloads/pdf/latest/
 * https://developer.lametric.com/icons
 * https://lametric-documentation.readthedocs.io/en/latest/reference-docs/cloud-icons.html
 * 
 * https://github.com/lecram/gifdec
 * https://forum.arduino.cc/index.php?topic=448038.0
 * https://blog.squix.org/2017/01/esp8266-planespotter-color.html
 * 
 * 
 * PNG Specification
 * https://en.wikipedia.org/wiki/Portable_Network_Graphics
 * http://www.libpng.org/pub/png/book/chapter11.html#png.ch11.div.8
 * 
 * tinf + upng <- png support
 * https://github.com/jibsen/tinf
 * https://help.lametric.com/support/solutions/articles/6000225467-my-data-diy
 * https://techtutorialsx.com/2017/01/21/esp8266-watchdog-functions/
 * https://github.com/Makuna/Task
 * 
 * https://techtutorialsx.com/2018/06/08/esp8266-arduino-getting-http-response-headers/
 * https://techtutorialsx.com/2016/07/17/esp8266-http-get-requests/
 * https://www.arduino.cc/reference/de/language/functions/communication/stream/streamreadbytes/
 * https://github.com/esp8266/Arduino/tree/master/libraries
 * https://www.geeksforgeeks.org/size_t-data-type-c-language/
 * https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPClient/examples/BasicHttpClient/BasicHttpClient.ino
 * https://links2004.github.io/Arduino/dd/d8d/class_h_t_t_p_client.html#aa959e4da0c99a63486e2689f8bd900cf
 * https://stackoverflow.com/questions/10060098/getting-only-response-header-from-http-post-using-curl
 * https://www.az-delivery.de/blogs/azdelivery-blog-fur-arduino-und-raspberry-pi/esp8266-spiffs-dateisystem
 * http://david.tribble.com/text/cdiffs.htm#C99-char-literal
 * https://www.arduino.cc/reference/en/language/functions/communication/stream/
 * https://learn.adafruit.com/adafruit-neopixel-uberguide/neomatrix-library
 * https://learn.adafruit.com/memories-of-an-arduino/solving-memory-problems
 * http://www.c-howto.de/tutorial/arrays-felder/speicherverwaltung/
 * https://en.wikipedia.org/wiki/Bitwise_operation#Bit_shifts
 * 
 */
