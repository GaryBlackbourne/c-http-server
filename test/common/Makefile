common-test-sources := $(wildcard test/common/*.c)
common-test-objects := $(patsubst test/common/%.c, $(test-obj-dir)/common/%.o, $(common-test-sources))
common-test-deps    := $(patsubst test/common/%.c, $(test-obj-dir)/common/%.d, $(common-test-sources))

test-objects        += $(common-test-objects)

$(test-obj-dir)/common/%.o: test/common/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(test-CFLAGS) -c $< -o $@
-include $(common-test-deps)
