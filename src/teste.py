# 1. Atribuicoes, Variaveis e Operacoes (+, -, *, >, /)
a = 10
b = 5
c = a + b
d = c * 2
e = d > a

# 2. Comando Print
print(e)

# 3. IF com blocos indentados
if (a > b):
    print(a)

# 4. IF e ELSE de uma linha so (Inline)
if (c > 10): print(c) else: print(a)

# 5. WHILE com bloco indentado
while (a > 0):
    a = a - 1
    print(a)

# 6. FOR loop com bloco indentado (Criando a variavel no loop)
for i in c:
    print(i)

# 7. Regras de Importacao (Ignoradas graciosamente pela AST)
import math
import pandas as pd