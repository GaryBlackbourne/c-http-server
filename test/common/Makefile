common-test-sources := $(wildcard test/common/*.c)
common-test-objects := $(patsubst test/common/%.c, $(test_obj_dir)/common/%.o, $(common-test-sources))
common-test-deps    := $(patsubst test/common/%.c, $(test_obj_dir)/common/%.d, $(common-test-sources))
common-test-objects += $(obj_dir)/unity.o

common-test         += $(test_dir)/common-test
tests               += $(common-test)

$(test_obj_dir)/common/%.o: test/common/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(test-CFLAGS) -c $< -o $@
-include $(common-test-deps)

$(common-test): $(common-test-objects) $(objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)
