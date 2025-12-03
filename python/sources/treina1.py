import random

dataset=[]
#busca os valores no arquivo e armazena em um array 'dataset'
with open("entradas1.txt","r") as f:
    for line in f:
        peso,especie=line.split(' ')
        dataset.append({'peso':float(peso),'especie':especie})

#inicializa o bias com um valor aleatorio
bias=random.random() #valor entre 0 e 1

for x in range(4000): #ajusta o bias centenas de vezes
    amostra=dataset[random.randint(0,24)] #uma laranja aleatória

    if amostra['peso']>bias:bias+=bias*0.01 #um pouco a mais
    if amostra['peso']<bias:bias-=bias*0.01 #um pouco a menos

print(f"O valor que diferencia (bias): {bias:.6f}")
