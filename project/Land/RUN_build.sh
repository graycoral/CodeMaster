#!/bin/sh
rm -rf build
mkdir build

WORK_DIR=$PWD

pushd build
source ../runcmake.sh
source ../runmake.sh
source ../runmake_install.sh
popd
