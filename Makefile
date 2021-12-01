SHELL=/bin/bash

BUILD_DIR = ./build

all: build
	cd $(BUILD_DIR); cmake ..; make
clean:
	rm semi;cd $(BUILD_DIR); rm -rf ./*

build:
	mkdir $(BUILD_DIR); cd $(BUILD_DIR); cmake ..