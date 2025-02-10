#!/bin/bash

rm -rf build

cmake -S . -B build -G "Ninja Multi-Config" \
  -DCMAKE_CONFIGURATION_TYPES="Debug;Release" \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
  -DCMAKE_CXX_COMPILER=$INSTP/bin/clang++ \
  -DCMAKE_CXX_FLAGS="-fexperimental-library" \
  -DCMAKE_EXE_LINKER_FLAGS="-L$INSTP/lib -Wl,-rpath,$INSTP/lib -fuse-ld=lld -stdlib=libc++" \
  -Wno-dev
