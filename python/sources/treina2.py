import random
import json

# Lê amostras
with open('entradas2.txt', 'r', encoding='utf-8') as f:
    amostras = json.load(f) # carrega na variavel amostra

# Inicializa os bias com valores aleatorios
bias = random.random()

for x in range(600000): # ajusta os bias milhares de :ezes
    a = amostras[random.randint(0, 14)]  # uma laranja qualquer
    caracteristica = [a['peso'], a['volume'], a['cor'], a['posicao'], a['textura'], a['consistencia'], a['temperatura'], a['idade']]
    referencia = sum(caracteristica)

    if referencia > bias: # um pouco a mais
        bias += bias * 0.000007
    elif referencia < bias: # um pouco a menos
        bias -= bias * 0.000007

    print(f"finalBias = {bias}")

# Salva os bias no arquivo
with open('bias1.txt', 'w', encoding='utf-8') as f:
    f.write('\n' + str(bias) + '\n')
