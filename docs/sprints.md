---
layout: default
title: Sprints
---

# Planejamento das Sprints

O projeto está organizado em sprints semanais para acompanhar a evolução da disciplina e manter a documentação alinhada ao que foi realmente implementado.

## Modelo de registro

Cada sprint é documentada com os seguintes campos:

- objetivo da sprint;
- entregas;
- resultado esperado para proxima sprint;

## Sprint 1 - Definição do projeto e base inicial

### Objetivo
Definir o projeto, organizar o repositório e preparar o ambiente de desenvolvimento.

### Entregas
- repositório criado;
- estrutura inicial de diretórios;
- definição do compilador;

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

## Sprint 4 - Aprofundamento do parser e lexer

### Objetivo
Adicionar TOKENS e refinar já existentes para analisar o código com mais precisão.

### Entregas
- reconhecimento da indentação como parte da grámatica.
- reconhecimento de mais funções e termos pelo lexer.
- montagem mais precisa da sintatica esperada pelo parser.
- correção de bugs.

### Resultado esperado
Ter os fundamentos preparados para criar a arvore sintatica abstrata.

## Sprint 5 - Criação da AST

### Objetivo
Criar e montar uma arvore sintatica abstrata funcional

### Entregas
- AST criada e funcionando.
- Implementação no parser para registro dos nodes.
- função para imprimir arvore e checar se tudo está como o esperado.

### Resultado esperado
Ter uma estrutura sintatica que organiza a precedência dos operadores e associatividade.

## Sprint 6 - Symtable

### Objetivo
Criar um tabela de símbolos capaz de organizar os indentificadores do código.

### Entregas
- Tabela de símbolos funcional
- Gerador básico de código Java
- Implementação da tabela no parser
- Implementação do Gerador de código Java

### Resultado esperado
Poder gereneciar e verificar a criação de variaveis dentro do código para apontar erros.

## Sprint 7 - Criação do código final

### Objetivo
Organizar e otimizar o código para gerar o código final.

### Entregas
- Geração do código intermediario.
- Criação do arquivo com código final em Java.

### Resultado esperado
Finalizar o nosso projeto com um compilador Python para Java funcional.