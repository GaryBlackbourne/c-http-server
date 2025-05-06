config-test-sources := $(wildcard test/config/*.c)
config-test-objects := $(patsubst test/config/%.c, $(test-obj-dir)/config/%.o, $(config-test-sources))
config-test-deps    := $(patsubst test/config/%.c, $(test-obj-dir)/config/%.d, $(config-test-sources))

test-objects        += $(config-test-objects)

$(test-obj-dir)/config/%.o: test/config/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(test-CFLAGS) -c $< -o $@
-include $(conig-test-deps)
