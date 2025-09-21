# Configurações gerais
CXX := g++
CXXFLAGS := -g --std=c++17 -I../include -Wall -Wextra
LDFLAGS := -L../lib -lglfw3dll -lopengl32 -lgdi32
GLAD_SRC := ../src/glad.c
SRC_DIR := ../src

# Compilar todas as tarefas
all: tarefa_1 tarefa_2 tarefa_3

# Tarefas individuais
tarefa_1: $(SRC_DIR)/tarefa_1/main.cpp $(GLAD_SRC)
	@echo "Compilando Tarefa 1..."
	$(CXX) $(CXXFLAGS) $< $(GLAD_SRC) $(LDFLAGS) -o tarefa_1

tarefa_2: $(SRC_DIR)/tarefa_2/main.cpp $(GLAD_SRC)
	@echo "Compilando Tarefa 2..."
	$(CXX) $(CXXFLAGS) $< $(GLAD_SRC) $(LDFLAGS) -o tarefa_2

tarefa_3: $(SRC_DIR)/tarefa_3/main.cpp $(GLAD_SRC)
	@echo "Compilando Tarefa 3..."
	$(CXX) $(CXXFLAGS) $< $(GLAD_SRC) $(LDFLAGS) -o tarefa_3

# Executar tarefas
run_1: tarefa_1
	@echo "Executando Tarefa 1..."
	./tarefa_1

run_2: tarefa_2
	@echo "Executando Tarefa 2..."
	./tarefa_2

run_3: tarefa_3
	@echo "Executando Tarefa 3..."
	./tarefa_3

# Limpeza (compatível com Windows)
clean:
	@echo "Limpando arquivos compilados..."
	-del /Q tarefa_1.exe tarefa_2.exe tarefa_3.exe 2>nul || true
	-rm -f tarefa_1 tarefa_2 tarefa_3 2>/dev/null || true

# Ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make all          - Compila todas as tarefas"
	@echo "  make tarefa_N     - Compila tarefa específica (N = 1,2,3)"
	@echo "  make run_N        - Compila e executa tarefa N"
	@echo "  make clean        - Remove arquivos compilados"
	@echo "  make help         - Mostra esta ajuda"

.PHONY: all clean help run_1 run_2 run_3 tarefa_1 tarefa_2 tarefa_3