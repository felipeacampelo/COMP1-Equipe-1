---
layout: default
title: Exemplos de Código
---

# Exemplos de Código

Esta página mostra exemplos alinhados com a gramática atual.

## Exemplos aceitos hoje

### Impressão numérica

```python
x = 10
print(x)
```

### Atribuição de Variável

```python
x = 10
z = x + 2
print(z)
```

### Expressão aritmética

```python
a = 3 + 4 * 2
print(a)
```

## Fluxo de Controle

### Comando If

```python
x = 10
if (x > 5):
    print(x)
```

### Loop While

```python
i = 0
while (i < 10):
    print(i)
```

### Bloco com múltiplos comandos

```python
x = 10
if (x > 5):
    print(x)
    print(x)
```

## Importações

### Importação básica

```python
import numpy
```

### Importação com alias

```python
import numpy as np
```

### Importação `from`

```python
from math import sqrt
```

### Importação `from` com alias

```python
from math import sqrt as square_root
```

## Observações importantes

- Cada comando deve terminar em nova linha.
- Blocos usam indentação.
- `if` e `while` aceitam múltiplos comandos no corpo.
- `input`, declarações tipadas e atribuições compostas ainda não fazem parte da gramática atual.

## Ainda não aceitos pelo parser atual

### Exemplo com `input`

```python
n = int(input())
```

### Exemplo com divisão inteira

```python
n //= 2
```

Esses casos ajudam a testar o que já foi tokenizado, mas ainda não tem regra completa no parser.

## Executando Exemplos

Para testar um exemplo compatível:

```bash
# Salvar em arquivo
cat > test.py << 'EOF'
n = 5
print(n)
EOF

# Executar com o compilador
./compiladorpj test.py
```

## Adicionando Novos Exemplos

Para adicionar um novo exemplo compatível:

1. Crie um arquivo `.py` no diretório `src/`
2. Siga a gramática suportada
3. Teste com `make all && ./compiladorpj src/seu_exemplo.py`

## Limitações

- Funciona apenas com o subconjunto listado acima.
- A tabela de símbolos ainda não foi implementada.
- A análise semântica ainda não foi implementada.
- O suporte a tipos, strings e operadores compostos ainda está incompleto.
