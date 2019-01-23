#!/bin/bash

# depot_tool need to be installed on you machine(https://chromium.googlesource.com/chromium/src/+/lkcr/docs/mac_build_instructions.md)
pushd "$(realpath $(dirname $0))"
	mkdir breakpad && \
    	cd breakpad && \
    	fetch breakpad && \
    	cd src && \
    	./configure && make -j4

	mkdir -p ./libs/armeabi-v7a

	NDK_LIBS_OUT="./libs" ndk-build "$@"
popd

rsync \
      --include="*.a" \
      --exclude="*" \
      -r "obj/local/armeabi-v7a/" "libs/armeabi-v7a" 

mkdir -p ./include/

rsync \
      --include="*.h" \
      --include='*/' \
      --exclude="*" \
      -r "breakpad/src/src/client" "include" 

rsync \
      --include="*.h" \
      --include='*/' \
      --exclude="*" \
      -r "breakpad/src/src/common" "include" 

rsync \
      --include="*.h" \
      --include='*/' \
      --exclude="*" \
      -r "breakpad/src/src/google_breakpad" "include" 

rsync \
      --include="*.h" \
      --include='*/' \
      --exclude="*" \
      -r "breakpad/src/src/third_party" "include" 

rm -rf ./obj
# rm -rf ./breakpad