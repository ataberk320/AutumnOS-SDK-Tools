#!/bin/bash
CC="gcc"
[ "$1" == "arm" ] && CC="arm-linux-gnueabihf-gcc"
[ "$1 == risc-v ] &&
CC = riscv-linux-gcc

rm -f *.o *.so gltestapp
$CC -c AutumnGL_Eng.c AutumnGL_Math.c -fPIC $(pkg-config --cflags sdl2 freetype2)
$CC -shared -o libautumngl.so AutumnGL_Eng.o AutumnGL_Math.o $(pkg-config --libs sdl2 freetype2) -lGLESv2 -lEGL -lm
$CC gltest.c -o gltestapp -L. -lautumngl $(pkg-config --cflags --libs sdl2 freetype2) -lGLESv2 -lEGL -lm
