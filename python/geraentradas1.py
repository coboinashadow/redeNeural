import random

frutas=[]

#25 laranjas
for x in range(25):
    especie='l'
    peso=0.082+random.random()/100 #entre 0.082 e 0.092
    frutas.append(f"{peso} {especie}")

#25 frutas qualquer
for x in range(25):
    especie='q'
    peso=random.random()*2 #entre 0 e 2
    frutas.append(f"{peso} {especie}")

#salva no arquivo
with open('entradas1.txt','w',encoding='utf-8')as f:f.write('\n'.join(frutas))

#leitura e exibicao
with open('entradas1.txt','r',encoding='utf-8')as f:
    conteudo=f.read().split('\n')
    for amostra in conteudo:
        peso,especie=amostra.split(' ')

        if especie=='l':especie='laranja'
        else: especie='fruta qualquer'

        print(f"{float(peso):.6f} {especie}")
