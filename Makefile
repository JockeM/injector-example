CC := clang
CFLAGS := -Os -Wall -std=c99
LDFLAGS := -luser32

# Directories
BUILD_DIR := bin

# Binary files
PAYLOAD_BIN := $(BUILD_DIR)/payload.dll
INJECTOR_BIN := $(BUILD_DIR)/injector.exe

.PHONY: all clean

all: $(PAYLOAD_BIN) $(INJECTOR_BIN)

$(PAYLOAD_BIN): payload.c | $(BUILD_DIR)
	$(CC) -shared -o $@ $< $(LDFLAGS)

$(INJECTOR_BIN): injector.c | $(BUILD_DIR)
	$(CC) -o $@ $< $(CFLAGS)

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)
