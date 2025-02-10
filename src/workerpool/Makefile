workerpool-root := src/workerpool

workerpool-sources := $(wildcard $(workerpool-root)/*.c)
workerpool-objects := $(patsubst $(workerpool-root)/%.c, $(OBJ_DIR)/workerpool-%.o, $(workerpool-sources))
workerpool-deps    := $(patsubst $(OBJ_DIR)/workerpool-%.o, $(OBJ_DIR)/workerpool-%.d, $(workerpool-objects))

objects            += $(workerpool-objects)

workerpool-CFLAGS  := -Isrc/config
workerpool-CFLAGS  += -Isrc/networking
workerpool-CFLAGS  += -I.

workerpool: $(workerpool-objects)

$(OBJ_DIR)/workerpool-%.o: $(workerpool-root)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(workerpool-CFLAGS) -c $< -o $@

-include $(workerpool-deps)
