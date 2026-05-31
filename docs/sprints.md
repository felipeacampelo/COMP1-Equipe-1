---
layout: default
title: Sprints
---

# Planejamento das Sprints

O projeto está organizado em sprints semanais para acompanhar a evolução da disciplina e manter a documentação alinhada ao que foi realmente implementado.

## Modelo de registro

Cada sprint é documentada com os seguintes campos:

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

## Sprint 4 - Consolidação sintática

### Objetivo
Ampliar a gramática para blocos indentados e melhorar a integração entre lexer e parser.

### Entregas
- suporte a `INDENT`, `DEDENT` e `NEWLINE`;
- blocos com múltiplos comandos;
- refinamento de expressões e de controle de fluxo;
- revisão da documentação técnica.

### Resultado esperado
Uma base sintática mais próxima da estrutura de um subconjunto real de Python.

## Sprint 5 - Estruturação da AST e tabela de símbolos

### Objetivo
Adicionar uma representação intermediária para que o compilador deixe de apenas validar a entrada e preparar a base da análise semântica.

### Entregas
- definição dos tipos de nós da AST;
- funções de criação de nós;
- integração do parser com a árvore;
- visualização da árvore no terminal;
- estrutura da tabela de símbolos.

### Resultado esperado
Representar programas aceitos pelo parser em uma estrutura navegável e preparar o compilador para validações semânticas posteriores.

## Sprint 6 - Próximos passos

### Objetivo
Preparar a evolução do compilador para além da sintaxe.

### Entregas previstas
- análise semântica;
- verificação de tipos;
- tradução mais completa para Java.

### Resultado esperado
Uma arquitetura capaz de evoluir de parser com AST para compilador com validação semântica e saída mais robusta.
