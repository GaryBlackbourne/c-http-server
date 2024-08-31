common-test-sources := $(wildcard test/common/*-test.c)
common-test-objects := $(patsubst test/common/%-test.c, $(OBJ_DIR)/%-test.o, $(common-test-sources))
common-test-objects += $(OBJ_DIR)/unity.o

common-test         += $(TEST_DIR)/common-test

common-test-CFLAGS  += -IUnity/src
common-test-CFLAGS  += -Isrc/common

$(OBJ_DIR)/%-test.o: test/common/%-test.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(common-test-CFLAGS) -c $< -o $@

$(common-test): $(common-test-objects) $(common-objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)

all: $(common-test)
