import random
import json

amostras = []

# 15 laranjas
for x in range(15):
    amostras.append({
        'peso': 0.8 + random.random() / 10, # valor entre 0.8 e 0.9
        'volume': 0.7 + random.random() / 10, # valor entre 0.7 e 0.8
        'cor': 0.6 + random.random() / 10, # valor entre 0.6 e 0.7
        'posicao': 0.5 + random.random() / 10, # valor entre 0.5 e 0.6
        'textura': 0.4 + random.random() / 10, # valor entre 0.4 e 0.5
        'consistencia': 0.3 + random.random() / 10, # valor entre 0.3 e 0.4
        'temperatura': 0.2 + random.random() / 10, # valor entre 0.2 e 0.3
        'idade': 0.1 + random.random() / 10, # valor entre 0.1 e 0.2
        'especie': 'l'
    })

# 15 frutas qualquer
for x in range(15):
    amostras.append({
        'peso': random.random() * 2, # valor entre 0 e 2
        'volume': random.random() * 2, # valor entre 0 e 2
        'cor': random.random() * 2, # valor entre 0 e 2
        'posicao': random.random() * 2, # valor entre 0 e 2
        'textura': random.random() * 2, # valor entre 0 e 2
        'consistencia': random.random() * 2, # valor entre 0 e 2
        'temperatura': random.random() * 2, # valor entre 0 e 2
        'idade': random.random() * 2, # valor entre 0 e 2
        'especie': 'q'
    })

with open('entradas2.txt', 'w', encoding='utf-8') as f:
    json.dump(amostras, f) # salva no arquivo

# Leitura e exibição
with open('entradas2.txt', 'r', encoding='utf-8') as f:
    lidas = json.load(f)

for i, a in enumerate(lidas): # exibe os dados gerados
    print(f"{i})\n{a['peso']} {a['volume']} {a['cor']} {a['posicao']} {a['textura']} {a['consistencia']} {a['temperatura']} {a['idade']} {a['especie']}\n")
