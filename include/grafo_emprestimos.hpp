#ifndef GRAFO_EMPRESTIMOS_HPP
#define GRAFO_EMPRESTIMOS_HPP

#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

// Estruturas para o grafo do exemplo D6
struct ArestaEmprestimo {
    std::string livroId;
    std::string dataEmprestimo;
};

struct NoLivro {
    std::string id;
    std::string titulo;
    bool disponivel = true;
    std::queue<std::string> filaReservas; // Ordem de reserva do livro
};

// Classe que representa os emprestimos
class GrafoEmprestimos {
  private:
    std::unordered_map<std::string, std::string> usuarios;
    std::unordered_map<std::string, NoLivro> livros;
    std::unordered_map<std::string, std::vector<ArestaEmprestimo>> adj;

  public:
    void adicionarUsuario(const std::string &id, const std::string &nome);
    void adicionarLivro(const std::string &id, const std::string &titulo);

    bool emprestarOuReservar(const std::string &usuarioId,
                             const std::string &livroId,
                             const std::string &data);

    void devolverLivro(const std::string &usuarioId, const std::string &livroId,
                       const std::string &dataDevolucao);

    void imprimirEstadoGrafo() const;
};

#endif