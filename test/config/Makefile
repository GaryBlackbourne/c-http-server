config-test-sources := $(wildcard test/config/*-test.c)
config-test-objects := $(patsubst test/config/%-test.c, $(OBJ_DIR)/%-test.o, $(config-test-sources))
config-test-objects += $(OBJ_DIR)/unity.o

config-test         += $(TEST_DIR)/config-test
tests               += $(config-test)

$(OBJ_DIR)/%-test.o: test/config/%-test.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(test-CFLAGS) -c $< -o $@

$(config-test): $(config-test-objects) $(config-objects) $(common-objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)

all: $(config-test)
