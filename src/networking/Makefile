networking-sources := $(wildcard src/networking/*.c)
networking-objects := $(patsubst src/networking/%.c, $(obj-dir)/networking/%.o, $(networking-sources))
networking-deps    := $(patsubst src/networking/%.c, $(obj-dir)/networking/%.d, $(networking-sources))

objects            += $(networking-objects)

$(obj-dir)/networking/%.o: src/networking/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(networking-deps)
