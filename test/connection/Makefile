connection-test-sources := $(wildcard test/connection/*-test.c)
connection-test-objects := $(patsubst test/connection/%-test.c, $(OBJ_DIR)/%-test.o, $(connection-test-sources))
connection-test-objects += $(OBJ_DIR)/unity.o

connection-test         += $(TEST_DIR)/connection-test
tests                   += $(connection-test)

$(OBJ_DIR)/%-test.o: test/connection/%-test.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(test-CFLAGS) -c $< -o $@

$(connection-test): $(connection-test-objects) $(connection-objects) $(config-objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)

all: $(connection-test)
