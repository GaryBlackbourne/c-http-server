common_root    := src/common

common_sources := $(wildcard $(common_root)/*.c)
common_objects := $(patsubst $(common_root)/%.c, $(OBJ_DIR)/common-%.o, $(common_sources))
common_deps    := $(patsubst $(OBJ_DIR)/%.o, $(OBJ_DIR)/common-%.d, $(common_objects))

objects        += $(common_objects)

common: $(common_objects)

$(OBJ_DIR)/common-%.o: $(common_root)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(common_deps)



