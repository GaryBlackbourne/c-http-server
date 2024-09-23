config-root := src/config

config-sources := $(wildcard $(config-root)/*.c)
config-objects := $(patsubst $(config-root)/%.c, $(OBJ_DIR)/config-%.o, $(config-sources))
config-deps    := $(patsubst $(OBJ_DIR)/config-%.o, $(OBJ_DIR)/config-%.d, $(config-objects))

objects        += $(config-objects)

config-CFLAGS  := -Isrc/common
config-CFLAGS  += -I.

config: $(config-objects)

$(OBJ_DIR)/config-%.o: $(config-root)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(config-CFLAGS) -c $< -o $@

-include $(config-deps)

-include src/config/cmdline-parser/Makefile
