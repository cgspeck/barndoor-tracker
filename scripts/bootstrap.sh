#! /bin/bash -e
SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"
source $SCRIPTPATH/vars

sudo apt-get update
sudo apt-get install -y \
  arduino \
  arduino-mk \
  cmake \
  python-serial \
  python3-serial \
  wget

sudo usermod -a -G dialout $USER

if [[ ! -d $ESPRESSIF_DIR ]]; then
  _pwd=$(pwd)
  sudo mkdir $ESPRESSIF_DIR
  sudo git clone https://github.com/espressif/arduino-esp32.git $ESPRESSIF_DIR/esp32


  cd $ESPRESSIF_DIR/esp32
  sudo git submodule update --init --recursive
  cd $ESPRESSIF_DIR/esp32/tools
  sudo python3 get.py

  cd $_pwd
fi

./scripts/update-submodules.sh

if [[ ! -d $CGREEN_DEST ]]; then
  ./scripts/build-cgreen.sh
fi
