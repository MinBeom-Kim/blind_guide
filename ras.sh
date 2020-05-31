#!/bin/sh
g++ raspicamview.cpp -o raspicamview `pkg-config --cflags --libs opencv3`