workerpool-root := src/workerpool

workerpool-sources := $(wildcard $(workerpool-root)/*.c)
workerpool-objects := $(patsubst $(workerpool-root)/%.c, $(obj_dir)/workerpool-%.o, $(workerpool-sources))
workerpool-deps    := $(patsubst $(obj_dir)/workerpool-%.o, $(obj_dir)/workerpool-%.d, $(workerpool-objects))

objects            += $(workerpool-objects)

workerpool: $(workerpool-objects)

$(obj_dir)/workerpool-%.o: $(workerpool-root)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(workerpool-deps)
