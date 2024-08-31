config_root := src/config

config_sources := $(wildcard $(config_root)/*.c)
config_objects := $(patsubst $(config_root)/%.c, $(OBJ_DIR)/config-%.o, $(config_sources))
config_deps    := $(patsubst $(OBJ_DIR)/config-%.o, $(OBJ_DIR)/config-%.d, $(config_objects))

objects += $(config_objects)

config: $(config_objects)

$(OBJ_DIR)/config-%.o: $(config_root)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(config_deps)

