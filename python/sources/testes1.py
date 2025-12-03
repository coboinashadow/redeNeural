import random

# Contabilizando acertos e erros
laranjacerto = laranjaerrado = qqrcerto = qqrerrado = 0

# Lê os bias
with open('bias1.txt', 'r', encoding='utf-8') as f:
    linhas = f.read().strip().split('\n')
bias = [float(x) for x in linhas[:3]]
finalBias = float(linhas[3])

for x in range(1000):  # testa 1000 vezes
    if random.random() < 0.5:
        especie = 'l'  # laranja aleatória
        peso = 0.8 + random.random() / 10
        volume = 0.7 + random.random() / 10
        cor = 0.6 + random.random() / 10
        posicao = 0.5 + random.random() / 10
        textura = 0.4 + random.random() / 10
        consistencia = 0.3 + random.random() / 10
        temperatura = 0.2 + random.random() / 10
        idade = 0.1 + random.random() / 10
    else:
        especie = 'q'  # fruta qualquer
        peso = random.random() * 2
        volume = random.random() * 2
        cor = random.random() * 2
        posicao = random.random() * 2
        textura = random.random() * 2
        consistencia = random.random() * 2
        temperatura = random.random() * 2
        idade = random.random() * 2

    referencia = peso + volume + cor + posicao + textura + consistencia + temperatura + idade

    referenciaFinal = referencia * bias[0] + referencia * bias[1] + referencia * bias[2] # valor para comparar com o bias final

    delta = referenciaFinal - finalBias

    if especie == 'l':
        if -5 < delta < 5:
            laranjacerto += 1
        else:
            laranjaerrado += 1
    else:
        if -5 < delta < 5:
            qqrerrado += 1
        else:
            qqrcerto += 1

print(f"\n{laranjacerto + laranjaerrado + qqrcerto + qqrerrado} tentativas:")
print(f"Esperado laranja dado laranja: {laranjacerto}")
print(f"Esperado laranja dado qqr: {laranjaerrado}")
print(f"Esperado qqr dado qqr: {qqrcerto}")
print(f"Esperado qqr dado laranja: {qqrerrado}\n")
