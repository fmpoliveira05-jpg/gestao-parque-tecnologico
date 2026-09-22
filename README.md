# Gestão de Parque Tecnológico

Aplicação de consola em C para gerir o inventário de equipamentos informáticos de uma organização: quem tem o quê, em que estado está cada equipamento e que manutenções já levou.

Foi o trabalho prático individual da unidade curricular de **Laboratório de Programação** (1.º ano da Licenciatura em Engenharia Informática, ESTG – Politécnico do Porto, 2023/24). Em 2026 voltei a pegar no código para corrigir erros que só mais tarde percebi que existiam, organizar melhor o projeto e acrescentar testes.

[![CI](https://github.com/fmpoliveira05-jpg/gestao-parque-tecnologico/actions/workflows/ci.yml/badge.svg)](https://github.com/fmpoliveira05-jpg/gestao-parque-tecnologico/actions/workflows/ci.yml)

## O problema

O enunciado pedia uma aplicação para acompanhar o parque tecnológico de uma empresa. Em resumo:

- cada equipamento tem um identificador sequencial, designação, categoria (impressora, portátil, router, …), data de aquisição, estado e, opcionalmente, um utilizador a quem está atribuído;
- cada equipamento guarda o seu histórico de manutenções (número de movimento único, data, tipo e notas);
- os utilizadores têm código, sigla, nome, função e estado (ativo/inativo); um utilizador com equipamentos não pode ser removido, só inativado;
- equipamentos "para reciclagem" não podem ter utilizador, não aparecem nas listagens normais e são os únicos que podem ser eliminados;
- os dados têm de persistir em ficheiro e a memória tem de ser gerida de forma dinâmica.

## O que a aplicação faz

- **Equipamentos** – criar, alterar estado/utilizador, registar manutenções e remover (só os que estão para reciclagem).
- **Utilizadores** – criar, editar e remover, respeitando as regras acima.
- **Listagens** – equipamentos livres agrupados por categoria, equipamentos para reciclagem e histórico de manutenções de um equipamento por ordem cronológica.
- **Pesquisas** – por estado e data de aquisição, ou por parte do nome (sem distinguir maiúsculas de minúsculas).
- **Persistência** – os dados ficam em `equipment.bin` e `users.bin`; é possível guardar a qualquer momento ou ao sair. As opções escolhidas nos menus ficam registadas em `logs.txt`.

A interface está em inglês, tal como o código.

## Como compilar e executar

É preciso um compilador de C (GCC ou Clang) e o `make`. Em Windows, a forma mais simples é usar o WSL ou o MSYS2.

```bash
git clone https://github.com/fmpoliveira05-jpg/gestao-parque-tecnologico.git
cd gestao-parque-tecnologico
make          # compila para bin/parque-tecnologico
make run      # compila e arranca a aplicação
```

Na primeira execução não existem ficheiros de dados; a aplicação começa com as listas vazias e cria-os quando guardar.

O [manual de utilização](docs/MANUAL.md) explica cada menu com um exemplo completo.

## Testes

```bash
make test       # testes unitários
make memcheck   # os mesmos testes, a correr no Valgrind (Linux)
```

Os testes cobrem a parte que não depende do teclado: validação e comparação de datas, critérios de pesquisa, cálculo do maior identificador e o ciclo guardar → carregar dos ficheiros binários (incluindo um equipamento com mais manutenções do que a capacidade inicial, que era precisamente o caso que rebentava). O GitHub Actions compila com `-Werror` e corre os testes e o Valgrind em cada *push*.

## Estrutura

```
include/            cabeçalhos (tipos de dados, constantes e documentação Doxygen)
src/
  main.c            menu principal
  equipment.c       criar, editar, manter e remover equipamentos
  users.c           gestão de utilizadores
  lists.c           listagens e formatação da informação no ecrã
  search.c          critérios de pesquisa
  date.c            validação, comparação e leitura de datas
  input.c           leitura segura do teclado
  memory_and_files.c  memória dinâmica e persistência em ficheiro
tests/              testes unitários
docs/               Doxyfile e manual de utilização
```

A documentação técnica gera-se com `make docs` (é preciso ter o Doxygen instalado) e fica em `docs/html/index.html`.

## O que mudou na revisão de 2026

A versão entregue funcionava nas demonstrações, mas tinha problemas que apareciam com dados reais:

- **Falha ao arrancar sem dados** – com os ficheiros vazios, o contador era lido sem verificar o `fread` e o programa podia tentar alocar um valor aleatório. Agora a ausência de dados é tratada como primeira utilização.
- ***Buffer overflow* nas manutenções** – ao registar uma manutenção só se aumentava a capacidade do *primeiro* equipamento da lista, e ao carregar do ficheiro só se reservavam 3 posições. Um equipamento com mais de 3 manutenções escrevia fora da memória.
- **Fugas de memória** – os históricos de manutenção nunca eram libertados no fim.
- **Identificador máximo** – a função que o calculava lia uma posição a mais do vetor e falhava quando os IDs não estavam por ordem.
- **Regras de negócio** – era possível ficar com duas siglas iguais ao editar um utilizador, inativar um utilizador não lhe retirava os equipamentos e os IDs deixavam de ser sequenciais quando uma inserção falhava.
- **Entrada de dados** – aceitavam-se datas como 31/02 ou datas futuras, e fechar a entrada (Ctrl+D) deixava o programa num ciclo infinito.

Aproveitei também para separar os tipos de dados num cabeçalho próprio, juntar a lógica das datas num módulo, eliminar código repetido na apresentação dos dados, trocar o projeto NetBeans por um `Makefile` simples e acrescentar os testes.

## Limitações conhecidas

- Os ficheiros binários guardam as estruturas tal como estão em memória, por isso não são portáveis entre arquiteturas/compiladores diferentes. Para este contexto foi uma escolha aceitável; numa aplicação real usaria um formato de texto (CSV/JSON) ou uma base de dados.
- Os equipamentos são escolhidos pela posição na listagem em algumas operações e pelo ID noutras, herança da versão original que decidi manter para não alterar o comportamento avaliado.

## Autor

**Francisco Miguel Pereira Oliveira** – [GitHub](https://github.com/fmpoliveira05-jpg)

Distribuído com a licença MIT (ver [LICENSE](LICENSE)).
