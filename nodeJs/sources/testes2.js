fs=require('fs');
path=require('path');

imagens=120;
amostra=new Array(imagens).fill(0);

//contabilizando acertos e erros
circulocerto=0,circuloerrado=0,quadradocerto=0,quadradoerrado=0;

for(i=0;i<imagens;i++){
	buf=fs.readFileSync(`imagens/amostra${i.toString().padStart(4,'0')}.bmp`);
	//BMP header tem 54 bytes
	//imagem 60x60x3
	soma=0;
	for(j=54;j<buf.length;j++)soma+=buf[j];
	amostra[i]=soma;
}

//inicializa o bias com valor buscado do txt
bias=parseFloat(fs.readFileSync('bias2.txt','utf-8'));

for(x=0;x<1000;x++){ //testa centenas de vezes
	img=parseInt(Math.random()*imagens); //uma imagem qualquer

	if(amostra[img]>bias){
		if(img<imagens/2)circulocerto++;
		else circuloerrado++;
	}else{
		if(img>imagens/2)quadradocerto++;
		else quadradoerrado++;
	}
}

console.log(`\n${circulocerto + circuloerrado + quadradocerto + quadradoerrado} tentativas:`);
console.log(`Esperado circulo dado circulo: ${circulocerto}`);
console.log(`Esperado circulo dado quadrado: ${circuloerrado}`);
console.log(`Esperado quadrado dado quadrado: ${quadradocerto}`);
console.log(`Esperado quadrado dado circulo: ${quadradoerrado}\n`);
