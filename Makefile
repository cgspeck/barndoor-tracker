ESP_LIBS = $(ESP_ROOT)/libraries

LIBS=./src \
	./libraries \
	$(ESP_LIBS)/EEPROM

SKETCH=src/main.ino

BUILD_DIR=./build

include ./makeEspArduino/makeEspArduino.mk
