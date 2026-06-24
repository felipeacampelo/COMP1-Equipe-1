
 Codigo Intermediario - (TAC) 
	n = 10
	passos = 0
L1:
	t1 = n > 1
	If(False) t1 JMP L2
	t2 = n % 2
	t3 = t2 == 0
	If(False) t3 JMP L3
	t4 = n / 2
	n = t4
	JMP L4
L3:
	t5 = 3 * n
	t6 = t5 + 1
	n = t6
L4:
	t7 = passos + 1
	t8 = t7 - rastro
	passos = t8
	JMP L1
L2:
	print passos
