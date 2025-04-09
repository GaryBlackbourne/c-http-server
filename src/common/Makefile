common-sources := $(wildcard src/common/*.c)
common-objects := $(patsubst src/common/%.c, $(obj_dir)/common/%.o, $(common-sources))
common_deps    := $(patsubst src/common/%.c, $(obj_dir)/common/%.d, $(common-sources))

objects        += $(common-objects)

$(obj_dir)/common/%.o: src/common/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(common-deps)
