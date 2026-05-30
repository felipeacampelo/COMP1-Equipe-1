# 1. Operacoes Basicas e Atribuicoes
x = 10
y = 20
soma = x + y
conta = x * 2 - 10 / y

# 2. Comandos aninhados (If dentro de If) testando INDENT/DEDENT
if (x > 5):
    print(x)
    if (y == 20):
        print(y)
        x = x + 1

# 3. Laco While tradicional
contador = 0
while (contador < 3):
    contador = contador + 1
    print(contador)

# 4. O FOR com RANGE que acabamos de criar!
for i in range(0, 5):
    print(i)
    if (i > 2):
        print(x)

# 5. Teste de Imports (todas as variacoes do seu Bison)
import math
import numpy as np
from utils import helper
from system import time as t

# ---------------------------------------------------------
# 6. ERROS INTENCIONAIS (O Teste de Fogo da Recuperacao)
# O compilador DEVE acusar erro nessas linhas, mas NAO PODE travar!
# ---------------------------------------------------------

10 = x                 # Erro: Numero nao pode receber atribuicao
if x > 5:              # Erro: Faltam os parenteses () do seu IF
while (x > 0)          # Erro: Falta os dois pontos : no final
x = 10 + * 5           # Erro: Dois operadores matematicos juntos
print (                # Erro: Expressao incompleta (falta fechar parenteses)

# ---------------------------------------------------------
# 7. Teste de Sobrevivencia
# Se a recuperacao de erro funcionou, a arvore DEVE registrar isso aqui:
# ---------------------------------------------------------
sobreviveu = 999
print(sobreviveu)