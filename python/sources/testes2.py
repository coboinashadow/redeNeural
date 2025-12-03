import random
import os

imagens = 120
amostra = [0] * imagens

# Contabilizando acertos e erros
circulocerto = circuloerrado = quadradocerto = quadradoerrado = 0

for i in range(imagens):
    with open(f"imagens/amostra{i:04d}.bmp", "rb") as f:
        buf = f.read()
    amostra[i] = sum(buf[54:])

# Lê bias2.txt
with open('bias2.txt', 'r', encoding='utf-8') as f:
    bias = float(f.read().strip())

for x in range(1000):  # testa 1000 vezes
    img = random.randint(0, imagens - 1)  # uma imagem qualquer

    if amostra[img] > bias:
        if img < imagens // 2:
            circulocerto += 1
        else:
            circuloerrado += 1
    else:
        if img > imagens // 2:
            quadradocerto += 1
        else:
            quadradoerrado += 1

print(f"\n{circulocerto + circuloerrado + quadradocerto + quadradoerrado} tentativas:")
print(f"Esperado circulo dado circulo: {circulocerto}")
print(f"Esperado circulo dado quadrado: {circuloerrado}")
print(f"Esperado quadrado dado quadrado: {quadradocerto}")
print(f"Esperado quadrado dado circulo: {quadradoerrado}\n")
