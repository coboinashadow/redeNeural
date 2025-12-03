const fs = require('fs');
const path = require('path');

const imagens = 120;
let amostra = new Array(imagens).fill(0);

let circulocerto = 0, circuloerrado = 0, quadradocerto = 0, quadradoerrado = 0;

for (let i = 0; i < imagens; i++) {
  const buf = fs.readFileSync(`imagens/amostra${i.toString().padStart(4, '0')}.bmp`);
  // BMP header tem 54 bytes, o resto é imagem 60x60x3
  let soma = 0;
  for (let j = 54; j < buf.length; j++) {
    soma += buf[j];
  }
  amostra[i] = soma;
}

// Lê bias2.txt
const bias = parseFloat(fs.readFileSync('bias2.txt', 'utf-8'));

for (let x = 0; x < 1000; x++) { //testa 1000 vezes
  const img = Math.floor(Math.random() * imagens); //uma imagem qualquer

  if (amostra[img] > bias) {
    if (img < imagens / 2) circulocerto++;
    else circuloerrado++;
  } else {
    if (img > imagens / 2) quadradocerto++;
    else quadradoerrado++;
  }
}

console.log(`\n${circulocerto + circuloerrado + quadradocerto + quadradoerrado} tentativas:`);
console.log(`Esperado circulo dado circulo: ${circulocerto}`);
console.log(`Esperado circulo dado quadrado: ${circuloerrado}`);
console.log(`Esperado quadrado dado quadrado: ${quadradocerto}`);
console.log(`Esperado quadrado dado circulo: ${quadradoerrado}\n`);
