networking-sources := $(wildcard src/networking/*.c)
networking-objects := $(patsubst src/networking/%.c, $(OBJ_DIR)/networking-%.o, $(networking-sources))
networking-deps    := $(patsubst $(OBJ_DIR)/networking-%.o, $(OBJ_DIR)/networking-%.d, $(networking-objects))

objects            += $(networking-objects)

networking-CFLAGS  += -Isrc/config
networking-CFLAGS  += -Isrc/common
networking-CFLAGS  += -I.

networking: $(networking-objects)

$(OBJ_DIR)/networking-%.o: src/networking/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(networking-CFLAGS) -c $< -o $@

-include $(networking-deps)
