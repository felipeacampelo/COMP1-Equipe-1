# 1. O ERRO SEMANTICO (A nossa estrela da Tabela Hash)
# Criamos a variavel nota, mas tentamos somar com a variavel 'bonus' que nao existe.
nota = 10
media = nota + bonus

# 2. O ERRO SINTATICO (Recuperacao de Erro do Modo Panico)
# O compilador vai pular essa linha porque a nossa regra exige parenteses: if (nota > 5):
if nota > 5:
    print(nota)

# Como o modo panico protegeu a arvore no erro acima, esta linha final compila normal:
final = 100