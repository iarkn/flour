PROJECT := flour
BUILD   := build
TARGET  := $(BUILD)/$(PROJECT)

SRCS := $(shell find src -type f -name "*.c")
OBJS := $(SRCS:src/%.c=$(BUILD)/obj/%.o)
DEPS := $(OBJS:%.o=%.d)
PKGS := ncursesw

CC     ?= gcc
CFLAGS += -O3 -ggdb -std=c17 -Wall -Wextra -Wpedantic -Iinclude
CFLAGS += $(shell pkg-config --cflags $(PKGS))
LDLIBS := $(shell pkg-config --libs $(PKGS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "-- Linking executable $@"
	@$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

-include $(DEPS)

$(BUILD)/obj/%.o: src/%.c
	@mkdir -p $(@D)
	@echo "-- Compiling file $<"
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	@rm -rf $(BUILD)

.PHONY: all clean
