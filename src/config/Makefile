config-root := src/config

config-sources := $(wildcard $(config-root)/*.c)
config-objects := $(patsubst $(config-root)/%.c, $(OBJ_DIR)/config-%.o, $(config-sources))
config-deps    := $(patsubst $(OBJ_DIR)/config-%.o, $(OBJ_DIR)/config-%.d, $(config-objects))

objects += $(config-objects)

config: $(config-objects)

$(OBJ_DIR)/config-%.o: $(config-root)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(config-deps)

