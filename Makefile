TARGET = terceira_avaliacao

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I./include -I./src

SRCS = ./src/main.cpp ./src/biblioteca.cpp ./src/grafo_emprestimos.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = ./include/biblioteca.hpp ./include/grafo_emprestimos.hpp

# Evita conflitos caso exista algum arquivo com esses nomes
.PHONY: all clean

all: $(TARGET)

# Regra para linkar os arquivos objeto e gerar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regra genérica para compilar arquivos .cpp em .o
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados (compilação limpa)
clean:
	rm -f $(OBJS) $(TARGET)