networking-test-sources := $(wildcard test/networking/*-test.c)
networking-test-objects := $(patsubst test/networking/%-test.c, $(obj_dir)/%-test.o, $(networking-test-sources))
networking-test-objects += $(obj_dir)/unity.o

networking-test         += $(test_dir)/networking-test
tests                   += $(networking-test)

$(obj_dir)/%-test.o: test/networking/%-test.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(test-CFLAGS) -c $< -o $@

$(networking-test): $(networking-test-objects) $(networking-objects) $(config-objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)
