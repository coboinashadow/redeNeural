import random
import os

qtdimagens=120 #qtd de qtdimagens para treinar
amostra=[0]*qtdimagens #array de representacao numerica da imagem

#contabilizando acertos e erros
circulocerto=circuloerrado=quadradocerto=quadradoerrado=0

for i in range(qtdimagens):
    with open(f"imagens/amostra{i:04d}.bmp","rb")as f:
        buf=f.read()
    #imagem com 60 linhas 60 colunas 3 bytes por pixel
    for l in range(60):
        for x in range(60):
            for y in range(3):
                amostra[i]+=buf[(l*180)+(x*3)+y]; #gera um 'weight' que representa a imagem

#inicializa o bias com valor buscado do txt
with open('bias2.txt','r',encoding='utf-8')as f:
    bias=float(f.read().strip())

for x in range(1000): #testa centenas de vezes
    img=random.randint(0,qtdimagens-1) #uma imagem qualquer
    if amostra[img]>bias:
        if img<qtdimagens//2:
            circulocerto+=1
        else:
            circuloerrado+=1
    else:
        if img>qtdimagens//2:
            quadradocerto+=1
        else:
            quadradoerrado+=1

print(f"\n{circulocerto+circuloerrado+quadradocerto+quadradoerrado} tentativas:")
print(f"Esperado circulo dado circulo: {circulocerto}")
print(f"Esperado circulo dado quadrado: {circuloerrado}")
print(f"Esperado quadrado dado quadrado: {quadradocerto}")
print(f"Esperado quadrado dado circulo: {quadradoerrado}\n")
