#!/bin/sh

BUILD_DIRECTORY=build

mkdir -p $BUILD_DIRECTORY
cd $BUILD_DIRECTORY
cmake ..
make