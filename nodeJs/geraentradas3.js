fs=require('fs');
path=require('path');

width=60;
height=60;
radius=10;
qtdimagens=120;

fileHeader=Buffer.alloc(14);
infoHeader=Buffer.alloc(40);
imgSize=width*height*3;
//file header
fileHeader.write('BM');
fileHeader.writeUInt32LE(54+imgSize,2);
fileHeader.writeUInt32LE(0,6);
fileHeader.writeUInt32LE(54,10);
//info header
infoHeader.writeUInt32LE(40,0);
infoHeader.writeInt32LE(width,4);
infoHeader.writeInt32LE(-height,8);// top-down
infoHeader.writeUInt16LE(1,12);
infoHeader.writeUInt16LE(24,14);
infoHeader.writeUInt32LE(0,16);
infoHeader.writeUInt32LE(imgSize,20);

for(i=0;i<qtdimagens;i++){
	img=Buffer.alloc(width*height*3, 255);
	if(i<qtdimagens/2){//metade das imagens contem circulo
		cx=20+parseInt(Math.random()*20); //centro do circulo
		cy=20+parseInt(Math.random()*20); //centro do circulo
		for(y=0;y<height;y++){
			for(x=0;x<width;x++){
				dx=x-cx;
				dy=y-cy;
				//se o pixel esta dentro do circulo
				if(dx*dx+dy*dy<=radius*radius){
					c=(y*width+x)*3; //posicao do pixel no bitmap
					img[c]=0;	//vermelho
					img[c+1]=0;	//verde
					img[c+2]=0;	//azul
				}
			}
		}
	}else{ //metade das imagens contem quadrado
		cx=10+parseInt(Math.random()*20); //posicao do quadrado
		cy=10+parseInt(Math.random()*20); //posicao do quadrado
		for(y=0;y<height;y++){
			for(x=0;x<width;x++){
				//se o pixel esta dentro do quadrado
				if(x>cx&&x<cx+20&&y>cy&&y<cy+20){
					c=(y*width+x)*3; //posicao do pixel no bitmap
					img[c]=0;	//vermelho
					img[c+1]=0;	//verde
					img[c+2]=0;	//azul
				}
			}
		}
	}

	//monta e salva a imagem
	bmp=Buffer.concat([fileHeader,infoHeader,img]);
	filename=`imagens/amostra${i.toString().padStart(4,'0')}.bmp`;
	fs.mkdirSync(path.dirname(filename),{recursive:true});
	fs.writeFileSync(filename,bmp);
	console.log(`${filename} - [${img.length+54} bytes]`);
}
console.log(`\n${qtdimagens} arquivos imagens salvos com sucesso`);
