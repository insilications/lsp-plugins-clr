#!/bin/bash

export THREADS=16
export BUILD_PROFILE=x86_64
export CC_FLAGS=-DLSP_NO_EXPERIMENTAL

echo "******************************************************"
echo "  Building profile=$BUILD_PROFILE"
echo "******************************************************"

make clean && make -j$THREADS all
