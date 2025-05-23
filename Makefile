MODE         ?= debug
BINARY_NAME  ?= balu

build_dir    := build
obj_dir      := $(build_dir)/$(MODE)/.obj-files
test_dir     := $(build_dir)/$(MODE)/tests
test_obj_dir := $(test_dir)/.obj-files
binary       := $(build_dir)/$(MODE)/$(BINARY_NAME)
CC           := gcc

CFLAGS       += -Wall
CFLAGS       += -Wextra
CFLAGS       += -Wpedantic
CFLAGS       += -MMD
CFLAGS       += -std=c23

LDFLAGS      += -pthread
LDFLAGS      += -lm

tests        := 

ifeq ($(MODE), release)
	CFLAGS  += -O3
	CFLAGS  += -flto
	LFLAGS  += -flto
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

include src/common/Makefile
include src/config/Makefile
include src/networking/Makefile
include src/workerpool/Makefile

include test/common/Makefile
include test/config/Makefile
include test/networking/Makefile
# -include test/workerpool/Makefile

$(obj_dir)/main.o: src/main.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(main-CFLAGS) -c $< -o $@
-include $(obj_dir)/main.d

objects  += $(obj_dir)/main.o

$(binary): $(objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)

$(obj_dir)/unity.o: Unity/src/unity.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
tests: $(tests)

# For running tests from make
define newline


endef
check: $(tests)
	$(foreach t, $(tests), ./$(t)$(newline))

clean:
	rm -rf $(obj_dir)/*     &>/dev/null
	rm -rf $(test_obj_dir)/* &>/dev/null
	rm -rf $(test_dir)/*    &>/dev/null
	rm -f $(binary)         &>/dev/null
.PHONY: clean

distclean:
	rm -rf $(build_dir)
.PHONY: distclean
