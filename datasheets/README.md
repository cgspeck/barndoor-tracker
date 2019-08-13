# References

## Lens warming strap

COOWOO Upgraded Lens Warmer/Heater Dew Heater Strip for Universal SLR Camera Lens and Telescopes

[Purchase page - "hot2" (Amazon)](https://www.amazon.com.au/gp/product/B0773M7Y98/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)

"hot2" specs:

Strip length: 14in
Strip width: 3.15in
Heater length: 8.3in
Strip material: Neoprene and polyester
Heater material: Carbon fiber heating coil
Power Consumption: 5V 0.8A 4W
USB cord length: 59in
Velcro length: 4.72in

## USB Power Connectors

Use 2x [Panel Mount USB to 4-pin Female Header Cable - 6'](https://core-electronics.com.au/panel-mount-usb-to-4-pin-female-header-cable-6.html), $4.41 each.

## DS18B20 Digital temperature sensor

1wire bus.

[Product Page](https://core-electronics.com.au/waterproof-ds18b20-digital-temperature-sensor.html).

[Wiki](https://wiki.dfrobot.com/Waterproof_DS18B20_Digital_Temperature_Sensor__SKU_DFR0198_)

[Wiring and use with ESP32 in Arduino](https://randomnerdtutorials.com/esp32-multiple-ds18b20-temperature-sensors/)

Use a 3.5mm stereo panel mount socket / plug combo.

Use a header on board to connect.

## Compass/Orientation sensor

i2c bus

[SparkFun 9DoF Sensor Stick](https://www.sparkfun.com/products/13944)

> This breakout board has built-in 4.7 kΩ pull up resistors for I2C communications. If you're hooking up multiple I2C devices on the same bus, you may want to disable/enable the pull-up resistors for one or more boards.

## Stepper driver

SPI

TMC2130 evaluation board.

[Purchase page](https://www.aliexpress.com/item/32853263225.html?spm=a2g0s.9042311.0.0.27424c4drxUNUe).

## Display

SPI(?)

[8 Digit 7 Segment Display Module](https://www.jaycar.com.au/8-digit-7-segment-display-module/p/XC3714)

MAX7219 based 8 Digit 7 Segment Display module

Pins (top-to-bottom):

* VCC (5v)
* GND
* DIN (-> MOSI)
* CS
* CLK (-> SCK)

## Buttons

Does the ESP32 have internal pull-down or pull-up resistors?

Need 4:

 * home
 * track start / stop
 * unassigned
 * (rescessed) system reset

