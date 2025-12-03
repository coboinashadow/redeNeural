import random
import os

qtdimagens=120 #qtd de imagens para treinar
amostra=[0]*qtdimagens #array de representacao numerica da imagem

bias=random.random() #inicializa bias aleatório

for i in range(qtdimagens):
    with open(f"imagens/amostra{i:04d}.bmp","rb")as f:
        buf=f.read()
    #imagem com 60 linhas 60 colunas 3 bytes por pixel
    for l in range(60):
        for x in range(60):
            for y in range(3):
                amostra[i]+=buf[(l*180)+(x*3)+y]; #gera um 'weight' que representa a imagem

for x in range(200000): #ajusta o bias centenas de vezes
    alguma=random.randrange(qtdimagens) #uma imagem qualquer

    #ajusta o bias pouco a pouco
    if amostra[alguma]>bias:bias+=bias*0.0001 # um pouco a mais
    if amostra[alguma]<bias:bias-=bias*0.0001 # um pouco a menos

    print(f"biasfinal = {bias:.6f}")

#salva o bias no arquivo
with open('bias2.txt','w',encoding='utf-8')as f:f.write(f"{bias}\n")
    
print("\nTreinamento finalizado. Pesos salvos em 'bias2.txt'")
