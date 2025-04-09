config-sources := $(wildcard src/config/*.c)
config-objects := $(patsubst src/config/%.c, $(obj_dir)/config/%.o, $(config-sources))
config-deps    := $(patsubst src/config/%.c, $(obj_dir)/config/%.d, $(config-sources))

objects        += $(config-objects)

$(obj_dir)/config/%.o: src/config/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(config-deps)
