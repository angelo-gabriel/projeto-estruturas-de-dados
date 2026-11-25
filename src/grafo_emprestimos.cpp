#include "grafo_emprestimos.hpp"

#include <algorithm>
#include <iostream>

void GrafoEmprestimos::adicionarUsuario(const std::string &id,
                                        const std::string &nome) {
    usuarios[id] = nome;
}

void GrafoEmprestimos::adicionarLivro(const std::string &id,
                                      const std::string &titulo) {
    livros[id] = NoLivro{id, titulo, true, {}};
}

bool GrafoEmprestimos::emprestarOuReservar(const std::string &usuarioId,
                                           const std::string &livroId,
                                           const std::string &data) {
    if (usuarios.find(usuarioId) == usuarios.end() ||
        livros.find(livroId) == livros.end()) {
        std::cout << "[Erro] Usuario ou livro nao encontrado.\n";
        return false;
    }

    NoLivro &livro = livros[livroId];

    if (livro.disponivel) {
        livro.disponivel = false;
        adj[usuarioId].push_back(ArestaEmprestimo{livroId, data});
        std::cout << "[Emprestimo] " << usuarios[usuarioId] << " pegou \""
                  << livro.titulo << "\" em " << data << ".\n";
        return true;
    }

    livro.filaReservas.push(usuarioId);
    std::cout << "[Reserva] \"" << livro.titulo << "\" indisponivel. "
              << usuarios[usuarioId] << " entrou na fila (posicao "
              << livro.filaReservas.size() << ").\n";
    return false;
}

void GrafoEmprestimos::devolverLivro(const std::string &usuarioId,
                                     const std::string &livroId,
                                     const std::string &dataDevolucao) {
    auto itAdj = adj.find(usuarioId);
    if (itAdj == adj.end()) {
        std::cout << "[Erro] Nenhum emprestimo ativo para esse usuario.\n";
        return;
    }

    auto &arestas = itAdj->second;
    auto itAresta = std::find_if(
        arestas.begin(), arestas.end(),
        [&](const ArestaEmprestimo &a) { return a.livroId == livroId; });

    if (itAresta == arestas.end()) {
        std::cout << "[Erro] Esse usuario nao possui este livro emprestado.\n";
        return;
    }

    arestas.erase(itAresta);
    NoLivro &livro = livros[livroId];
    std::cout << "[Devolucao] " << usuarios[usuarioId] << " devolveu \""
              << livro.titulo << "\" em " << dataDevolucao << ".\n";

    if (!livro.filaReservas.empty()) {
        std::string proximoUsuario = livro.filaReservas.front();
        livro.filaReservas.pop();
        adj[proximoUsuario].push_back(ArestaEmprestimo{livroId, dataDevolucao});
        std::cout << "[Transferencia] Livro repassado automaticamente para "
                     "reserva de "
                  << usuarios[proximoUsuario] << ".\n";
    } else {
        livro.disponivel = true;
    }
}

void GrafoEmprestimos::imprimirEstadoGrafo() const {
    std::cout << "\n=== GRAFO DE EMPRESTIMOS (Usuario -> Livro) ===\n";
    for (const auto &[uId, uNome] : usuarios) {
        std::cout << uNome << " (" << uId << ")";
        auto it = adj.find(uId);
        if (it == adj.end() || it->second.empty()) {
            std::cout << " -> [sem emprestimos ativos]\n";
        } else {
            for (const auto &emp : it->second) {
                std::cout << " -> [" << livros.at(emp.livroId).titulo
                          << " | desde " << emp.dataEmprestimo << "]";
            }
            std::cout << "\n";
        }
    }

    std::cout << "\n=== RESERVAS POR LIVRO ===\n";
    for (const auto &[lId, livro] : livros) {
        std::cout << "\"" << livro.titulo << "\" (" << lId << ") | Status: "
                  << (livro.disponivel ? "Disponivel" : "Emprestado") << "\n";

        if (livro.filaReservas.empty()) {
            std::cout << "   Reservas: nenhuma\n";
        } else {
            std::cout << "   Reservas (ordem de chegada): ";
            std::queue<std::string> copia = livro.filaReservas;
            bool primeiro = true;
            while (!copia.empty()) {
                if (!primeiro)
                    std::cout << " -> ";
                std::cout << usuarios.at(copia.front()) << " (" << copia.front()
                          << ")";
                copia.pop();
                primeiro = false;
            }
            std::cout << "\n";
        }
    }
}