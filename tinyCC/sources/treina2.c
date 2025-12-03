#include<stdio.h> //FILE
#include<stdlib.h> //rand
#include<time.h>

typedef struct{
	double peso;
	double volume;
	double cor;
	double posicao;
	double textura;
	double consistencia;
	double temperatura;
	double idade;
	char especie;
} fruta;

int main(){
	double bias[3];
	double finalBias;
	fruta amostra[30];
	srand(time(0));

	//busca os valores no arquivo e armazena em um array 'amostra'
	FILE *fp=fopen("entradas2.txt","r");
	for(int x=0;x<30;x++){
		fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %c\n",&amostra[x].peso,&amostra[x].volume,&amostra[x].cor,&amostra[x].posicao,&amostra[x].textura,&amostra[x].consistencia,&amostra[x].temperatura,&amostra[x].idade,&amostra[x].especie,&amostra[x].especie); //busca no arquivo
		//printf("%d) %lf %lf %lf %lf %lf %lf %lf %lf %c\n",x,amostra.peso,amostra.volume,amostra.cor,amostra.posicao,amostra.textura,amostra.consistencia,amostra.temperatura,amostra.idade,amostra.especie);
	}
	fclose(fp);

	//inicializa os bias com valores aleatorios
	for(int x=0;x<3;x++)bias[x]=(((double)rand()/(double)(RAND_MAX))/1.0);
	finalBias=40.0+(((double)rand()/(double)(RAND_MAX))/1.0);

	for(int x=0;x<1000000;x++){ //ajusta os bias centenas de vezes
		int alguma=rand()%15; //escolhe uma fruta qualquer
		fruta a=amostra[alguma];

		double referencia=a.peso+a.volume+a.cor+a.posicao+a.textura+a.consistencia+a.temperatura+a.idade;

		//for(int x=0;x<3;x++)printf("%lf\n",bias[x]);

		for(int x=0;x<3;x++){
			//ajusta os bias pouco a pouco
			if(referencia>bias[x])bias[x]+=bias[x]*0.000007; //um pouco a mais
			else if(referencia<bias[x])bias[x]-=bias[x]*0.000007; //um pouco a menos
		}

		double referenciaFinal = referencia * bias[0] + referencia * bias[1] + referencia * bias[2];

			//ajusta os bias pouco a pouco
		if(referenciaFinal>finalBias)finalBias+=finalBias*0.000007; //um pouco a mais
		else if(referenciaFinal<finalBias)finalBias-=finalBias*0.000007; //um pouco a menos

		printf("finalBias = %lf\n",finalBias);

	}

	fopen("bias1.txt","w");
	for(int x=0;x<3;x++)fprintf(fp,"%lf\n",bias[x]); //grava no arquivo os bias
	fprintf(fp,"%lf\n",finalBias); //grava no arquivo o bias final
	fclose(fp);

	return 0;
}

