import random

# Lê amostras
with open('entradas1.txt', 'r', encoding='utf-8') as f:
    linhas = f.read().strip().split('\n')

amostra = []
for linha in linhas: # carrega do arquivo para variavel amostra
    peso, especie = linha.split(' ')
    amostra.append({'peso': float(peso), 'especie': especie})

# Inicializa bias aleatório
bias = random.random()

for x in range(4000): # ajusta o bias centenas de vezes
    fruta = amostra[random.randint(0, 24)]  # uma laranja aleatória

    if fruta['peso'] > bias:
        bias += bias * 0.01 # um pouco a mais
    elif fruta['peso'] < bias:
        bias -= bias * 0.01 # um pouco a menos

print(f"O valor que diferencia (bias): {bias}")
