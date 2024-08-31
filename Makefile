MODE            ?= release

OUTPUT_DIR      := build
OBJ_DIR         := $(OUTPUT_DIR)/$(MODE)/.obj-files
BINARY_NAME     := balu
BINARY          := $(OUTPUT_DIR)/$(MODE)/$(BINARY_NAME)
CC              := gcc

CFLAGS          := -Wall
CFLAGS          += -Wextra
CFLAGS          += -MMD

LDFLAGS         := -pthread

ifeq($(MODE), release)
	CFLAGS  += -O3
	LDFLAGS += -lasan
else ifeq ($(MODE), debug)
	CFLAGS  += -O0
	CFLAGS  += -g3
else
	$(error "Invalid MODE value: $(MODE). Use either 'release' or 'debug'.")
endif

all: $(BINARY) 

-include $(OBJ_DIR)/main.d

objects  := $(OBJ_DIR)/main.o
$(OBJ_DIR)/main.o: src/main.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

-include src/config/Makefile
-include src/common/Makefile

$(BINARY): $(objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/unity.o: Unity/src/unity.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) &>/dev/null
	@rm -r  $(BINARY)  &>/dev/null
.PHONY: clean

dist-clean:
	@rm -rf $(OUTPUT_DIR) &>/dev/null
.PHONY: clean
