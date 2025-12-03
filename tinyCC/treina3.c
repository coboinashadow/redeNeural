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
			amostra[i][h]+=(double)cor; //gera um array de 'weight' que representa a imagem
		}
		fclose(fp);
	}

	//Inicializa weights e bias
	for(int i=0; i<8; i++) weights[i] = ((double)rand() / (double)RAND_MAX);
	bias = 0.0;

	for(int x=0;x<10000;x++){ //ajusta os bias centenas de vezes
		int total_erros=0;

		for(int i=0;i<300;i++){
			int alguma=rand()%imagens;

			double somatorio=bias;
			for(int h=0;h<8;h++)somatorio+=weights[h]*amostra[alguma][h];

			double degrau=somatorio>=0.0?1.0:0.0;
			double target=alguma>imagens/2?1.0:0.0;
			double erro=target-degrau;

			if(erro!=0.0){
				total_erros++;
				for(int h=0;h<8;h++)weights[h]+=0.01*erro*amostra[alguma][h];
				bias+=0.01*erro;
			}
		}

		printf("%d biasfinal = %.6lf\n", 10000-x, bias);

		if(x%5000==0&&total_erros==0)break; //o bias foi encontrado
	}

	//Salva os pesos e bias
	fp = fopen("bias2.txt", "w");
	for(int i=0; i<8; i++) fprintf(fp, "%lf\n", weights[i]);
	fprintf(fp, "%lf\n", bias);
	fclose(fp);

	printf("\nTreinamento finalizado. Pesos salvos em 'bias2.txt'\n");
	return 0;
}

