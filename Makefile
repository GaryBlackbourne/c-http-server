MODE            ?= debug

OUTPUT_DIR      := build
OBJ_DIR         := $(OUTPUT_DIR)/$(MODE)/.obj-files
TEST_DIR        := $(OUTPUT_DIR)/$(MODE)/tests
BINARY_NAME     ?= balu
BINARY          := $(OUTPUT_DIR)/$(MODE)/$(BINARY_NAME)
CC              := gcc

CFLAGS          += -Wall
CFLAGS          += -Wextra
CFLAGS          += -Wpedantic
CFLAGS          += -MMD
CFLAGS          += -std=c23

LDFLAGS         += -pthread
LDFLAGS         += -lm

tests           := 

ifeq ($(MODE), release)
	CFLAGS  += -O3
else ifeq ($(MODE), debug)
	CFLAGS  += -O0
	CFLAGS  += -g3
else
	$(error "Invalid MODE value: $(MODE). Use either 'release' or 'debug'.")
endif

CFLAGS += -Isrc
CFLAGS += -Isrc/common
CFLAGS += -Isrc/config
CFLAGS += -Isrc/networking
CFLAGS += -Isrc/workerpool

test-CFLAGS := -IUnity/src

all: $(BINARY)

-include $(OBJ_DIR)/main.d

objects  := $(OBJ_DIR)/main.o
$(OBJ_DIR)/main.o: src/main.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(main-CFLAGS) -c $< -o $@

include src/common/Makefile
include test/common/Makefile

include src/config/Makefile
include test/config/Makefile

include src/networking/Makefile
# include test/networking/Makefile

-include src/workerpool/Makefile
# -include test/workerpool/Makefile

$(BINARY): $(objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/unity.o: Unity/src/unity.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_DIR)/*.o    &>/dev/null
	@rm -f $(OBJ_DIR)/*.d    &>/dev/null
	@rm -f $(BINARY)         &>/dev/null
.PHONY: clean

distclean: clean
.PHONY: distclean

# For running tests from make
define newline


endef
check: $(BINARY) $(tests)
	$(foreach t, $(tests), ./$(t)$(newline))

