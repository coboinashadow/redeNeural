import random
import math

LEARNINGRATE=0.1

#funcao que recebe qualquer double e retorna valor entre -1 e 1
def sigmoid(x:float)->float:return 1.0/(1.0+math.exp(-x))
#funcao inversa a sigmoide
def dsigmoid(y:float)->float:return y*(1.0-y)

inputs=[]
target=[]
#busca os valores no arquivo entradas2.txt
with open("entradas2.txt","r") as f:
    for line in f:
        line = line.strip()
        parts = line.split()
        inputs.append([float(parts[i]) for i in range(8)])
        target.append(0.0 if parts[8] == 'l' else 1.0)

#inicializa os bias com valores aleatorios
weights=[[random.random()*2-1 for _ in range(8)]for _ in range(8)]
weightsfinal=[random.random()*2-1 for _ in range(8)]
bias=[random.random()*2-1 for _ in range(8)]
biasfinal=random.random()*2-1

for it in range(50000): #ajusta os bias centenas de vezes
    alguma=random.randrange(30) #escolhe uma fruta qualquer

	# --- FORWARD PROPAGATION ---
    hidden=[0.0]*8
    for h in range(8):
        hidden[h]=bias[h]
        for i in range(8):hidden[h]+=inputs[alguma][i]*weights[i][h]
        hidden[h]=sigmoid(hidden[h])
    out=biasfinal
    for h in range(8):out+=hidden[h]*weightsfinal[h]
    out=sigmoid(out)

	# --- BACKPROPAGATION ---
    outputfinal=(target[alguma]-out)*dsigmoid(out);
    hiddenfinal=[0.0]*8
    for h in range(8):hiddenfinal[h]=(outputfinal*weightsfinal[h])*dsigmoid(hidden[h])

	# --- ATUALIZAÇÃO DE PESOS E BIASES ---
    for h in range(8):weightsfinal[h]+=LEARNINGRATE*outputfinal*hidden[h]
    biasfinal+=LEARNINGRATE*outputfinal
    for i in range(8):
        for h in range(8):weights[i][h]+=LEARNINGRATE*hiddenfinal[h]*inputs[alguma][i]
    for h in range(8):bias[h]+=LEARNINGRATE*hiddenfinal[h]

    print(f"biasfinal = {biasfinal:.6f}")

#salva os bias e weights
with open("bias1.txt", "w")as f:
    for i in range(8):
        for h in range(8):f.write(f"{weights[i][h]:.12f}\n") #grava no arquivo os weights
    for h in range(8):f.write(f"{weightsfinal[h]:.12f}\n") #grava no arquivo os weightsfinal
    for h in range(8):f.write(f"{bias[h]:.12f}\n") #grava no arquivo os bias
    f.write(f"{biasfinal:.12f}\n") #grava no arquivo os biasfinal

print("\nTreinamento finalizado. Pesos salvos em 'bias1.txt'")
