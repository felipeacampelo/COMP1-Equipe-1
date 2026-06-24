
 Codigo Intermediario - (TAC) 
	n = 5
L1:
	t1 = n > 0
	If(False) t1 JMP L2
	print n
	t2 = n - 1
	n = t2
	JMP L1
L2:

 Codigo Intermediario gerado com sucesso em compilador.tac
