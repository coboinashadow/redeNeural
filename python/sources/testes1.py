import math

#funcao que recebe qualquer double e retorna valor entre -1 e 1
def sigmoid(x:float)->float:return 1.0/(1.0+math.exp(-x))

inputs=[]
target=[]
#busca os valores no arquivo entradas2.txt
with open("entradas2.txt", "r") as f:
    for line in f:
        parts=line.split()
        inputs.append([float(parts[i])for i in range(8)])
        target.append(1.0 if parts[8]=='l' else 0.0)

vals=[]
#buscando dados no arquivo texto
with open("bias1.txt","r") as f:
    for line in f:
        vals.append(float(line.strip()))

weights=[[0.0 for _ in range(8)]for _ in range(8)]
for i in range(8):
    for h in range(8):
        weights[i][h]=vals[0];

weightsfinal=[0.0 for _ in range(8)]
for h in range(8):
    weightsfinal[h]=vals[1];

bias=[0.0 for _ in range(8)]
for h in range(8):
    bias[h]=vals[2];

biasfinal=vals[3]

#contabilizando acertos e erros
laranjacerto=laranjaerrado=qqrcerto=qqrerrado=0

for s in range(30):
    hidden=[0.0]*8
    for h in range(8):
        acc=bias[h]
        for i in range(8):
            acc+=inputs[s][i]*weights[i][h]
        hidden[h]=sigmoid(acc)

    out=biasfinal
    for h in range(8):
        out+=hidden[h]*weightsfinal[h]
    out=sigmoid(out)

    if target[s]>0.095:
        if out>0.095:laranjacerto+=1
        else:laranjaerrado+=1
    else:
        if out>0.095:qqrcerto+=1
        else:qqrerrado+=1

print(f"\n--- RESULTADO ---\nPara as 30 frutas da base de dados:\n");
print(f"Esperado laranja dado laranja: {laranjacerto}")
print(f"Esperado laranja dado qqr: {laranjaerrado}")
print(f"Esperado qqr dado qqr: {qqrcerto}")
print(f"Esperado qqr dado laranja: {qqrerrado}\n")
