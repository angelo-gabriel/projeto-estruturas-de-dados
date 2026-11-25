# Sistema de biblioteca

Projeto integrador para a disciplina de Estruturas de Dados da UNIFSA. Aluno: `Ângelo Gabriel da Silva Assis`

Código de demonstração, desenvolvido em C++17, com exemplos de busca, ordenacão, filas, pilhas, prioridades e empréstimos representados por um grafo.

## Requisitos

- Compilador C++17, como `g++` (GCC) ou `clang++` (Clang).
- GNU Make para usar o `Makefile`.

## Compilar e executar

Na raiz do projeto, compile com:

```sh
make
```

Execute no Linux/macOS:

```sh
./terceira_avaliacao
```

No Windows, com MinGW e GNU Make:

```powershell
make
.\terceira_avaliacao.exe
```

Sem GNU Make, compile diretamente com `g++` (ou substitua pelo compilador disponivel):

```sh
g++ -std=c++17 -Wall -Wextra -O2 -Iinclude src/main.cpp src/biblioteca.cpp src/grafo_emprestimos.cpp -o terceira_avaliacao
```

No Windows, acrescente `.exe` ao nome de saida (`-o terceira_avaliacao.exe`) e execute `.\terceira_avaliacao.exe` no PowerShell. O programa apresenta um menu interativo; digite uma opcao de 1 a 7.

Para remover os arquivos gerados pela compilacao:

```sh
make clean
```

## Arquivos

- `Makefile`: regras para compilar e limpar o projeto.
- `include/biblioteca.hpp`: estruturas de livros e reservas, e declarações dos exemplos da biblioteca.
- `src/biblioteca.cpp`: implementa os exemplos de busca, ordenação, atendimento em filas, prioridades e desfazer reservas.
- `include/grafo_emprestimos.hpp`: declara as estruturas e a classe do grafo de empréstimos.
- `src/grafo_emprestimos.cpp`: implementa cadastro de usuários e livros, empréstimos, reservas, devoluções e exibicão do grafo.
- `src/main.cpp`: exibe o menu e chama os exemplos.
- `.clang-format`: preferências de formatação para ferramentas compatíveis.
