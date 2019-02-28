#!/bin/bash
fetch breakpad
gclient sync

# remove old version if needed
rm -rf _bad_scm

# remove .git if needed
rm -rf src/.git
rm -rf src/.gitignore
rm -rf src/src/third_party/lss/.git