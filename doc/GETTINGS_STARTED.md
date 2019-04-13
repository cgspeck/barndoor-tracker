# Getting Started

## What?

Make toolchain for Arduino programming in C++ on the Espressif ESP32 (specifically the Adafruit Feather series).

## Why?

In order to:

* reuse the many, many pre-built and tested Arduino libraries that come with components, e.g. [Adafruit_ILI9341]
* have a project structure that makes sense to a professional software developer
* expose the C/C++ search paths so that IDEs/editors other then the Arduino one can be used
* have a build tool-chain that will allow any C/C++ library to be used
* allow the use of unit testing / [BDD] / mocking libraries

## How?

On a Ubuntu system run `./scripts/bootstrap.sh`.

This will:

* setup the Arduino dependencies
* add your user to `dialout`
* clone the Espressif ESP32 board support repo to `/usr/share/arduino/hardware/espressif` in accordance with [the instructions]
* checkout the [makeEspArduino project] as a sub-module

[Adafruit_ILI9341]: https://github.com/adafruit/Adafruit_ILI9341/
[BDD]: https://cgreen-devs.github.io/
[the instructions]: https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/debian_ubuntu.md
[makeEspArduino]: https://github.com/plerup/makeEspArduino
