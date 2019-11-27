CHIP=esp32
BOARD=esp32
ESP_ROOT = ./esp32

LIBS = ./libraries/AsyncTCP \
	./libraries/ESPAsyncWebServer \
	$(ESP_LIBS)/EEPROM

SKETCH=src/main.ino

BUILD_DIR=./build

include ./makeEspArduino/makeEspArduino.mk
