const fs = require('fs');

let laranjacerto = 0, laranjaerrado = 0, qqrcerto = 0, qqrerrado = 0;

let bias, finalBias;

// Lê os bias
const linhas = fs.readFileSync('bias1.txt', 'utf-8').trim().split('\n');
bias = linhas.slice(0, 3).map(Number);
finalBias = parseFloat(linhas[3]);

for (let x = 0; x < 1000; x++) { //testa 1000 vezes
  let especie, peso, volume, cor, posicao, textura, consistencia, temperatura, idade;

  if (Math.random() < 0.5) { //cara ou coroa
    especie = 'l'; //laranja aleatoria
    peso = 0.8 + Math.random() / 10;
    volume = 0.7 + Math.random() / 10;
    cor = 0.6 + Math.random() / 10;
    posicao = 0.5 + Math.random() / 10;
    textura = 0.4 + Math.random() / 10;
    consistencia = 0.3 + Math.random() / 10;
    temperatura = 0.2 + Math.random() / 10;
    idade = 0.1 + Math.random() / 10;
  } else {
    especie = 'q'; //fruta qualquer
    peso = Math.random() * 2;
    volume = Math.random() * 2;
    cor = Math.random() * 2;
    posicao = Math.random() * 2;
    textura = Math.random() * 2;
    consistencia = Math.random() * 2;
    temperatura = Math.random() * 2;
    idade = Math.random() * 2;
  }

  let referencia = peso + volume + cor + posicao + textura + consistencia + temperatura + idade;

  let referenciaFinal = referencia * bias[0] + referencia * bias[1] + referencia * bias[2]; //calculo para comparar com o valor do finalBias

  let delta = referenciaFinal - finalBias;

  if (especie === 'l') {
    if (delta > -5 && delta < 5) laranjacerto++; else laranjaerrado++;
  } else {
    if (delta > -5 && delta < 5) qqrerrado++; else qqrcerto++;
  }
}

console.log(`\n${laranjacerto + laranjaerrado + qqrcerto + qqrerrado} tentativas:`);
console.log(`Esperado laranja dado laranja: ${laranjacerto}`);
console.log(`Esperado laranja dado qqr: ${laranjaerrado}`);
console.log(`Esperado qqr dado qqr: ${qqrcerto}`);
console.log(`Esperado qqr dado laranja: ${qqrerrado}\n`);
