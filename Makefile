MODE        ?= debug
BINARY_NAME ?= balu

build_dir   := build
obj_dir     := $(build_dir)/$(MODE)/.obj-files
test_dir    := $(build_dir)/$(MODE)/tests
binary      := $(build_dir)/$(MODE)/$(BINARY_NAME)
CC          := gcc

CFLAGS      += -Wall
CFLAGS      += -Wextra
CFLAGS      += -Wpedantic
CFLAGS      += -MMD
CFLAGS      += -std=c23

LDFLAGS     += -pthread
LDFLAGS     += -lm

tests       := 

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

all: $(binary)

objects  := $(obj_dir)/main.o

$(obj_dir)/main.o: src/main.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(main-CFLAGS) -c $< -o $@
-include $(obj_dir)/main.d

include src/common/Makefile
include src/config/Makefile
include src/networking/Makefile
-include src/workerpool/Makefile

include test/common/Makefile
include test/config/Makefile
include test/networking/Makefile
# -include test/workerpool/Makefile

$(binary): $(objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)

$(obj_dir)/unity.o: Unity/src/unity.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(obj_dir)/*.o    &>/dev/null
	@rm -f $(obj_dir)/*.d    &>/dev/null
	@rm -f $(binary)         &>/dev/null
.PHONY: clean

distclean:
	rm -rf $(build_dir)
.PHONY: distclean

# For running tests from make
define newline


endef
check: $(binary) $(tests)
	$(foreach t, $(tests), ./$(t)$(newline))

