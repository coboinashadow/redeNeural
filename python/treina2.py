import random

inputs=[]
target=[]
#busca os valores no arquivo entradas2.txt
with open("entradas2.txt","r") as f:
    for line in f:
        parts=line.split()
        inputs.append([float(parts[i])for i in range(8)])
        target.append(1.0 if parts[8]=='l' else 0.0)

#inicializa os bias com valores aleatorios
weights=[random.random() for _ in range(8)]
bias=0.0

for x in range(100000): #ajusta os bias centenas de vezes
    total_erros=0

    for i in range(100):
        alguma=int(random.random()*30)
        somatorio=bias
        for h in range(8):somatorio=somatorio+(weights[h]*inputs[alguma][h]) #para as 8 caracteristicas

        if somatorio>=0.0:
            degrau=1.0
        else:
            degrau=0.0

        erro=target[alguma]-degrau

        if erro!=0.0:
            total_erros=total_erros+1
            for h in range(8):weights[h]=weights[h]+(0.000004*erro*inputs[alguma][h])
            bias=bias+(0.000004*erro)

    print(f"{100000-x} biasfinal = {bias:.6f}")

    if x%5000==0 and total_erros==0:break; #o bias foi encontrado

#salva o bias e weights
with open("bias1.txt", "w")as f:
    for h in range(8):f.write(f"{weights[h]:.12f}\n") #grava no arquivo os weights
    f.write(f"{bias:.12f}\n") #grava no arquivo os bias

print("\nTreinamento finalizado. Pesos salvos em 'bias1.txt'")
