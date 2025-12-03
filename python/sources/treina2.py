import random
import json

# Lê amostras
with open('entradas2.txt', 'r', encoding='utf-8') as f:
    amostras = json.load(f) # carrega na variavel amostra

# Inicializa os bias com valores aleatorios
bias = [random.random(), random.random(), random.random()]
finalBias = 40 + random.random()

for x in range(1000000): # ajusta os bias milhares de :ezes
    a = amostras[random.randint(0, 14)]  # uma laranja qualquer
    caracteristica = [a['peso'], a['volume'], a['cor'], a['posicao'], a['textura'], a['consistencia'], a['temperatura'], a['idade']]
    referencia = sum(caracteristica)

    for t in range(3): # ajusta os bias da camada intermediaria
        if referencia > bias[t]: # um pouco a mais
            bias[t] += bias[t] * 0.000007
        elif referencia < bias[t]: # um pouco a menos
            bias[t] -= bias[t] * 0.000007

    referenciaFinal = referencia * bias[0] + referencia * bias[1] + referencia * bias[2] # ajusta o bias final

    if referenciaFinal > finalBias: # um pouco a mais
        finalBias += finalBias * 0.000007
    elif referenciaFinal < finalBias: # um pouco a menos
        finalBias -= finalBias * 0.000007

    print(f"finalBias = {finalBias}")

# Salva os bias no arquivo
with open('bias1.txt', 'w', encoding='utf-8') as f:
    f.write('\n'.join([str(b) for b in bias]) + '\n' + str(finalBias) + '\n')
