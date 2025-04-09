config-root := src/config

config-sources := $(wildcard $(config-root)/*.c)
config-objects := $(patsubst $(config-root)/%.c, $(obj_dir)/config-%.o, $(config-sources))
config-deps    := $(patsubst $(obj_dir)/config-%.o, $(obj_dir)/config-%.d, $(config-objects))

objects        += $(config-objects)

$(obj_dir)/config-%.o: $(config-root)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(config-deps)
