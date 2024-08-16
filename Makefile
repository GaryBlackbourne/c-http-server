OUTPUT_DIR           = output
OBJ_DIR              = $(OUTPUT_DIR)/.obj-files
SRC_DIR              = src
BINARY_NAME          = balu

CC = gcc

CFLAGS          += -Wall
CFLAGS          += -Wextra
debug: CFLAGS   += -O0
debug: CFLAGS   += -g3
release: CFLAGS += -O3

LDFLAGS         += -pthread
debug: LDFLAGS  += -lasan

SOURCES = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(SRC_DIR)/*.h)
OBJECTS = $(foreach SRC, $(SOURCES), $(OBJ_DIR)/$(notdir $(basename $(SRC))).o)

all: debug

release: $(OUTPUT_DIR)/$(BINARY_NAME)
debug:   $(OUTPUT_DIR)/$(BINARY_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
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
