OUTPUT_DIR           = build
OBJ_DIR              = $(OUTPUT_DIR)/.obj-files
BINARY_NAME          = balu

CC = gcc

CFLAGS          += -Isrc
CFLAGS          += -Isrc/common
CFLAGS          += -Isrc/config

CFLAGS          += -Wall
CFLAGS          += -Wextra
debug: CFLAGS   += -O0
debug: CFLAGS   += -g3
release: CFLAGS += -O3

LDFLAGS         += -pthread
debug: LDFLAGS  += -lasan

SOURCES  = $(wildcard src/*.c)
SOURCES += $(wildcard src/config/*.c)
OBJECTS  = $(foreach SRC, $(SOURCES), $(OBJ_DIR)/$(notdir $(basename $(SRC))).o)

all: debug

release: $(OUTPUT_DIR)/$(BINARY_NAME)
debug:   $(OUTPUT_DIR)/$(BINARY_NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/%.o: src/config/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OUTPUT_DIR)/$(BINARY_NAME): $(OBJECTS)
	@mkdir -p $(OUTPUT_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	@rm -rf $(OBJ_DIR) &>/dev/null
.PHONY: clean

dist-clean:
	@rm -rf $(OUTPUT_DIR) &>/dev/null
.PHONY: clean
