common-sources := $(wildcard src/common/*.c)
common-objects := $(patsubst src/common/%.c, $(obj-dir)/common/%.o, $(common-sources))
common_deps    := $(patsubst src/common/%.c, $(obj-dir)/common/%.d, $(common-sources))

objects        += $(common-objects)

$(obj-dir)/common/%.o: src/common/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(common-deps)
