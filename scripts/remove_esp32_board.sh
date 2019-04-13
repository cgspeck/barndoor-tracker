#! /bin/bash -e

ESPRESSIF_DIR=/usr/share/arduino/hardware/espressif

if [[ -d $ESPRESSIF_DIR ]]; then
  sudo rm -rf $ESPRESSIF_DIR
fi
