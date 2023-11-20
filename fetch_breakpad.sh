#!/bin/bash

mkdir -p fetch_breakpad

pushd fetch_breakpad
	fetch breakpad
	gclient sync

	cp -a -f src/src/. ../Source/Breakpad
popd

rm -rf Source/Breakpad/third_party/lss/.git
rm -rf Source/Breakpad/third_party/protobuf/protobuf/.git
