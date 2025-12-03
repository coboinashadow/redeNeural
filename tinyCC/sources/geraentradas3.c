#include<stdio.h>
#include<stdlib.h>
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

int width=60;
int height=60;
char *image;

void circle(){
	int radius=10;
	int cx=20+(rand()%20);
	int cy=20+(rand()%20);
	for(int i=0;i<width*height*3;i++)image[i]=255;
	for(int y=0;y<height;y++){
		  for(int x=0;x<width;x++){
				int dx=x-cx;
				int dy=y-cy;
				if(dx*dx+dy*dy<=radius*radius){
					int index=(y*width+x)*3;
					image[index]=0; // Azul
					image[index+1]=0; // Verde
					image[index+2]=0; // Vermelho
				}
		  }
	 }
}
void rect(){
	int cx=10+(rand()%20);
	int cy=10+(rand()%20);
	for(int i=0;i<width*height*3;i++)image[i]=255;
	for(int y=0;y<height;y++){
		  for(int x=0;x<width;x++){
				if(x>cx&&x<cx+20&&y>cy&&y<cy+20){
					int index=(y*width+x)*3;
					image[index]=0; // Azul
					image[index+1]=0; // Verde
					image[index+2]=0; // Vermelho
				}
		  }
	 }
}

int main() {
 	image=calloc(width*height*3,1);
	srand(time(0));
	FILE *file;
	int qtdimagens=120;
	char filename[qtdimagens]; //variavel que guarda o nome das imagens
	for(int x=0;x<qtdimagens;x++){
		// Cria o cabeçalho BMP
		BMPFileHeader fileHeader={{'B','M'},0,0,0,54};
		BMPInfoHeader infoHeader={40,width,-height,1,24,0,0,0,0,0,0};

		fileHeader.bfSize=54+width*height*3;
		// Tamanho total: cabeçalhos + dados de pixel

		if(x<qtdimagens/2)circle(); //metade das imagens contem circulo
		else rect(); //metade das imagens contem quadrado

		sprintf(filename,"imagens/amostra%04d.bmp",x);

		// Salva a imagem em um arquivo BMP
		file=fopen(filename,"wb");
		if (!file) {
			perror("\nErro ao criar o arquivo\n\nTalvez seja necessario criar a pasta /imagens/ que ira conter os bitmaps\n\n");
			free(image);
			return 1;
		 }

		 fwrite(&fileHeader,sizeof(fileHeader),1,file);
		 fwrite(&infoHeader,sizeof(infoHeader),1,file);
		 fwrite(image,width*height*3,1,file);

		printf("/sources/%s - [%d bytes]\n",filename,fileHeader.bfSize);
	}

	fclose(file);
	free(image);

	printf("\nImagens salvas com sucesso\n");
	return 0;
}

