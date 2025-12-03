fs=require('fs');

inputs=[]
target=[]
//busca os valores no arquivo entradas2.txt
a=JSON.parse(fs.readFileSync('entradas2.txt','utf-8'));
for(x=0;x<30;x++){
	inputs[x]=[a[x].idade,a[x].temperatura,a[x].consistencia,a[x].textura,a[x].posicao,a[x].cor,a[x].volume,a[x].peso];
	target[x]=(a[x].especie=='l')?1.0:0.0;
}

//buscando dados no arquivo texto
lidas=JSON.parse(fs.readFileSync('bias1.txt','utf-8'));
weights=lidas[0];
bias=lidas[1];

laranjacerto=0,laranjaerrado=0,qqrcerto=0,qqrerrado=0; //contabilizando acertos e erros

console.log("--- RESULTADO ---\nPara as 30 frutas da base de dados:\n");
for(s=0;s<1000;s++){
	alguma=parseInt(Math.random()*30); //escolhe uma fruta qualquer

	somatorio=0.0;
	for(h=0;h<8;h++)somatorio+=inputs[alguma][h]*weights[h];

	if(target[alguma]>0.5)
		if(somatorio>0)laranjacerto++;
		else laranjaerrado++;
	if(target[alguma]<0.5)
		if(somatorio<0)qqrcerto++;
		else qqrerrado++;
}

console.log("Esperado laranja dado laranja: "+laranjacerto);
console.log("Esperado laranja dado qqr: "+laranjaerrado);
console.log("Esperado qqr dado qqr: "+qqrcerto);
console.log("Esperado qqr dado laranja: "+qqrerrado);
