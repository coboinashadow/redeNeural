#include<stdio.h> //FILE
#include<stdlib.h> //rand
#include<string.h> //memcpy
#include<time.h>

typedef struct{
	double inputs[8];	//8 características da fruta
	double target;	 //espécie
} fruta;

int main(){
	fruta dataset[30];
	double weights[8];
	double bias;
	int laranjacerto=0, laranjaerrado=0, qqrcerto=0, qqrerrado=0; //contabilizando acertos e erros
	srand(time(0));

	//Busca os valores no arquivo entradas2.txt
	FILE *fp = fopen("entradas2.txt", "r");
	for(int x=0; x<30; x++){
		double in[8];
		char especie;
		fscanf(fp, "%lf %lf %lf %lf %lf %lf %lf %lf %c\n", &in[0], &in[1], &in[2], &in[3], &in[4], &in[5], &in[6], &in[7], &especie);
		for(int i=0; i<8; i++) dataset[x].inputs[i] = in[i];
		dataset[x].target = (especie == 'l') ? 1.0 : 0.0;
	}
	fclose(fp);

	//Carrega os pesos e bias do arquivo bias1.txt
	fp = fopen("bias1.txt", "r");
	for(int i=0; i<8; i++) fscanf(fp, "%lf\n", &weights[i]);
	fscanf(fp, "%lf\n", &bias);
	fclose(fp);
	
	printf("\n--- RESULTADO ---\nPara as 30 frutas da base de dados\n\n");
	//Testa a rede neural com 1000 predições aleatórias
	for(int s=0; s<1000; s++){
		fruta alguma = dataset[rand() % 30];	//escolhe uma fruta qualquer

		double somatorio=bias;
		for(int h=0;h<8;h++)somatorio+=weights[h]*alguma.inputs[h]; //para as 8 caracteristicas

		if(alguma.target>0.5)
			if(somatorio>0)laranjacerto++;
			else laranjaerrado++;
		if(alguma.target<0.5)
			if(somatorio<0)qqrcerto++;
			else qqrerrado++;
	}
	
	printf("Esperado laranja dado laranja (acertos): %d\n", laranjacerto);
	printf("Esperado laranja dado qqr (erros): %d\n", laranjaerrado);
	printf("Esperado qqr dado qqr (acertos): %d\n", qqrcerto);
	printf("Esperado qqr dado laranja (erros): %d\n\n", qqrerrado);
	
	return 0;
}