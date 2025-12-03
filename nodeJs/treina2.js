fs=require('fs');

inputs=[]
target=[]
//busca os valores no arquivo entradas2.txt
a=JSON.parse(fs.readFileSync('entradas2.txt','utf-8'));
for(x=0;x<30;x++){
	inputs[x]=[a[x].idade,a[x].temperatura,a[x].consistencia,a[x].textura,a[x].posicao,a[x].cor,a[x].volume,a[x].peso];
	target[x]=(a[x].especie=='l')?1.0:0.0;
}

//inicialização das estruturas de dados
weights=new Array(8);
bias=0.0;

//inicializa os weights com valores aleatorios
for(h=0;h<8;h++)weights[h]=Math.random();

for(x=0;x<100000;x++){ //ajusta os bias centenas de vezes
	total_erros=0;

	for(i=0;i<100;i++){
		alguma=parseInt(Math.random()*30);
		somatorio=bias;
		for(h=0;h<8;h++)somatorio+=weights[h]*inputs[alguma][h]; //para as 8 caracteristicas

		degrau=somatorio>=0.0?1.0:0.0;
		erro=target[alguma]-degrau;

		if(erro!=0.0){
			total_erros++;
			for(h=0;h<8;h++)weights[h]+=0.000002*erro*inputs[alguma][h];
			bias+=0.000002*erro;
		}
	}

	console.log(`${100000-x} biasfinal = ${bias.toFixed(6)}`);

	if(x%5000==0&&total_erros==0)break; //o bias foi encontrado
}

//salva os bias e weights
data=[weights,bias];
fs.writeFileSync('bias1.txt',JSON.stringify(data),'utf-8');

console.log("\nTreinamento finalizado. Pesos salvos em 'bias1.txt'")
