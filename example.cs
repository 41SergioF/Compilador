START_PROG

	var variaveis:Flw[3]
	var aux:Flw

	Outs(">> Vamos resolver a formula de Baskara <<")

	Outs("Entre com o valor de 'A':")
	
	Imp(aux)
	variaveis[0] = aux
	Outs("Entre com o valor de 'B':")
	Imp(aux)
	variaveis[1] = aux
	Outs("Entre com o valor de 'C':")
	Imp(aux)
	variaveis[2] = aux

	var delta:Flw
	delta = (variaveis[1]**2)-(4*variaveis[0]*variaveis[2])
	Out(delta, Flw)

	if (delta < 0.0){
		Outs("O delta e menor que 0")
	}else{
		var x1:Flw
		var x2:Flw

		x1 = (-variaveis[1]+delta)/(2*variaveis[0])
		x2 = (-variaveis[1]+delta)/(2*variaveis[0])

		Outs("X linha")
		Out(x1, Flw)
		Outs("X duas linhas")
		Out(x2, Flw)
	}

END_PROG