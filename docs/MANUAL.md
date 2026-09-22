# Manual de utilização

Este guia percorre a aplicação do início ao fim com um exemplo: registar uma pessoa, atribuir-lhe um portátil, mandá-lo para manutenção e consultar o histórico.

A aplicação funciona por menus numerados. Escreve-se o número da opção e carrega-se em Enter. Sempre que um valor está fora do intervalo aceite, a pergunta repete-se.

## Menu principal

| Opção | O que faz |
|---|---|
| 1 – Manage Equipment | criar, editar, remover e registar manutenções |
| 2 – Manage Users | criar, editar e remover utilizadores |
| 3 – View Lists | listagens obrigatórias e histórico de manutenções |
| 4 – Search Equipment | pesquisa por estado + data, ou por nome |
| 5 – View Additional Information | resumo das regras da aplicação |
| 6 – Save Data Now | grava os dados sem sair |
| 0 – Save And Exit | grava e termina |

Os dados ficam na pasta a partir da qual a aplicação foi executada (`users.bin`, `equipment.bin` e `logs.txt`).

## 1. Criar um utilizador

`2 – Manage Users` → `1 – Create User`

1. Sigla: `FMO` (tem de ser única)
2. Nome: `Francisco Oliveira`
3. Função: `Programador`

O utilizador fica ativo e recebe o próximo código disponível (o primeiro é o 1).

## 2. Registar um equipamento

`1 – Manage Equipment` → `1 – Create Equipment`

1. Nome: `Portátil Dell XPS` (não pode repetir o de outro equipamento)
2. Categoria: escolher o número da lista (por exemplo `3 – Laptop`)
3. Data de aquisição: dia, mês e ano. Datas inexistentes (31/04) ou futuras são recusadas.
4. Associar a um utilizador? `y` e depois a posição do utilizador na lista apresentada.

O equipamento começa sempre no estado **Operational**.

## 3. Mudar o estado e registar manutenções

Só é possível registar manutenções em equipamentos **Under maintenance**.

1. `1 – Manage Equipment` → `2 – Edit Equipment`, indicar o ID, escolher o estado `2 – Under maintenance` e, na pergunta seguinte, `0` para manter o utilizador (ou `-1` para o desassociar).
2. `4 – Maintain Equipment`, indicar o ID e preencher: número de movimento (único em toda a aplicação), data, tipo (ex.: `Atualização de software`) e notas.

Pode registar-se as manutenções que forem precisas; a memória cresce automaticamente.

## 4. Consultar informação

`3 – View Lists`:

- **List Free Equipment** – equipamentos sem utilizador, agrupados por categoria;
- **List Equipment For Recycling** – o que está marcado para reciclagem;
- **List Equipment Maintenance History By Date** – escolhe-se o equipamento pela posição na lista e as manutenções aparecem da mais antiga para a mais recente.

`4 – Search Equipment`:

- **por estado e data de aquisição** – devolve os equipamentos que coincidem nos dois critérios;
- **por nome** – basta parte do nome, sem distinguir maiúsculas e minúsculas (`dell` encontra `Portátil Dell XPS`).

Equipamentos para reciclagem nunca aparecem nas pesquisas.

## 5. Reciclar e remover

1. Editar o equipamento e escolher o estado `4 – For recycling`. O utilizador associado é retirado automaticamente e o estado deixa de poder ser alterado.
2. `3 – Remove Equipment` com o ID do equipamento. Todo o histórico de manutenções é apagado com ele.

## 6. Remover ou inativar utilizadores

- Um utilizador sem equipamentos pode ser removido.
- Se tiver equipamentos, a aplicação propõe inativá-lo. Um utilizador inativo perde os equipamentos que tinha e deixa de poder receber novos, mas pode voltar a ser ativado na edição.
- Utilizadores inativos não podem ser removidos.

## Perguntas frequentes

**Fechei a janela sem sair pelo menu. Perdi os dados?**
Perde-se o que foi feito desde a última gravação. Use a opção 6 para gravar a meio.

**Posso copiar os ficheiros `.bin` para outro computador?**
Sim, desde que o programa tenha sido compilado para o mesmo tipo de sistema (ver "Limitações" no README).
