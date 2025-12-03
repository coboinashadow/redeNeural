#include<stdio.h> //FILE
#include<stdlib.h> //rand
#include<math.h>
#include<time.h>

#pragma pack(push,1)
typedef struct {
    unsigned char bfType[2];      // sempre "BM")
    unsigned int bfSize;          // Tamanho do arquivo
    unsigned short bfReserved1;   // Reservado (sempre 0)
    unsigned short bfReserved2;   // Reservado (sempre 0)
    unsigned int bfOffBits;       // Offset pixel começam
} BMPFileHeader;

typedef struct {
    unsigned int biSize;          // Tamanho da estrutura
    int biWidth;                  // Largura da imagem
    int biHeight;                 // Altura da imagem
    unsigned short biPlanes;      // sempre 1
    unsigned short biBitCount;    // Bits por pixel (24)
    unsigned int biCompression;   // Tipo de compressão 0
    unsigned int biSizeImage;     // imagesize sem headers
    int biXPelsPerMeter;          // Resolução horizontal
    int biYPelsPerMeter;          // Resolução vertical
    unsigned int biClrUsed;       // cores na paleta (0)
    unsigned int biClrImportant;  // 0
} BMPInfoHeader;
#pragma pack(pop)

int main() {
	int width=60;
	int height=60;
	int radius=10;
	char *img=calloc(width*height*3,1);
	int qtdimagens=120;
	char filename[50]; //variavel que guarda o nome das imagens
	srand(time(0));

	//cria o cabeçalho BMP
	BMPFileHeader fileHeader={{'B','M'},0,0,0,54};
	BMPInfoHeader infoHeader={40,width,-height,1,24,0,0,0,0,0,0};

	fileHeader.bfSize=54+width*height*3;
	//tamanho total: cabecalhos + dados de pixel

	for(int x=0;x<qtdimagens;x++){
		if(x<qtdimagens/2){//metade das imagens contem circulo
			int cx=20+(rand()%20); //centro do circulo
			int cy=20+(rand()%20); //centro do circulo
			for(int i=0;i<width*height*3;i++)img[i]=255;
			for(int y=0;y<height;y++){
				  for(int x=0;x<width;x++){
						int dx=x-cx;
						int dy=y-cy;
						//se o pixel esta dentro do circulo
						if(dx*dx+dy*dy<=radius*radius){
							int c=(y*width+x)*3; //posicao do pixel no bitmap
							img[c]=0;	//vermelho
							img[c+1]=0;	//verde
							img[c+2]=0;	//azul
						}
				  }
			 }
		}else{ //metade das imagens contem quadrado
			int cx=10+(rand()%20); //posicao do quadrado
			int cy=10+(rand()%20); //posicao do quadrado
			for(int i=0;i<width*height*3;i++)img[i]=255;
			for(int y=0;y<height;y++){
				  for(int x=0;x<width;x++){
						//se o pixel esta dentro do quadrado
						if(x>cx&&x<cx+20&&y>cy&&y<cy+20){
							int c=(y*width+x)*3; //posicao do pixel no bitmap
							img[c]=0;	//vermelho
							img[c+1]=0;	//verde
							img[c+2]=0;	//azul
						}
				  }
			 }
		}
		sprintf(filename,"imagens/amostra%04d.bmp",x);

		//monta e salva a imagem
		FILE *fp=fopen(filename,"wb");
		if(!fp){
			perror("\nErro ao criar o arquivo\n\nTalvez seja necessario criar a pasta /imagens/ que ira conter os bitmaps\n\n");
			return 1;
		}
		fwrite(&fileHeader,sizeof(fileHeader),1,fp);
		fwrite(&infoHeader,sizeof(infoHeader),1,fp);
		fwrite(img,width*height*3,1,fp);
		fclose(fp);
		printf("/sources/%s - [%d bytes]\n",filename,fileHeader.bfSize);
	}
	printf("\n%d arquivos imagens salvos com sucesso\n",qtdimagens);
	return 0;
}
