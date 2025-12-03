import random

linhas = []

# 25 laranjas
for x in range(25):
    especie = 'l'
    peso = 0.082 + random.random() / 100  # entre 0.082 e 0.092
    linhas.append(f"{peso} {especie}")

# 25 frutas qualquer
for x in range(25):
    especie = 'q'
    peso = random.random() * 2  # entre 0 e 2
    linhas.append(f"{peso} {especie}")

with open('entradas1.txt', 'w', encoding='utf-8') as f:
    f.write('\n'.join(linhas)) # salva no arquivo

# Leitura e exibição
with open('entradas1.txt', 'r', encoding='utf-8') as f:
    conteudo = f.read().split('\n')

for x, linha in enumerate(conteudo): # exibe os dados
    peso, especie = linha.split(' ')
    print(f"{x}) {peso} {especie}")
