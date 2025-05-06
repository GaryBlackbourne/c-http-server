workerpool-sources := $(wildcard src/workerpool/*.c)
workerpool-objects := $(patsubst src/workerpool/%.c, $(obj-dir)/workerpool/%.o, $(workerpool-sources))
workerpool-deps    := $(patsubst src/workerpool/%.c, $(obj-dir)/workerpool/%.d, $(workerpool-sources))

objects            += $(workerpool-objects)

$(obj-dir)/workerpool/%.o: src/workerpool/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(workerpool-deps)
