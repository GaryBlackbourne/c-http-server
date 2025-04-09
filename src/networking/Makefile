networking-sources := $(wildcard src/networking/*.c)
networking-objects := $(patsubst src/networking/%.c, $(obj_dir)/networking-%.o, $(networking-sources))
networking-deps    := $(patsubst $(obj_dir)/networking-%.o, $(obj_dir)/networking-%.d, $(networking-objects))

objects            += $(networking-objects)

$(obj_dir)/networking-%.o: src/networking/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(networking-deps)
