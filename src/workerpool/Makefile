workerpool-sources := $(wildcard src/workerpool/*.c)
workerpool-objects := $(patsubst src/workerpool/%.c, $(obj_dir)/workerpool/%.o, $(workerpool-sources))
workerpool-deps    := $(patsubst src/workerpool/%.c, $(obj_dir)/workerpool/%.d, $(workerpool-sources))

objects            += $(workerpool-objects)

$(obj_dir)/workerpool/%.o: src/workerpool/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(workerpool-deps)
