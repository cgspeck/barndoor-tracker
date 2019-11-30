CHIP=esp32
BOARD=esp32
ESP_ROOT = ./esp32

LIBS = ./libraries/AsyncTCP \
	./libraries/ArduinoJson \
	./libraries/ESPAsyncWebServer \
	$(ESP_LIBS)/EEPROM \
	$(ESP_LIBS)/WiFi \
	$(ESP_LIBS)/SPIFFS \
	$(ESP_LIBS)/DNSServer \
	$(ESP_LIBS)/FS

SKETCH=src/main.ino

BUILD_DIR=./build

FS_DIR=./frontend/build

monitor:
	echo "\n\nCTRL + a, k, y to quit!\n\n"
	/bin/bash -c 'read -n 1 -s -r -p "Press any key to start..."'
	screen ${UPLOAD_PORT} ${UPLOAD_SPEED}

include ./makeEspArduino/makeEspArduino.mk
