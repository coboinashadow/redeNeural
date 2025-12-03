fs=require('fs');

//função que recebe qualquer double e retorna valor entre -1 e 1
function sigmoid(x){return 1.0/(1.0+Math.exp(-x));}

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
weightsfinal=lidas[1];
bias=lidas[2];
biasfinal=lidas[3];

console.log("--- RESULTADO ---\nPara as 30 frutas da base de dados:\n");
for(s=0;s<30;s++){
	hidden=new Array(8);
	for(h=0;h<8;h++){
		hidden[h]=bias[h];
		for(i=0;i<8;i++)hidden[h]+=inputs[s][i]*weights[i][h];
		hidden[h]=sigmoid(hidden[h]);
	}
	output=biasfinal;
	for(h=0;h<8;h++)output+=hidden[h]*weightsfinal[h];
	output=sigmoid(output);
	console.log((s+1)+") Esperado: " + (target[s]>0.98?"Laranja":"Qualquer") + " - Saida: " + (output>0.98?"Laranja":"Qualquer"));
}
