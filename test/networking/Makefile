networking-test-sources := $(wildcard test/networking/*.c)
networking-test-objects := $(patsubst test/networking/%.c, $(obj_dir)/test/networking/%.o, $(networking-test-sources))
networking-test-deps    := $(patsubst test/networking/%.c, $(obj_dir)/test/networking/%.d, $(networking-test-sources))
networking-test-objects += $(obj_dir)/unity.o

networking-test         += $(test_dir)/networking-test
tests                   += $(networking-test)

$(obj_dir)/test/networking/%.o: test/networking/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(test-CFLAGS) -c $< -o $@
-include $(networking-test-deps)

$(networking-test): $(networking-test-objects) $(objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)
