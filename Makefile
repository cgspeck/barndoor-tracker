CHIP=esp32
ESP_ROOT = ./esp32
ESP_LIBS = $(ESP_ROOT)/libraries

CUSTOM_LIBS=./libraries

SKETCH=src/main.ino

BUILD_DIR=./build

include ./makeEspArduino/makeEspArduino.mk
