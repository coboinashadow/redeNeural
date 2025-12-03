const fs = require('fs');
const path = require('path');

const width = 60;
const height = 60;

function circle(image) {
  const radius = 10;
  const cx = 20 + Math.floor(Math.random() * 20);
  const cy = 20 + Math.floor(Math.random() * 20);
  for (let y = 0; y < height; y++) {
    for (let x = 0; x < width; x++) {
      const dx = x - cx;
      const dy = y - cy;
      if (dx * dx + dy * dy <= radius * radius) {
        const idx = (y * width + x) * 3;
        image[idx] = 0;
        image[idx + 1] = 0;
        image[idx + 2] = 0;
      }
    }
  }
}

function rect(image) {
  const cx = 10 + Math.floor(Math.random() * 20);
  const cy = 10 + Math.floor(Math.random() * 20);
  for (let y = 0; y < height; y++) {
    for (let x = 0; x < width; x++) {
      if (x > cx && x < cx + 20 && y > cy && y < cy + 20) {
        const idx = (y * width + x) * 3;
        image[idx] = 0;
        image[idx + 1] = 0;
        image[idx + 2] = 0;
      }
    }
  }
}

// Função para escrever BMP 24 bits (simples)
function writeBMP(filename, imageBuffer) {
  const fileHeader = Buffer.alloc(14);
  const infoHeader = Buffer.alloc(40);
  const imgSize = width * height * 3;
  // File header
  fileHeader.write('BM');
  fileHeader.writeUInt32LE(54 + imgSize, 2);
  fileHeader.writeUInt32LE(0, 6);
  fileHeader.writeUInt32LE(54, 10);
  // Info header
  infoHeader.writeUInt32LE(40, 0);
  infoHeader.writeInt32LE(width, 4);
  infoHeader.writeInt32LE(-height, 8); // top-down
  infoHeader.writeUInt16LE(1, 12);
  infoHeader.writeUInt16LE(24, 14);
  infoHeader.writeUInt32LE(0, 16);
  infoHeader.writeUInt32LE(imgSize, 20);

  const bmp = Buffer.concat([fileHeader, infoHeader, imageBuffer]);
  fs.mkdirSync(path.dirname(filename), { recursive: true });
  fs.writeFileSync(filename, bmp);
}

const qtdimagens = 120;
for (let x = 0; x < qtdimagens; x++) {
  const filename = `imagens/amostra${x.toString().padStart(4, '0')}.bmp`;

  let img = Buffer.alloc(width * height * 3, 255);

  if (x < qtdimagens / 2) circle(img); //metade das imagens contem circulo
  else rect(img); //metade das imagens contem quadrado

  writeBMP(filename, img);

  console.log(`${filename} - [${img.length + 54} bytes]`);
}
console.log('\nImagens salvas com sucesso');
