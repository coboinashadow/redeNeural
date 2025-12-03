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

	//Inicializa weights e bias
	for(int i=0; i<8; i++) weights[i] = ((double)rand() / (double)RAND_MAX);
	bias = 0.0;

	for(int x=0;x<100000;x++){ //ajusta os bias centenas de vezes
		int total_erros=0;

		for(int i=0;i<100;i++){
			int alguma=rand()%30;
			double somatorio=bias;
			for(int h=0;h<8;h++)somatorio+=weights[h]*dataset[alguma].inputs[h]; //para as 8 caracteristicas

			double degrau=somatorio>=0.0?1.0:0.0;
			double erro=dataset[alguma].target-degrau;

			if(erro!=0.0){
				total_erros++;
				for(int h=0;h<8;h++)weights[h]+=0.000002*erro*dataset[alguma].inputs[h];
				bias+=0.000002*erro;
			}
		}

		printf("%6d biasfinal = %.6lf\n", 100000-x, bias);

		if(x%5000==0&&total_erros==0)break; //o bias foi encontrado
	}

	//Salva os pesos e bias
	fp = fopen("bias1.txt", "w");
	for(int i=0; i<8; i++) fprintf(fp, "%lf\n", weights[i]);
	fprintf(fp, "%lf\n", bias);
	fclose(fp);

	printf("\nTreinamento finalizado. Pesos salvos em 'bias1.txt'\n");
	return 0;
}
