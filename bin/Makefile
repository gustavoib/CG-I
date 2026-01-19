# Configurações gerais
CXX := g++
CXXFLAGS := -g --std=c++17 -I../include -Wall -Wextra
LDFLAGS := -L../lib -lglfw3dll -lopengl32 -lgdi32
GLAD_SRC := ../src/glad.c
SRC_DIR := ../src

# Compilar trabalho final
all: trabalho_final

# Trabalho final
trabalho_final: $(SRC_DIR)/trabalho_final/main.cpp $(SRC_DIR)/trabalho_final/Cenario.cpp $(SRC_DIR)/trabalho_final/Camera.cpp $(SRC_DIR)/trabalho_final/Cor.cpp $(SRC_DIR)/trabalho_final/Esfera.cpp $(SRC_DIR)/trabalho_final/Plano.cpp $(SRC_DIR)/trabalho_final/FonteIluminacao.cpp $(SRC_DIR)/trabalho_final/Janela.cpp $(SRC_DIR)/trabalho_final/Ponto.cpp $(SRC_DIR)/trabalho_final/Vetor.cpp $(SRC_DIR)/trabalho_final/Cilindro.cpp $(SRC_DIR)/trabalho_final/Cone.cpp $(SRC_DIR)/trabalho_final/Cubo.cpp $(SRC_DIR)/trabalho_final/Textura.cpp $(SRC_DIR)/trabalho_final/Malha.cpp $(SRC_DIR)/trabalho_final/Matriz.cpp $(SRC_DIR)/trabalho_final/Aresta.cpp $(SRC_DIR)/trabalho_final/Face.cpp $(SRC_DIR)/trabalho_final/Vertice.cpp $(SRC_DIR)/trabalho_final/Raio.cpp $(SRC_DIR)/trabalho_final/Menu.cpp ../include/imgui/imgui.cpp ../include/imgui/imgui_demo.cpp ../include/imgui/imgui_draw.cpp ../include/imgui/imgui_impl_glfw.cpp ../include/imgui/imgui_impl_opengl3.cpp ../include/imgui/imgui_tables.cpp ../include/imgui/imgui_widgets.cpp $(GLAD_SRC)
	@echo "Compilando Trabalho Final..."
	$(CXX) $(CXXFLAGS) -I../src/trabalho_final/include $^ $(LDFLAGS) -o trabalho_final

# Executar trabalho final
run: trabalho_final
	@echo "Executando Trabalho Final..."
	./trabalho_final

# Limpeza (compatível com Windows)
clean:
	@echo "Limpando arquivos compilados..."
	-del /Q trabalho_final.exe 2>nul || true
	-rm -f trabalho_final 2>/dev/null || true

# Ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make all     - Compila trabalho final"
	@echo "  make         - Compila trabalho final (padrão)"
	@echo "  make run     - Compila e executa trabalho final"
	@echo "  make clean   - Remove arquivos compilados"
	@echo "  make help    - Mostra esta ajuda"

.PHONY: all clean help run_1 run_2 run_3 tarefa_1 tarefa_2 tarefa_3