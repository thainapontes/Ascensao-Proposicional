TARGET = pouproposicoes
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CC = gcc
CFLAGS = -Wall -Wextra -g -I$(INCLUDE_DIR)
LDFLAGS = -lncurses -lrt

# Lista explícita de todos os arquivos .c (para garantir que make encontre o main.c)
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/screen.c $(SRC_DIR)/keyboard.c $(SRC_DIR)/timer.c $(SRC_DIR)/plataforma.c $(SRC_DIR)/pergunta.c $(SRC_DIR)/jogador.c $(SRC_DIR)/visual.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS = $(wildcard $(INCLUDE_DIR)/*.h)

# 1. Regra principal: Linkar todos os objetos no executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -lrt -lncurses

# 2. Regra para garantir que a pasta BUILD_DIR exista (Pré-requisito de Ordem)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(BUILD_DIR) $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean run
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)
