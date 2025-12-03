const fs = require('fs');

// Lê amostras
const amostras = JSON.parse(fs.readFileSync('entradas2.txt', 'utf-8'));

let bias = Math.random();

for (let x = 0; x < 600000; x++) { //treina a rede milhares de vezes
  const a = amostras[Math.floor(Math.random() * 15)]; //uma laranja qualquer

  const referencia = a.peso+ a.volume+ a.cor+ a.posicao+ a.textura+ a.consistencia+ a.temperatura+ a.idade;

  if (referencia > bias) bias += bias * 0.000007; //um pouco a mais
  else if (referencia < bias) bias -= bias * 0.000007; //um pouco a menos

  console.log(`finalBias = ${bias}`);
}

// Salva os bias
fs.writeFileSync('bias1.txt', '' + bias, 'utf-8');
