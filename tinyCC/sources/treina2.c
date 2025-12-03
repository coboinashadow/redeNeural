#include<stdio.h> //FILE
#include<stdlib.h> //rand
#include<math.h> //exp
#include<time.h>

#define LEARNING_RATE 0.1

typedef struct{
    double inputs[8];
    double target;
} fruta;

//funcao que recebe qualquer double e retorna valor entre -1 e 1
double sigmoid(double x){return 1.0/(1.0+exp(-x));}
//funcao inversa a sigmoide
double dsigmoid(double y){return y*(1.0-y);}

int main(){
	fruta dataset[30];
	double weights[8][8],weightsfinal[8];
	double bias[8],biasfinal;
	srand(time(0));

	//busca os valores no arquivo entradas2.txt
	FILE *fp=fopen("entradas2.txt","r");
	for(int x=0;x<30;x++){
		double in[8];
		char especie;
		fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %c\n",&in[0],&in[1],&in[2],&in[3],&in[4],&in[5],&in[6],&in[7],&especie);
		for(int i=0;i<8;i++)dataset[x].inputs[i]=in[i];
		dataset[x].target=(especie=='l')?1.0:0.0;
	}
	fclose(fp);

	//inicializa os bias com valores aleatorios
	for(int i=0;i<8;i++)for(int h=0;h<8;h++)weights[i][h]=((double)rand()/RAND_MAX)*2-1;
	for(int h=0;h<8;h++)weightsfinal[h]=((double)rand()/RAND_MAX)*2-1;
	for(int h=0;h<8;h++)bias[h]=((double)rand()/RAND_MAX)*2-1;
	biasfinal=((double)rand()/RAND_MAX)*2-1;

	for(int x=0;x<50000;x++){ //ajusta os bias centenas de vezes
		fruta alguma=dataset[rand()%30]; //escolhe uma fruta qualquer

		// --- FORWARD PROPAGATION ---
		double hidden[8];
		for(int h=0;h<8;h++){
			hidden[h]=bias[h];
			for(int i=0;i<8;i++)hidden[h]+=alguma.inputs[i]*weights[i][h];
			hidden[h]=sigmoid(hidden[h]);
		}
		double output=biasfinal;
		for(int h=0;h<8;h++)output+=hidden[h]*weightsfinal[h];
		output=sigmoid(output);

		// --- BACKPROPAGATION ---
		double outputfinal=(alguma.target-output)*dsigmoid(output);
		double hiddenfinal[8];
		for(int h=0;h<8;h++)hiddenfinal[h]=(outputfinal*weightsfinal[h])*dsigmoid(hidden[h]);

		// --- ATUALIZAÇÃO DE PESOS E BIAS ---
		for(int h=0;h<8;h++)weightsfinal[h]+=LEARNING_RATE*outputfinal*hidden[h];
		biasfinal+=LEARNING_RATE*outputfinal;
		for(int i=0;i<8;i++)for(int h=0;h<8;h++)weights[i][h]+=LEARNING_RATE*hiddenfinal[h]*alguma.inputs[i];
		for(int h=0;h<8;h++)bias[h]+=LEARNING_RATE*hiddenfinal[h];

		printf("biasfinal = %.6lf\n",biasfinal);
	}

	fopen("bias1.txt","w");
	for(int i=0;i<8;i++)for(int h=0;h<8;h++)fprintf(fp,"%lf\n",weights[i][h]); //grava no arquivo os weights
	for(int h=0;h<8;h++)fprintf(fp,"%lf\n",weightsfinal[h]); //grava no arquivo os weightsfinal
	for(int h=0;h<8;h++)fprintf(fp,"%lf\n",bias[h]); //grava no arquivo os bias
	fprintf(fp,"%lf\n",biasfinal); //grava no arquivo os biasfinal
	fclose(fp);

	printf("\nTreinamento finalizado. Pesos salvos em 'bias1.txt'\n");
	return 0;
}
