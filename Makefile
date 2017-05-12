TARGET = export-mysql-to-json
LIBS =
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
BUILD_DIR = build

.PHONY: default all clean

default: $(shell mkdir -p $(BUILD_DIR)) $(TARGET)
all: default

OBJECTS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)


$(BUILD_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $(BUILD_DIR)/$@

clean:
	-rm -rf $(BUILD_DIR)
