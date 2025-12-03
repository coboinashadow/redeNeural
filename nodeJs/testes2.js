fs=require('fs');
path=require('path');

qtdimagens=120; //qtd de qtdimagens para treinar
amostra=new Array(qtdimagens).fill(0); //array de representacao numerica da imagem

//contabilizando acertos e erros
circulocerto=0,circuloerrado=0,quadradocerto=0,quadradoerrado=0;

for(i=0;i<qtdimagens;i++){
	buf=fs.readFileSync(`imagens/amostra${i.toString().padStart(4,'0')}.bmp`);
	//imagem com 60 linhas 60 colunas 3 bytes por pixel
	for(l=0;l<60;l++)for(x=0;x<60;x++)for(y=0;y<3;y++)
		amostra[i]+=buf[(l*180)+(x*3)+y]; //gera um 'weight' que representa a imagem
}

//inicializa o bias com valor buscado do txt
bias=parseFloat(fs.readFileSync('bias2.txt','utf-8'));

for(x=0;x<1000;x++){ //testa centenas de vezes
	img=parseInt(Math.random()*qtdimagens); //uma imagem qualquer

	if(amostra[img]>bias){
		if(img<qtdimagens/2)circulocerto++;
		else circuloerrado++;
	}else{
		if(img>qtdimagens/2)quadradocerto++;
		else quadradoerrado++;
	}
}

console.log(`\n${circulocerto + circuloerrado + quadradocerto + quadradoerrado} tentativas:`);
console.log(`Esperado circulo dado circulo: ${circulocerto}`);
console.log(`Esperado circulo dado quadrado: ${circuloerrado}`);
console.log(`Esperado quadrado dado quadrado: ${quadradocerto}`);
console.log(`Esperado quadrado dado circulo: ${quadradoerrado}\n`);
