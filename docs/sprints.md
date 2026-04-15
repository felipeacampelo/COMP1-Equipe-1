---
layout: default
title: Sprints
---

# Planejamento das Sprints

O projeto está organizado em sprints semanais para acompanhar a evolução da disciplina e manter a documentação alinhada ao que foi realmente implementado.

## Modelo de registro

Cada sprint pode ser documentada com os seguintes campos:

- objetivo da sprint;
- entregas previstas;
- o que foi implementado;
- pendências;
- problemas encontrados;
- soluções adotadas;
- próximo passo.

## Sprint 1 - Definição do projeto e base inicial

### Objetivo
Definir o projeto, organizar o repositório e preparar o ambiente de desenvolvimento.

### Entregas
- repositório criado;
- estrutura inicial de diretórios;
- definição do compilador como projeto central;
- documentação inicial da proposta.

### Resultado esperado
Uma base organizada para começar a implementação do analisador léxico.

## Sprint 2 - Analisador léxico

### Objetivo
Implementar o lexer com os primeiros tokens da linguagem.

### Entregas
- arquivo Flex com regras de tokens;
- reconhecimento de palavras-chave, identificadores, números e símbolos básicos;
- comentários e espaços em branco tratados;
- primeiros exemplos de entrada.

### Resultado esperado
Entrada textual convertida em fluxo de tokens compreensível pelo parser.

## Sprint 3 - Parser inicial

### Objetivo
Criar a primeira versão do parser e integrá-lo ao lexer.

### Entregas
- gramática inicial em Bison;
- regras para expressões e comandos simples;
- integração scanner + parser;
- testes de sintaxe básicos.

### Resultado esperado
Reconhecer um subconjunto pequeno da linguagem sem depender de geração de código.

## Sprint 4 - Expansão da gramática e erros sintáticos

### Objetivo
Aumentar a cobertura sintática e melhorar a resposta a erros.

### Entregas
- novas regras gramaticais;
- tratamento inicial de erro sintático;
- revisão dos exemplos válidos e inválidos;
- alinhamento entre documentação e implementação.

### Resultado esperado
Um parser mais estável e uma documentação mais fiel ao estado real do projeto.

## Sprint 5 - Consolidação para o P1

### Objetivo
Consolidar a base do projeto para a apresentação do primeiro ponto de controle.

### Entregas
- visão geral do projeto;
- documentação das sprints;
- exemplos de uso compatíveis;
- lista clara de limitações;
- alinhamento do escopo para a próxima fase.

### Resultado esperado
O repositório apresentar claramente o que foi feito até aqui e qual será o próximo passo.

## Depois do P1

Após a primeira entrega, o projeto deve avançar para:

- análise semântica;
- tabela de símbolos;
- construção de AST;
- geração de código intermediário;
- geração final em Java.

## Observação

O cronograma abaixo não substitui o planejamento da equipe, mas serve como base para o acompanhamento da evolução do projeto ao longo do semestre.
