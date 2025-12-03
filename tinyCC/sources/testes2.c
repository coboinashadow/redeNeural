#include<stdio.h> //FILE
#include<stdlib.h> //rand
#include<time.h>

int main(){
	FILE * fp; //para lidar com arquivos
	int imagens=120; //qtd de imagens para treinar
	double amostra[imagens];
	char filename[imagens];
	char cor; //usada na conversao
	srand(time(0));
	double bias=rand();

	int circulocerto=0,circuloerrado=0,quadradocerto=0,quadradoerrado=0;

	for(int i=0;i<imagens;i++){
		sprintf(filename,"imagens/amostra%04d.bmp",i);
		fp=fopen(filename,"r");
		fseek(fp,54,SEEK_SET);
		amostra[i]=0.0;

		for(int l=0;l<60;l++)for(int x=0;x<60;x++)for(int y=0;y<3;y++){
			fread(&cor,sizeof(char),1,fp);
			amostra[i]+=(double)cor;
		}
		fclose(fp);
	}
	//for(int i=0;i<imagens;i++)printf("%lf\n",amostra[i]);

	//inicializa o bias com valores buscados do txt
	fp=fopen("bias2.txt","r");
	fscanf(fp,"%lf\n",&bias); //busca no arquivo o valor do bias final
	fclose(fp);

	//printf("%lf\n",bias);

	for(int x=0;x<1000;x++){
		int img=rand()%imagens;

		//printf("%d %lf %lf\n",img,amostra[img],bias);

		if(amostra[img]<bias){
			if(img<imagens/2)circulocerto++;
			else circuloerrado++;
		}else{
			if(img>imagens/2)quadradocerto++;
			else quadradoerrado++;
		}
	}
	printf("\n%d tentativas:\n",(circulocerto+circuloerrado+quadradocerto+quadradoerrado));
	printf("Esperado circulo dado circulo: %d\n",circulocerto);
	printf("Esperado circulo dado quadrado: %d\n",circuloerrado);
	printf("Esperado quadrado dado quadrado: %d\n",quadradocerto);
	printf("Esperado quadrado dado circulo: %d\n\n",quadradoerrado);

	return 0;
}

