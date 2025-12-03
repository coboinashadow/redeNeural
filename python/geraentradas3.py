import os
import struct
import random

qtdimagens=120
width=60
height=60
radius=10

img_size=width*height*3
file_header=bytearray(14)
info_header=bytearray(40)
# File header
file_header[0:2]=b'BM'
file_header[2:6]=struct.pack('<I',54+img_size)
file_header[6:10]=(0).to_bytes(4,'little')
file_header[10:14]=(54).to_bytes(4,'little')
# Info header
info_header[0:4]=(40).to_bytes(4,'little')
info_header[4:8]=struct.pack('<i',width)
info_header[8:12]=struct.pack('<i',-height)
info_header[12:14]=(1).to_bytes(2,'little')
info_header[14:16]=(24).to_bytes(2,'little')
info_header[16:20]=(0).to_bytes(4,'little')
info_header[20:24]=struct.pack('<I',img_size)

for x in range(qtdimagens):
    img=bytearray([255]*(width*height*3))

    if x<qtdimagens//2: #metade das imagens contem circulo
        cx=20+random.randint(0,19) #centro do circulo
        cy=20+random.randint(0,19) #centro do circulo
        for y in range(height):
            for c in range(width):
                dx=c-cx
                dy=y-cy
                #se o pixel esta dentro do circulo
                if dx*dx+dy*dy<=radius*radius:
                    c=(y*width+c)*3 #posicao do pixel no bitmap
                    img[c]=0 #vermelho
                    img[c+1]=0 #verde
                    img[c+2]=0 #azul
    else: #metade das imagens contem quadrado
        cx=10+random.randint(0,19) #posicao do quadrado
        cy=10+random.randint(0,19) #posicao do quadrado
        for y in range(height):
            for c in range(width):
                #se o pixel esta dentro do quadrado
                if cx<c<cx+20 and cy<y<cy+20:
                    c=(y*width+c)*3 #posicao do pixel no bitmap
                    img[c]=0 #vermelho
                    img[c+1]=0 #verde
                    img[c+2]=0 #azul

    filename=f"imagens/amostra{x:04d}.bmp"

    #monta e salva a imagem
    bmp=file_header+info_header+img
    os.makedirs(os.path.dirname(filename),exist_ok=True)
    with open(filename,'wb')as f:f.write(bmp) #salva o arquivo imagem
    print(f"{filename} - [{len(img) + 54} bytes]")

print("\nImagens salvas com sucesso")
