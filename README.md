Adalight WS2812
===============

This is a fork of Adalight working with WS2811/WS2812 LED using the FastLED library (v 3.1).

FastLED library can be found on Github here : https://github.com/FastLED/FastLED

## What you need
- An Arduino Nano (genuine or not).
- A 1000µF (or more) electrolytic capacitor.
- A resistance between 200 and 600 Ohms.
- WS2812B RGB LED strip (max 240 LEDs) I recommend a strip with 60 LEDs/meter.
- A 5v power supply. To calculate the required current do: 0.06A × `NUM_LEDS`.
- A soldering iron and cables **or** Dupont wires and 3 lines LED strip edge connector.
- Solderless breadboard **or** proto-board (if you want to do a welded version).
- Prismatik (Linux, Windows, Mac): https://github.com/psieg/Lightpack/releases

## The circuit
![image](https://user-images.githubusercontent.com/57588282/112463052-12ffd680-8d62-11eb-84cc-00eae1426d71.png)
