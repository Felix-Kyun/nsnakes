# Makefile
CC := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic  $(shell pkg-config --cflags --libs ncursesw)
INCLUDES := -Iinclude -Icvec/include 
LIBS := -Lcvec -lVec 
SOURCES := $(shell find src -type f -name '*.c')
TARGETS := nsnakes
BUILD_DIR := build

_TARGETS = $(addprefix $(BUILD_DIR)/, $(TARGETS))
_OBJS = $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

all: $(_TARGETS)
	mv $(BUILD_DIR)/nsnakes .

$(_TARGETS): $(_OBJS)
	$(CC) -o $@ $^ $(LIBS) $(INCLUDES) $(CFLAGS)

$(_OBJS): $(BUILD_DIR)/%.o: src/%.c
	$(shell [ -d $(dir $@) ] || mkdir -p $(dir $@))
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(BUILD_DIR):
	$(shell [ -d $(BUILD_DIR) ] || mkdir -p $(BUILD_DIR))

clean:
	rm -rf build/
	rm $(TARGETS)

.PHONY: clean all
