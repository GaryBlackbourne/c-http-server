config-test-sources := $(wildcard test/config/*-test.c)
config-test-objects := $(patsubst test/config/%-test.c, $(OBJ_DIR)/%-test.o, $(config-test-sources))
config-test-objects += $(OBJ_DIR)/unity.o

config-test         += $(TEST_DIR)/config-test

config-test-CFLAGS  += -IUnity/src
config-test-CFLAGS  += -Isrc/config
# config-test-CFLAGS  += -Isrc/common

$(OBJ_DIR)/%-test.o: test/config/%-test.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(config-test-CFLAGS) -c $< -o $@

$(config-test): $(config-test-objects) $(config-objects) $(common-objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)

all: $(config-test)
