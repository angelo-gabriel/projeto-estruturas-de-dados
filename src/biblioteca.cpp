#include "biblioteca.hpp"
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>

// Função auxiliar para gerar 10.000 livros fictícios
std::vector<Livro> gerarAcervoFicticio(int quantidade) {
    std::vector<Livro> acervo;
    acervo.reserve(quantidade);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribCodigo(100000, 999999);

    for (int i = 0; i < quantidade; ++i) {
        Livro livro;
        livro.codigo = distribCodigo(gen);

        // Gerando títulos e autores fictícios baseados no ID
        std::stringstream ssTitulo, ssAutor;
        ssTitulo << "O Misterio de " << (i + 1);
        ssAutor << "Autor Exemplo " << (i % 500);

        livro.titulo = ssTitulo.str();
        livro.autor = ssAutor.str();

        acervo.push_back(livro);
    }
    return acervo;
}

void exemploBuscaLivroCodigo() {
    std::cout << "\n--- [Exemplo 1] Busca de livro por Codigo ---\n";
    const int tamanho = 10000;
    const int repeticoes = 100000;
    std::vector<Livro> acervo = gerarAcervoFicticio(tamanho);
    std::unordered_map<int, Livro> mapaAcervo;

    // Preenchendo o Hash Map para busca por chave única
    for (const auto &livro : acervo) {
        mapaAcervo[livro.codigo] = livro;
    }

    int codigoProcurado = acervo[7500].codigo;

    // --- 1. Busca Linear (std::find_if) ---
    auto inicioLinear = std::chrono::high_resolution_clock::now();
    for (int r = 0; r < repeticoes; ++r) {
        volatile auto it = std::find_if(acervo.begin(), acervo.end(),
                                        [codigoProcurado](const Livro &l) {
                                            return l.codigo == codigoProcurado;
                                        });
        (void)it;
    }
    auto fimLinear = std::chrono::high_resolution_clock::now();
    auto tempoLinear =
        std::chrono::duration<double, std::milli>(fimLinear - inicioLinear);

    // --- 2. Busca por Chave Única (Hash Map) ---
    auto inicioHash = std::chrono::high_resolution_clock::now();
    for (int r = 0; r < repeticoes; ++r) {
        volatile auto busca = mapaAcervo.find(codigoProcurado);
        (void)busca;
    }
    auto fimHash = std::chrono::high_resolution_clock::now();
    auto tempoHash =
        std::chrono::duration<double, std::milli>(fimHash - inicioHash);

    // Exibindo resultados
    std::cout << "Livro buscado com codigo ID: " << codigoProcurado << "\n";
    std::cout << "  - Tempo Busca Linear (vetor): " << tempoLinear.count()
              << " ms\n";
    std::cout << "  - Tempo Chave Unica (Hash Map): " << tempoHash.count()
              << " ms\n";
    std::cout
        << "  (O Hash Map e exponencialmente mais rapido em buscas por ID!)\n";
}

void exemploOrdenarAcervoTitulo() {
    std::cout
        << "\n--- [Biblioteca] Ordenacao Alfabetica do Acervo por Titulo ---\n";
    const int tamanho = 10000;
    std::vector<Livro> acervo = gerarAcervoFicticio(tamanho);

    std::cout
        << "Acervo gerado. Exemplo de titulo antes da ordenacao (indice 0): "
        << acervo[0].titulo << "\n";

    // Cronometra a ordenação alfabética utilizando std::sort com uma expressão
    // lambda
    auto inicio = std::chrono::high_resolution_clock::now();
    std::sort(acervo.begin(), acervo.end(), [](const Livro &a, const Livro &b) {
        return a.titulo < b.titulo;
    });
    auto fim = std::chrono::high_resolution_clock::now();
    auto duracao = std::chrono::duration<double, std::milli>(fim - inicio);

    std::cout << "Acervo ordenado com sucesso em " << duracao.count()
              << " ms!\n\n";

    // Exibindo os primeiros 5 livros ordenados alfabeticamente
    std::cout << "--- Primeiros 5 livros do acervo (Ordem Alfabetica) ---\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "ID: " << acervo[i].codigo
                  << " | Titulo: " << acervo[i].titulo << "\n";
    }

    // Exibindo os últimos 5 livros ordenados alfabeticamente
    std::cout << "\n--- Ultimos 5 livros do acervo (Ordem Alfabetica) ---\n";
    for (int i = tamanho - 5; i < tamanho; ++i) {
        std::cout << "ID: " << acervo[i].codigo
                  << " | Titulo: " << acervo[i].titulo << "\n";
    }
}

// Reservas com ordem de chegada
void exemploAtendimento() {
    // Criando a fila de reservas
    std::queue<Reserva> reservas;

    // Variável que representa um id sequencial
    std::uint64_t contador = 0;

    reservas.push({"Angelo", contador++});
    reservas.push({"Maria", contador++});
    reservas.push({"Pedro", contador++});
    reservas.push({"Joao", contador++});

    std::cout << '\n';
    while (!reservas.empty()) {
        const Reserva &proxima = reservas.front();

        std::cout << proxima.usuario << " - Ordem: " << proxima.ordem << '\n';

        reservas.pop();
    }
}

// Reservas com critério de prioridade
void exemploAtendimentoPrioridade() {
    std::priority_queue<ReservaPrioridade, std::vector<ReservaPrioridade>,
                        Comparador>
        reservasPrioridade;

    reservasPrioridade.push({"Angelo", 2, 1});
    reservasPrioridade.push({"Joao", 1, 2});
    reservasPrioridade.push({"Maria", 2, 3});
    reservasPrioridade.push({"Pedro", 1, 4});

    std::cout << '\n';
    while (!reservasPrioridade.empty()) {
        const ReservaPrioridade &prox = reservasPrioridade.top();

        std::cout << prox.usuario << " - Prioridade: " << prox.prioridade
                  << " - Ordem: " << prox.ordem << '\n';

        reservasPrioridade.pop();
    }
}

void exemploDesfazer() {
    // Aqui, utiliza-se a estrutura 'stack', para implementar o principio LIFO
    std::stack<Reserva> pilha;

    std::uint64_t contador = 0;

    pilha.push({"Angelo", contador++});
    pilha.push({"Jose", contador++});
    pilha.push({"Mateus", contador++});
    pilha.push({"Ezequiel", contador++});
    pilha.push({"Pessoa", contador++});

    // Retirando a reserva do topo da pilha
    std::cout << "\nPrimeira reserva a ser desfeita: " << pilha.top().usuario
              << '\n';
    pilha.pop();

    std::cout << "Proxima reserva: " << pilha.top().usuario << '\n';
    std::cout << "Quantidade de reservas: " << pilha.size() << '\n';
    std::cout << "A pilha esta vazia? " << pilha.empty() << '\n';
}