common-test-sources := $(wildcard test/common/*-test.c)
common-test-objects := $(patsubst test/common/%-test.c, $(obj_dir)/%-test.o, $(common-test-sources))
common-test-objects += $(obj_dir)/unity.o

common-test         += $(test_dir)/common-test
tests               += $(common-test)

$(obj_dir)/%-test.o: test/common/%-test.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(test-CFLAGS) -c $< -o $@

$(common-test): $(common-test-objects) $(common-objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)
