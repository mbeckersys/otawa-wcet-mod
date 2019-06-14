MAKEFILE_DIR=$(dir $(realpath $(firstword $(MAKEFILE_LIST))))
BUILD_DIR=linux-x86_64

# install location ... modify as needed
PREFIX=$(MAKEFILE_DIR)/$(BUILD_DIR)/otawa-core

all: bootstrap build install

.PHONY: build install

$(BUILD_DIR): build.sh
	./build.sh

build: $(BUILD_DIR)
	cd $(BUILD_DIR)/otawa-core-build && make

install:
	cd $(BUILD_DIR)/otawa-core-build && make install PREFIX=$(PREFIX) INSTALL_TYPE=all user=None
