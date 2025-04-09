config-test-sources := $(wildcard test/config/*-test.c)
config-test-objects := $(patsubst test/config/%-test.c, $(obj_dir)/%-test.o, $(config-test-sources))
config-test-objects += $(obj_dir)/unity.o

config-test         += $(test_dir)/config-test
tests               += $(config-test)

$(obj_dir)/%-test.o: test/config/%-test.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(test-CFLAGS) -c $< -o $@

$(config-test): $(config-test-objects) $(config-objects) $(common-objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)
