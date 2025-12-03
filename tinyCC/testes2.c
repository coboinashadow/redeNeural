#include<stdio.h> //FILE
#include<stdlib.h> //rand
#include<time.h>

int main(){
	FILE * fp; //para lidar com arquivos
	int imagens=120; //qtd de imagens para treinar
	double amostra[imagens][8];
	double weights[8];
	double bias;
	char filename[50]; //variavel que guarda o nome das imagens
	char cor; //usada na conversao
	int circulocerto=0, circuloerrado=0, quadradocerto=0, quadradoerrado=0; //contabilizando acertos e erros
	srand(time(0));

	for(int i=0;i<imagens;i++){
		sprintf(filename,"imagens/amostra%04d.jpg",i);
		fp=fopen(filename,"r");
		fseek(fp, 0, SEEK_END);
		long tamanho = ftell(fp);
		
		fseek(fp,0,SEEK_SET);
		for(int h=0;h<8;h++)amostra[i][h]=0.0;
		for(int h=0;h<8;h++)for(int x=0;x<tamanho/8;x++){
			fread(&cor,sizeof(char),1,fp);
			amostra[i][h]+=(double)cor; //gera um 'weight' que representa a imagem
		}
		fclose(fp);
	}

	 //Carrega os pesos e bias do arquivo bias2.txt
	fp = fopen("bias2.txt", "r");
	for(int i=0; i<8; i++) fscanf(fp, "%lf\n", &weights[i]);
	fscanf(fp, "%lf\n", &bias);
	fclose(fp);
		
	for(int s=0; s<1000; s++) {
		int alguma=rand()%imagens;

		double somatorio=bias;
		for(int h=0;h<8;h++)somatorio+=weights[h]*amostra[alguma][h]; //para as 8 caracteristicas

		if(alguma>imagens/2)
			if(somatorio>0)circulocerto++;
			else circuloerrado++;
		if(alguma<imagens/2)
			if(somatorio<0)quadradocerto++;
			else quadradoerrado++;
	}

	printf("\nEsperado circulo dado circulo (acertos): %d\n", circulocerto);
	printf("Esperado circulo dado quadrado (erros): %d\n", circuloerrado);
	printf("Esperado quadrado dado quadrado (acertos): %d\n", quadradocerto);
	printf("Esperado quadrado dado circulo (erros): %d\n\n", quadradoerrado);

	return 0;
}
