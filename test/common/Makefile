common-test-sources := $(wildcard test/common/*.c)
common-test-objects := $(patsubst test/common/%.c, $(obj_dir)/test/common/%.o, $(common-test-sources))
common-test-deps    := $(patsubst test/common/%.c, $(obj_dir)/test/common/%.d, $(common-test-sources))
common-test-objects += $(obj_dir)/unity.o

common-test         += $(test_dir)/common-test
tests               += $(common-test)

$(obj_dir)/test/common/%.o: test/common/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(test-CFLAGS) -c $< -o $@
-include $(common-test-deps)

$(common-test): $(common-test-objects) $(objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)
