#! /bin/bash -e
SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"
source $SCRIPTPATH/vars

_pwd=$(pwd)
tmp_file=$(mktemp)

wget https://github.com/cgreen-devs/cgreen/archive/$CGREEN_VERSION.zip -O $tmp_file
unzip $tmp_file -d vendor
cd $CGREEN_DEST
make
make test
sudo make install
sudo /sbin/ldconfig
cd $_pwd
