A ASCENSÃO PROPOSICIONAL

---

Membros da Equipe

- Thainá Pontes | @thainapontes
- Michel dos Santos Serpa | @serpamichel
- Lucas Vinicius Oliveira da Silva | @Lucas-Viniicius
- Hugo Vinicius de Lima Mendonça | @BRKHugz
- Luiz Fernando Ramos Toledo | @fernandoToledo69
- Davi Lucas da Silva Pinheiro | @davi081dev

---

- Dados da Disciplina e Instituição

Disciplina: Programação Imperativa e Funcional - 2025.2
Instituição de Ensino: CESAR School

---

- Nome do Jogo Desenvolvido
**PouProsições**

---

- Breve Descrição do Jogo 

Inspirado no mini-game Sky Jump do Pou, nosso  jogo coloca o aluno em uma jornada desesperada para alcançar a Graça Lógica, com ajuda do Professor Guilherme, saltando sobre plataformas. O aluno deve usar seu conhecimento de Proposições Lógicas para garantir que a plataforma não seja uma falácia e evitar a queda. O Professor Diego, personificando o erro e a reprovação, tenta puxar o aluno para o Inferno da Reprovação (o chão). A pontuação é baseada na altura alcançada e no número de perguntas lógicas respondidas corretamente.

---

- Instruções Detalhadas para Compilar e Executar o Jogo

Este tópico detalha o funcionamento do Makefile e fornece as instruções necessárias para compilar e executar o jogo, garantindo que a estrutura modular do projeto em C seja utilizada corretamente.

1. Entendendo o Makefile e a Modularização
O Makefile é um arquivo de texto essencial que automatiza o processo de construção e gerenciamento do programa, utilizando o utilitário make. Em um projeto de Programação Imperativa e Funcional (PIF) com múltiplos arquivos-fonte (jogador.c, plataforma.c, etc.), o Makefile substitui a necessidade de executar comandos longos e complexos do gcc.

Função Principal: O Makefile garante a compilação modular. Ele compila cada arquivo .c de forma isolada em um arquivo objeto (.o) dentro da pasta build/ e, em seguida, linka todos esses arquivos .o em um único executável final (pouproposicoes). Isso otimiza o desenvolvimento, pois se você alterar apenas um módulo (ex: jogador.c), o make recompila apenas o jogador.o correspondente, economizando tempo.

Variáveis Chave:
CFLAGS: Contém as flags de qualidade (-Wall, -Wextra) e o caminho para os arquivos de cabeçalho (-Iinclude).
LDFLAGS: Garante a linkagem com a biblioteca ncurses (-lncurses), que é a base da nossa CLI-lib para manipulação do terminal.

2. Pré-requisitos e Adaptação para Windows

A CLI-lib e a biblioteca ncurses são nativas de ambientes UNIX (Linux/macOS). Para usuários de Windows, a execução deve ser feita em um ambiente que emule o sistema Linux.
Recomendamos fortemente o uso do WSL (Windows Subsystem for Linux) ou o Git Bash para garantir a compatibilidade total com as funções de terminal do jogo.
<img width="655" height="123" alt="image" src="https://github.com/user-attachments/assets/f844881a-dcf1-4b46-8c95-f3567d983a9f" />



