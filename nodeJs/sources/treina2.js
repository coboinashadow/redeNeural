fs=require('fs');

LEARNING_RATE=0.1

//funcao que recebe qualquer double e retorna valor entre -1 e 1
function sigmoid(x){return 1.0/(1.0+Math.exp(-x));}
//funcao inversa a sigmoide
function dsigmoid(y){return y*(1.0-y);}

inputs=[]
target=[]
//busca os valores no arquivo entradas2.txt
a=JSON.parse(fs.readFileSync('entradas2.txt','utf-8'));
for(x=0;x<30;x++){
	inputs[x]=[a[x].idade,a[x].temperatura,a[x].consistencia,a[x].textura,a[x].posicao,a[x].cor,a[x].volume,a[x].peso];
	target[x]=(a[x].especie=='l')?1.0:0.0;
}

//inicialização das estruturas de dados
weights=Array.from({length:8},()=>new Array(8));
weightsfinal=new Array(8);
bias=new Array(8);

//inicializa os bias com valores aleatorios
for(i=0;i<8;i++)for(h=0;h<8;h++)weights[i][h]=(Math.random()*2)-1;
for(h=0;h<8;h++)weightsfinal[h]=(Math.random()*2)-1;
for(h=0;h<8;h++)bias[h]=(Math.random()*2)-1;
biasfinal=(Math.random()*2)-1;

for(x=0;x<50000;x++){ //ajusta os bias centenas de vezes
	alguma=Math.floor(Math.random()*30); //escolhe uma fruta qualquer

	// --- FORWARD PROPAGATION ---
	hidden=new Array(8);
	for(h=0;h<8;h++){
		hidden[h]=bias[h];
		for(i=0;i<8;i++){
			hidden[h]+=inputs[alguma][i]*weights[i][h];
		}
		hidden[h]=sigmoid(hidden[h]);
	}
	output=biasfinal;
	for(h=0;h<8;h++)output+=hidden[h]*weightsfinal[h];
	output=sigmoid(output);

	// --- BACKPROPAGATION ---
	outputfinal=(target[alguma]-output)*dsigmoid(output);
	hiddenfinal=new Array(8);
	for(h=0;h<8;h++)hiddenfinal[h]=(outputfinal*weightsfinal[h])*dsigmoid(hidden[h]);

	// --- ATUALIZAÇÃO DE PESOS E BIAS ---
	for(h=0;h<8;h++)weightsfinal[h]+=LEARNING_RATE*outputfinal*hidden[h];
	biasfinal+=LEARNING_RATE*outputfinal;
	for(i=0;i<8;i++)for(h=0;h<8;h++)weights[i][h]+=LEARNING_RATE*hiddenfinal[h]*inputs[alguma][i];
	for(h=0;h<8;h++)bias[h]+=LEARNING_RATE*hiddenfinal[h];

	console.log(`biasfinal = ${biasfinal.toFixed(6)}`);
}

//salva os bias e weights
data=[weights,weightsfinal,bias,biasfinal];
fs.writeFileSync('bias1.txt',JSON.stringify(data),'utf-8');

console.log("\nTreinamento finalizado. Pesos salvos em 'bias1.txt'")
