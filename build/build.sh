#!/bin/bash

# depot_tool need to be installed on you machine(https://chromium.googlesource.com/chromium/src/+/lkcr/docs/mac_build_instructions.md)
mkdir breakpad && \
    cd breakpad && \
    fetch breakpad && \
    cd src && \
    ./configure && make -j4



mkdir -p ../libs

NDK_LIBS_OUT="../libs" ndk-build "$@"

rm -rf obj