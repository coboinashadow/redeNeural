fs=require('fs');

imagens=120; //qtd de imagens para treinar
amostra=new Array(imagens).fill(0);

bias=Math.random(); //inicializa bias aleatório

for(i=0;i<imagens;i++){
	buf=fs.readFileSync(`imagens/amostra${i.toString().padStart(4, '0')}.bmp`);
	soma=0;
	for(j=54;j<buf.length;j++)soma += buf[j];
	amostra[i]=soma; //gera um 'weight' que representa a imagem
}

for(x=0;x<200000;x++){ //ajusta o bias centenas de vezes
	alguma=parseInt(Math.random()*imagens); //uma imagem qualquer

	//ajusta o bias pouco a pouco
	if(amostra[alguma]>bias)bias+=bias*0.00008; //um pouco a mais
	if(amostra[alguma]<bias)bias-=bias*0.00008; //um pouco a menos

	console.log(`biasfinal = ${bias.toFixed(6)}`);
}
//salva o bias no arquivo
fs.writeFileSync('bias2.txt',`${bias}\n`,'utf-8');

console.log("\nTreinamento finalizado. Pesos salvos em 'bias2.txt'")
