common-root    := src/common

common-sources := $(wildcard $(common-root)/*.c)
common-objects := $(patsubst $(common-root)/%.c, $(obj_dir)/common-%.o, $(common-sources))
common_deps    := $(patsubst $(obj_dir)/common-%.o, $(obj_dir)/common-%.d, $(common-objects))

objects        += $(common-objects)

common: $(common-objects)

$(obj_dir
)/common-%.o: $(common-root)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(common-deps)



