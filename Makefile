# ==========================================================
# VARIÁVEIS DE CONFIGURAÇÃO DO PROJETO
# ==========================================================

# Compilador C que será usado
CC = gcc

# Nome do executável final
EXEC = pouproposicoes

# Caminhos para os diretórios
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Flags de Compilação:
# -Wall: Habilita todos os warnings (boa prática em PIF)
# -Wextra: Habilita warnings extras
# -g: Inclui informações de debug (útil para o professor)
# -I$(INCLUDE_DIR): Informa ao compilador onde buscar os arquivos .h
CFLAGS = -Wall -Wextra -g -I$(INCLUDE_DIR)

# Flags de Linkagem:
# -lncurses: Usada pela CLI-lib para controle de terminal
LDFLAGS = -lncursesW

# ==========================================================
# DEFINIÇÃO DOS ARQUIVOS FONTE (.c)
# ==========================================================

# 1. Módulos da CLI-lib (biblioteca do professor)
CLI_SOURCES = $(SRC_DIR)/screen.c \
              $(SRC_DIR)/keyboard.c \
              $(SRC_DIR)/timer.c

# 2. Módulos do Jogo (seus módulos)
GAME_SOURCES = $(SRC_DIR)/main.c \
               $(SRC_DIR)/jogador.c \
               $(SRC_DIR)/plataforma.c \
               $(SRC_DIR)/pergunta.c \
               $(SRC_DIR)/visual.c

# Combina todos os arquivos .c
C_SOURCES = $(CLI_SOURCES) $(GAME_SOURCES)

# Transforma a lista de arquivos .c em uma lista de arquivos objeto (.o)
# Ex: src/main.c -> build/main.o
O_OBJECTS = $(C_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# ==========================================================
# REGRAS DE COMPILAÇÃO
# ==========================================================

# Regra principal: 'make' compila o executável
.PHONY: all
all: $(BUILD_DIR) $(EXEC)

# Cria o diretório 'build' se ele não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# ----------------------------------------------------------
# Regra 1: Linkar os objetos para criar o executável final
# Depende de todos os arquivos .o estarem prontos.
# A ORDEM CORRETA É: $(OBJETOS) ANTES DE $(LDFLAGS)
# ----------------------------------------------------------
$(EXEC): $(O_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# ----------------------------------------------------------
# Regra 2: Compilar cada arquivo .c em um arquivo objeto .o
# Compila (Ex: src/main.c -> build/main.o)
# ----------------------------------------------------------
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# ==========================================================
# REGRAS AUXILIARES
# ==========================================================

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(EXEC)
	
.PHONY: run
run: $(EXEC)
	./$(EXEC)
