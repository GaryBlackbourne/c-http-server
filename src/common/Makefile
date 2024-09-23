common-root    := src/common

common-sources := $(wildcard $(common-root)/*.c)
common-objects := $(patsubst $(common-root)/%.c, $(OBJ_DIR)/common-%.o, $(common-sources))
common_deps    := $(patsubst $(OBJ_DIR)/common-%.o, $(OBJ_DIR)/common-%.d, $(common-objects))

objects        += $(common-objects)

common: $(common-objects)

$(OBJ_DIR)/common-%.o: $(common-root)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(common-deps)



