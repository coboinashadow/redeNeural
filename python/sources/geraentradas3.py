import os
import struct
import random

width = 60
height = 60

def circle(image):
    radius = 10
    cx = 20 + random.randint(0, 19)
    cy = 20 + random.randint(0, 19)
    for y in range(height):
        for x in range(width):
            dx = x - cx
            dy = y - cy
            if dx * dx + dy * dy <= radius * radius:
                idx = (y * width + x) * 3
                image[idx] = 0
                image[idx + 1] = 0
                image[idx + 2] = 0

def rect(image):
    cx = 10 + random.randint(0, 19)
    cy = 10 + random.randint(0, 19)
    for y in range(height):
        for x in range(width):
            if cx < x < cx + 20 and cy < y < cy + 20:
                idx = (y * width + x) * 3
                image[idx] = 0
                image[idx + 1] = 0
                image[idx + 2] = 0

def write_bmp(filename, image):
    img_size = width * height * 3
    file_header = bytearray(14)
    info_header = bytearray(40)
    # File header
    file_header[0:2] = b'BM'
    file_header[2:6] = struct.pack('<I', 54 + img_size)
    file_header[6:10] = (0).to_bytes(4, 'little')
    file_header[10:14] = (54).to_bytes(4, 'little')
    # Info header
    info_header[0:4] = (40).to_bytes(4, 'little')
    info_header[4:8] = struct.pack('<i', width)
    info_header[8:12] = struct.pack('<i', -height)
    info_header[12:14] = (1).to_bytes(2, 'little')
    info_header[14:16] = (24).to_bytes(2, 'little')
    info_header[16:20] = (0).to_bytes(4, 'little')
    info_header[20:24] = struct.pack('<I', img_size)
    bmp = file_header + info_header + image
    os.makedirs(os.path.dirname(filename), exist_ok=True)
    with open(filename, 'wb') as f:
        f.write(bmp) # salva o arquivo imagem

qtdimagens = 120
for x in range(qtdimagens):
    filename = f"imagens/amostra{x:04d}.bmp"
    img = bytearray([255] * (width * height * 3))

    if x < qtdimagens // 2:
        circle(img) # metade das imagens contem circulo
    else:
        rect(img) # metade das imagens contem quadrado

    write_bmp(filename, img) # monta e salva a imagem

    print(f"{filename} - [{len(img) + 54} bytes]")

print("\nImagens salvas com sucesso")
