---
layout: default
title: Exemplos de Código
---

# Exemplos de Código

Esta página mostra exemplos alinhados com a gramática atual.

## Exemplos aceitos hoje

### Olá Mundo

```python
print("Hello, World!")
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

### Comando If-Else

```python
x = 10

if (x > 15):
    print(x)
else:
    print(0)
```

### Loop While

```python
i = 0

while (i < 10):
    print(i)
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
- Não há indentação obrigatória para blocos.
- O corpo de `if` e `while` é apenas um único `stmt`.
- `for`, `input`, declarações tipadas e atribuições compostas ainda não fazem parte da gramática atual.

## Ainda não aceitos pelo parser atual

### Exemplo com `input`

```python
n = int(input())
```

### Exemplo com laço `for`

```python
for i in range(10):
    print(i)
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
./compilador < test.py
```

## Adicionando Novos Exemplos

Para adicionar um novo exemplo compatível:

1. Crie um arquivo `.py` no diretório `src/`
2. Siga a gramática suportada
3. Teste com `make all && ./compilador < src/seu_exemplo.py`

## Limitações

- Funciona apenas com o subconjunto listado acima.
- Não há suporte a blocos indentados.
- O projeto ainda não gera código Java; neste momento ele só reconhece e valida a estrutura do código de entrada.
