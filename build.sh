#!/usr/bin/env bash

set -x -e

sudo apt install libqt5serialport5-dev
qmake .
make
