networking-test-sources := $(wildcard test/networking/*.c)
networking-test-objects := $(patsubst test/networking/%.c, $(test-obj-dir)/networking/%.o, $(networking-test-sources))
networking-test-deps    := $(patsubst test/networking/%.c, $(test-obj-dir)/networking/%.d, $(networking-test-sources))

test-objects            += $(networking-test-objects)

$(test-obj-dir)/networking/%.o: test/networking/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(test-CFLAGS) -c $< -o $@
-include $(networking-test-deps)
