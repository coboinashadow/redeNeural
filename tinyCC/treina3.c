#include<stdio.h> //FILE
#include<stdlib.h> //rand
#include<time.h>

int main(){
	FILE * fp; //para lidar com arquivos
	int imagens=120; //qtd de imagens para treinar
	double amostra[imagens];
	char filename[50]; //variavel que guarda o nome das imagens
	char cor; //usada na conversao
	srand(time(0));

	double bias=(rand()%100)*-1; //inicializa bias aleatório

	for(int i=0;i<imagens;i++){
		sprintf(filename,"imagens/amostra%04d.bmp",i);
		fp=fopen(filename,"r");
		fseek(fp,54,SEEK_SET);
		amostra[i]=0.0;
		for(int l=0;l<60;l++)for(int x=0;x<60;x++)for(int y=0;y<3;y++){
			fread(&cor,sizeof(char),1,fp);
			amostra[i]+=(double)cor; //gera um 'weight' que representa a imagem
		}
		fclose(fp);
	}

	for(int x=0;x<200000;x++){ //ajusta o bias centenas de vezes
		int alguma=rand()%imagens; //uma imagem qualquer

		//ajusta o bias pouco a pouco
		if(amostra[alguma]<bias)bias+=bias*0.00008; //um pouco a mais
		if(amostra[alguma]>bias)bias-=bias*0.00008; //um pouco a menos

		printf("biasfinal = %.6lf\n",bias);
	}
	fp=fopen("bias2.txt","w");
	fprintf(fp,"%lf\n",bias); //grava no arquivo o bias final
	fclose(fp);

	printf("\nTreinamento finalizado. Pesos salvos em 'bias2.txt'\n");
	return 0;
}

