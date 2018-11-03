# Neopixel Room light controled by a ESP8266

## About
Use Neopixels to light up your room  
Control the LEDs with a ESP8266 over WiFi  
Some effects (rainbow, fire, ...) are available to be easily used  

## Features
- connects to Wifi and opens an UDP port
- controllable by sending json
- Several effects are predefined
- supports for Neopixel strips on different pins

## configuration
- copy config_example.h to config.h
- change settings in config.h
- use serial monitor to identify the IP (or check your DHCP server)
- send commands with netcat to your device

## examples
- echo "{effect:fire}" | nc -w 0 -u 192.168.x.x 2342
- echo "{effect:color,red:10,green:50,blue:100}" | nc -w 0 -u 192.168.x.x 2342
- echo "{effect:alert,red:255,green:1,blue:1,option1:10,option2:30}" | nc -w 0 -u 192.168.x.x 2342

## add your own new effects
- add your new function into effects.ino
- add a line to the runEffect function and the runEffectNumber function. Both in effects.ino
