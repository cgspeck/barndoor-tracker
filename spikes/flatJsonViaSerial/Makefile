CHIP=esp32
BOARD=esp32
ESP_ROOT = ../../esp32

LIBS = ../../libraries/ArduinoJson

monitor:
	echo "\n\nCTRL + a, K, y to quit!\n\n"
	/bin/bash -c 'read -n 1 -s -r -p "Press any key to start..."'
	screen ${UPLOAD_PORT} ${UPLOAD_SPEED}

include ../../makeEspArduino/makeEspArduino.mk
