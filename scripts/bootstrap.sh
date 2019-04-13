#! /bin/bash -e
sudo apt-get update
sudo apt-get install -y \
  arduino \
  arduino-mk \
  python-serial \
  python3-serial \
  wget

sudo usermod -a -G dialout $USER

ESPRESSIF_DIR=/usr/share/arduino/hardware/espressif

if [[ ! -d $ESPRESSIF_DIR ]]; then
  sudo mkdir $ESPRESSIF_DIR
  sudo git clone https://github.com/espressif/arduino-esp32.git $ESPRESSIF_DIR/esp32

  _pwd=$(pwd)

  cd $ESPRESSIF_DIR/esp32
  sudo git submodule update --init --recursive
  cd $ESPRESSIF_DIR/esp32/tools
  sudo python3 get.py

  cd $_pwd
fi

./scripts/update-submodules.sh
