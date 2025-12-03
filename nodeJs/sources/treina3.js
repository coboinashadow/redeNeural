fs=require('fs');

qtdimagens=120; //qtd de qtdimagens para treinar
amostra=new Array(qtdimagens).fill(0); //array de representacao numerica da imagem

bias=Math.random(); //inicializa bias aleatório

for(i=0;i<qtdimagens;i++){
	buf=fs.readFileSync(`imagens/amostra${i.toString().padStart(4,'0')}.bmp`);
	//imagem com 60 linhas 60 colunas 3 bytes por pixel
	for(l=0;l<60;l++)for(x=0;x<60;x++)for(y=0;y<3;y++)
		amostra[i]+=buf[(l*180)+(x*3)+y]; //gera um 'weight' que representa a imagem
}

for(x=0;x<250000;x++){ //ajusta o bias centenas de vezes
	alguma=parseInt(Math.random()*qtdimagens); //uma imagem qualquer

	//ajusta o bias pouco a pouco
	if(amostra[alguma]>bias)bias+=bias*0.00008; //um pouco a mais
	if(amostra[alguma]<bias)bias-=bias*0.00008; //um pouco a menos

	console.log(`biasfinal = ${bias.toFixed(6)}`);
}
//salva o bias no arquivo
fs.writeFileSync('bias2.txt',`${bias}\n`,'utf-8');

console.log("\nTreinamento finalizado. Pesos salvos em 'bias2.txt'")
