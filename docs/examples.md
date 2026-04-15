---
layout: default
title: Exemplos de Código
---

# Exemplos de Código

Esta página apresenta programas de exemplo que podem ser analisados pelo compilador COMP1.

## Programas Básicos

### Olá Mundo

```python
print("Hello, World!")
```

### Atribuição de Variável

```python
x = 10
y = 20
z = x + y
print(z)
```

### Entrada do Usuário

```python
n = int(input())
print(n)
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
    i = i + 1
```

## Programas Matemáticos

### Conjetura de Collatz

A Conjetura de Collatz é um famoso problema não resolvido da matemática.

```python
n = int(input())

while(n != 1):
    if n & 1:
        n = 3*n + 1
        print(n)
    else:
        n //= 2
        print(n)
```

**Como funciona:**
1. Comece com qualquer inteiro positivo n
2. Se n é par, divida por 2
3. Se n é ímpar, multiplique por 3 e adicione 1
4. Repita até n se tornar 1

## Exemplos de Importação

### Importação Básica

```python
import numpy
```

### Importação com Alias

```python
import numpy as np
```

### Importação From

```python
from math import sqrt
```

### Importação From com Alias

```python
from math import sqrt as square_root
```

## Exemplos Complexos

Estes exemplos demonstram funcionalidades Python que podem ser alvos para desenvolvimento do compilador:

### Plotagem de Curva Elíptica

```python
import numpy as np
import matplotlib.pyplot as plt

fig, ax = plt.subplots()

x = np.linspace(-10, 10, 1000000)
y = np.sqrt(x**3 - 7*x + 10)
yl = -np.sqrt(x**3 - 7*x + 10)

ax.plot(x, y, color='blue')
ax.plot(x, yl, color='blue')

plt.show()
```

### Parabolóide 3D

```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(-2, 2, 100)
y = np.linspace(-2, 2, 100)

X, Y = np.meshgrid(x, y)
Z = X**2 + Y**2

fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.plot_surface(X, Y, Z, cmap='viridis')

plt.show()
```

## Executando Exemplos

Para testar um exemplo:

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

Para adicionar um novo exemplo:

1. Crie um arquivo `.py` no diretório `src/`
2. Siga a gramática suportada
3. Teste com `make all && ./compilador < src/seu_exemplo.py`

## Limitações

Atualmente suportado:
- ✅ Aritmética básica e comparações
- ✅ Atribuição de variáveis
- ✅ Comandos print
- ✅ Condicionais if/else
- ✅ Loops while
- ✅ Importações
- ✅ Comentários

Ainda não implementado:
- ❌ Definição de funções
- ❌ Definição de classes
- ❌ Literais de lista/dicionário
- ❌ Operações com strings
- ❌ Tratamento de exceções
- ❌ List comprehensions
