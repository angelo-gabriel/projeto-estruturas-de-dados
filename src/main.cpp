#include "biblioteca.hpp"
#include "grafo_emprestimos.hpp"

#include <iostream>

// Função auxiliar para o exemplo D6
void exemploEmprestimos() {
    GrafoEmprestimos grafo;

    std::cout << '\n';
    grafo.adicionarUsuario("U1", "Ana");
    grafo.adicionarUsuario("U2", "Bruno");
    grafo.adicionarUsuario("U3", "Carla");

    grafo.adicionarLivro("L1", "Clean Code");
    grafo.adicionarLivro("L2", "Estrutura de Dados em C++");

    grafo.emprestarOuReservar("U1", "L1", "2026-11-20");
    grafo.emprestarOuReservar("U2", "L1", "2026-11-21");
    grafo.emprestarOuReservar("U3", "L1", "2026-11-22");
    grafo.emprestarOuReservar("U2", "L2", "2026-11-21");

    grafo.imprimirEstadoGrafo();

    std::cout << "\n--- Simulando devolucao de L1 por Ana ---\n";
    grafo.devolverLivro("U1", "L1", "2026-11-25");
    grafo.imprimirEstadoGrafo();
}

// Menu de console para executar os exemplos
void exibirMenu() {
    int opcao = 0;
    do {
        std::cout << "\n=========================================\n";
        std::cout << "      SISTEMA DE DEMONSTRACAO - C++      \n";
        std::cout << "=========================================\n";
        std::cout << "1. Buscar Livro por Codigo (Linear vs Hash)\n";
        std::cout << "2. Ordenar e exibir acervo por Titulo\n";
        std::cout << "3. Fila de atendimento de usuarios\n";
        std::cout << "4. Fila de atendimento com criterio de prioridade\n";
        std::cout << "5. Desfazer reservas\n";
        std::cout << "6. Consultar e cadastrar emprestimos\n";
        std::cout << "7. Sair\n";
        std::cout << "Escolha uma opcao (1-7): ";
        std::cin >> opcao;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            opcao = 0;
        }

        switch (opcao) {
        case 1:
            exemploBuscaLivroCodigo();
            break;
        case 2:
            exemploOrdenarAcervoTitulo();
            break;
        case 3:
            exemploAtendimento();
            break;
        case 4:
            exemploAtendimentoPrioridade();
            break;
        case 5:
            exemploDesfazer();
            break;
        case 6:
            exemploEmprestimos();
            break;
        case 7:
            std::cout << "\nEncerrando o programa.\n";
            break;
        default:
            std::cout << "\n[ERRO] Opcao invalida.\n";
        }
    } while (opcao != 7);
}

int main() {
    exibirMenu();
    return 0;
}