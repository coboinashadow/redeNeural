fs=require('fs');

//busca os valores no arquivo e armazena em um array 'dataset'
linhas=fs.readFileSync('entradas1.txt','utf-8').split('\n');
dataset=linhas.map(linha=>{
	[peso,especie]=linha.split(' ');
	return{peso:parseFloat(peso),especie};
});

//inicializa o bias com um valor aleatorio
bias=Math.random(); //valor entre 0 e 1

for(x=0;x<4000;x++){ //ajusta o bias centenas de vezes
	alguma=dataset[parseInt(Math.random()*25)]; //escolhe uma laranja qualquer

	//ajusta o bias pouco a pouco
	if(alguma.peso>bias)bias+=bias*0.01; //ajusta o bias um pouco a mais
	if(alguma.peso<bias)bias-=bias*0.01; //ajusta o bias um pouco a menos
}

console.log(`O valor que diferencia(bias) = ${bias.toFixed(6)}`);
