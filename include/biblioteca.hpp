#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP

#include <cstdint>
#include <string>

// Estrutura representando um livro no acervo
struct Livro {
    int codigo;
    std::string titulo;
    std::string autor;
};

// Estrutura que representa uma reserva
struct Reserva {
    std::string usuario;
    std::uint64_t ordem;
};

// Mesma estrutura, porém com a prioridade
struct ReservaPrioridade {
    std::string usuario;
    int prioridade;
    std::uint64_t ordem;
};

// Estrutura auxiliar para a implementação com priority queue
struct Comparador {
    bool operator()(const ReservaPrioridade &a,
                    const ReservaPrioridade &b) const {
        if (a.prioridade != b.prioridade)
            return a.prioridade > b.prioridade;
        return a.ordem > b.ordem;
    }
};

// D1. Busca
void exemploBuscaLivroCodigo();

// D2. Listagem
void exemploOrdenarAcervoTitulo();

// D3. Atendimento
void exemploAtendimento();

// D3. Atendimento (com prioridade)
void exemploAtendimentoPrioridade();

// D4. Desfazer
void exemploDesfazer();

// D5. Relacao
void exemploRelacao();

#endif