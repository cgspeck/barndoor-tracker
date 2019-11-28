CHIP=esp32
BOARD=esp32
ESP_ROOT = ./esp32

LIBS = ./libraries/AsyncTCP \
	./libraries/ESPAsyncWebServer \
	$(ESP_LIBS)/EEPROM \
	$(ESP_LIBS)/WiFi \
	$(ESP_LIBS)/SPIFFS \
	$(ESP_LIBS)/DNSServer \
	$(ESP_LIBS)/FS

SKETCH=src/main.ino

BUILD_DIR=./build

FS_DIR=./frontend/build

include ./makeEspArduino/makeEspArduino.mk

# ctrl + a, K, y to quit!
monitor:
	screen ${UPLOAD_PORT} ${UPLOAD_SPEED}
