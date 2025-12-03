import random
import os

imagens = 120
amostra = [0] * imagens

for i in range(imagens):
    with open(f"imagens/amostra{i:04d}.bmp", "rb") as f:
        buf = f.read()
    amostra[i] = sum(buf[54:])

bias = random.random()  # entre 0 e 1

for x in range(300000): # ajusta o bias milhares de vezes
    alguma = random.randint(0, imagens - 1)  # uma imagem qualquer

    if amostra[alguma] > bias:
        bias += bias * 0.0001 # um pouco a mais
    elif amostra[alguma] < bias:
        bias -= bias * 0.0001 # um pouco a menos

    print(f"finalBias: {bias}")

with open('bias2.txt', 'w', encoding='utf-8') as f:
    f.write(f"{bias}\n") # salva o bias final no arquivo
