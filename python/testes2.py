import random
import os

qtdimagens=120 #qtd de imagens para treinar
amostra=[0]*qtdimagens #array de representacoes numericas das imagens

#carregamento das imagens
for i in range(qtdimagens):
    with open(f"imagens/amostra{i:04d}.bmp","rb")as f:buf=f.read()
    #imagem com 60 linhas 60 colunas 3 bytes por pixel
    for l in range(60):
        for x in range(60):
            for y in range(3):
                amostra[i]+=buf[(l*180)+(x*3)+y+54]; #um 'weight' que representa a imagem

#inicializa o bias com valor buscado do txt
with open('bias2.txt','r',encoding='utf-8')as f:bias=float(f.read().strip())

#contabilizando acertos e erros
circulocerto=circuloerrado=quadradocerto=quadradoerrado=0

#testa a inteligencia artificial com 1000 predições aleatórias
for x in range(1000):
    alguma=random.randint(0,qtdimagens-1) #escolhe uma imagem qualquer

    if alguma>qtdimagens//2: #se a imagem contem um circulo
        if amostra[alguma]<bias:
            circulocerto+=1
        else:
            circuloerrado+=1
    else:
        if amostra[alguma]>bias: #se a imagem contem um quadrado
            quadradocerto+=1
        else:
            quadradoerrado+=1

print(f"\nEsperado circulo dado circulo: {circulocerto}")
print(f"Esperado circulo dado quadrado: {circuloerrado}")
print(f"Esperado quadrado dado quadrado: {quadradocerto}")
print(f"Esperado quadrado dado circulo: {quadradoerrado}\n")
