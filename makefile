# How to use:
# make					# debug build
# make BUILD=release 	#release build
# make clean			# clean

CC 		 := gcc
CFLAGS 	 := -Wall -Wextra -Werror -std=c2x
INCLUDES := -Iinclude

DEBUG_FLAGS 	:= -g -O0 -DNDEBUG
RELEASE_FLAGS	:= -O3

BUILD ?= DEBUG

ifeq ($(BUILD),release)
	CFLAGS += $(RELEASE_FLAGS)
else
	CFLAGS += $(DEBUG_FLAGS)
endif

SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=build/obj/%.o)
DEP := $(OBJ:.o=.d)

TARGET 	:= bin/mana

.PHONY := all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p bin
	$(CC) $(OBJ) -o $@

build/obj/%.o: src/%.c
	@mkdir -p build/obj
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

-include $(DEP)

clean:
	rm -rf build bin