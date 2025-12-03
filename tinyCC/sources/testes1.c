#include<stdio.h> //FILE
#include<stdlib.h> //rand
#include<math.h> //exp
#include<string.h> //memcpy
#include<time.h>

typedef struct{
    double inputs[8]; //8 caracteristicas da fruta
    double target; //especie
} fruta;

//função que recebe qualquer double e retorna valor entre -1 e 1
double sigmoid(double x){return 1.0/(1.0+exp(-x));}

int main(){
	fruta dataset[30];
	double weights[8][8],weightsfinal[8];
	double bias[8],biasfinal;
	int laranjacerto=0,laranjaerrado=0,qqrcerto=0,qqrerrado=0; //contabilizando acertos e erros
	srand(time(0));

	//busca os valores no arquivo e armazena em um array 'dataset'
	FILE *fp=fopen("entradas2.txt","r");
	for(int x=0;x<30;x++){
		double in[8];
		char especie;
		fscanf(fp, "%lf %lf %lf %lf %lf %lf %lf %lf %c\n",&in[0],&in[1],&in[2],&in[3],&in[4],&in[5],&in[6],&in[7],&especie);
		memcpy(dataset[x].inputs,in, sizeof(double)*8);
		dataset[x].target=(especie=='l')?1.0:0.0;
	}
	fclose(fp);

	//inicializa os bias com valores buscados do txt
	fp=fopen("bias1.txt","r");
	for(int i=0;i<8;i++)for(int h=0;h<8;h++)fscanf(fp,"%lf\n",&weights[i][h]); //busca no arquivo os weights
	for(int h=0;h<8;h++)fscanf(fp,"%lf\n",&weightsfinal[h]); //busca no arquivo os weightsfinal
	for(int h=0;h<8;h++)fscanf(fp,"%lf\n",&bias[h]); //busca no arquivo os bias
	fscanf(fp,"%lf\n",&biasfinal); //busca no arquivo os weightsfinal
	fclose(fp);

	printf("\n--- RESULTADO ---\nPara as 30 frutas da base de dados\n\n");
	for(int s=0;s<30;s++){
		double hidden[8],output;
		for(int h=0;h<8;h++){
			hidden[h]=bias[h];
			for(int i=0;i<8;i++)hidden[h]+=dataset[s].inputs[i]*weights[i][h];
			hidden[h]=sigmoid(hidden[h]);
		}
		output=biasfinal;
		for(int h=0;h<8;h++)output+=hidden[h]*weightsfinal[h];
		output=sigmoid(output);
		if(dataset[s].target<0.05)
			if(output<0.05)laranjacerto++;
			else laranjaerrado++;
		if(dataset[s].target>0.095)
			if(output>0.095)qqrcerto++;
			else qqrerrado++;
	}

	printf("Esperado laranja dado laranja: %d\n",laranjacerto);
	printf("Esperado laranja dado qqr: %d\n",laranjaerrado);
	printf("Esperado qqr dado qqr: %d\n",qqrcerto);
	printf("Esperado qqr dado laranja: %d\n\n",qqrerrado);

	return 0;
}
