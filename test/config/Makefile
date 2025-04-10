config-test-sources := $(wildcard test/config/*.c)
config-test-objects := $(patsubst test/config/%.c, $(test_obj_dir)/config/%.o, $(config-test-sources))
config-test-deps    := $(patsubst test/config/%.c, $(test_obj_dir)/config/%.d, $(config-test-sources))
config-test-objects += $(obj_dir)/unity.o

config-test         += $(test_dir)/config-test
tests               += $(config-test)

$(test_obj_dir)/config/%.o: test/config/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(test-CFLAGS) -c $< -o $@
-include $(conig-test-deps)

$(config-test): $(config-test-objects) $(objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)
