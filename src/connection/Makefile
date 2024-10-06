connection-root := src/connection

connection-sources := $(wildcard $(connection-root)/*.c)
connection-objects := $(patsubst $(connection-root)/%.c, $(OBJ_DIR)/connection-%.o, $(connection-sources))
connection-deps    := $(patsubst $(OBJ_DIR)/connection-%.o, $(OBJ_DIR)/connection-%.d, $(connection-objects))

objects        += $(connection-objects)

connection-CFLAGS  := -Isrc/config
connection-CFLAGS  += -I.

connection: $(connection-objects)

$(OBJ_DIR)/connection-%.o: $(connection-root)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(connection-CFLAGS) -c $< -o $@

-include $(connection-deps)

-include src/connection/cmdline-parser/Makefile
