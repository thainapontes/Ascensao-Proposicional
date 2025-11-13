Nome do executável

TARGET = pouproposicoes

Diretórios

BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include

Compilador e Flags

CC = gcc
CFLAGS = -Wall -Wextra -g -I$(INCLUDE_DIR)
LDFLAGS = -lncurses -lrt

Lista de todos os arquivos fonte .c

SRCS = $(wildcard $(SRC_DIR)/*.c)

Lista de todos os arquivos objeto .o (no diretório build)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

Lista de todos os arquivos de cabeçalho .h

DEPS = $(wildcard $(INCLUDE_DIR)/*.h)

-----------------------------------------------------------------------------

REGRAS PRINCIPAIS

-----------------------------------------------------------------------------

Regra principal: compila e linka o executável

$(TARGET): $(OBJS)
$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

Regra para criar o diretório build

$(BUILD_DIR):
mkdir -p $(BUILD_DIR)

Regra genérica para compilar qualquer arquivo .c em .o

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(BUILD_DIR) $(DEPS)
$(CC) $(CFLAGS) -c $< -o $@

-----------------------------------------------------------------------------

REGRAS AUXILIARES

-----------------------------------------------------------------------------

.PHONY: clean
clean:
rm -rf $(BUILD_DIR) $(TARGET)
