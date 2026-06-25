# Compilador para Subconjunto de Python

Este projeto implementa um compilador para um subconjunto de Python usando Flex e Bison. O fluxo atual do projeto faz:

- análise léxica
- análise sintática
- análise semântica mínima
- geração de código intermediário (TAC)
- geração de código final em Java (`Main.java`)

## Você também pode ver a documentação do GitPages
```bash
https://felipeacampelo.github.io/COMP1-Equipe-1/
```

## Como compilar

Primeiro, garanta que o ambiente tenha:

- `make`
- `gcc`
- `flex`
- `bison`

Em muitos ambientes Linux, basta compilar com:

```bash
make all
```

Se a biblioteca `libfl` não estiver no caminho padrão do linker, ajuste o ambiente antes da compilação.

Exemplo comum no macOS com Flex instalado via Homebrew:

```bash
LIBRARY_PATH=/opt/homebrew/opt/flex/lib make all
```

O executável gerado será:

```bash
./compiladorpj
```

## Como executar

Para compilar um arquivo de entrada:

```bash
./compiladorpj caminho/do/arquivo.py
```

Exemplo:

```bash
./compiladorpj exemplos/01_fluxo_inteiros.py
```

Ao executar, o compilador:

- mostra a árvore sintática
- gera o código intermediário (TAC)
- gera o arquivo `Main.java` quando não há erro semântico

## Como gerar Java

Depois de rodar o compilador com um arquivo válido:

```bash
./compiladorpj exemplos/01_fluxo_inteiros.py
```

o arquivo abaixo será gerado na raiz do projeto:

```bash
Main.java
```

## Como compilar e executar o Java gerado

Com um JDK funcional instalado:

```bash
javac Main.java
java Main
```

## Exemplos prontos

Os exemplos finais de apresentação estão em:

```bash
exemplos/
```

Arquivos disponíveis:

- `01_fluxo_inteiros.py`
- `02_fluxo_float.py`
- `03_erro_semantico.py`
- `04_erro_sintatico.py`
