const fs = require('fs');

// Lê amostras
const amostras = JSON.parse(fs.readFileSync('entradas2.txt', 'utf-8'));

let bias = [Math.random(), Math.random(), Math.random()];
let finalBias = 40 + Math.random();

for (let x = 0; x < 1000000; x++) { //treina a rede milhares de vezes
  const a = amostras[Math.floor(Math.random() * 15)]; //uma laranja qualquer

  const caracteristica = [a.peso, a.volume, a.cor, a.posicao, a.textura, a.consistencia, a.temperatura, a.idade];

  let referencia = caracteristica.reduce((soma, v) => soma + v, 0);

  for (let t = 0; t < 3; t++) { //ajusta a camada intermediaria
    if (referencia > bias[t]) bias[t] += bias[t] * 0.000007; //um pouco a mais
    else if (referencia < bias[t]) bias[t] -= bias[t] * 0.000007; //um pouco a menos
  }

  let referenciaFinal = referencia * bias[0] + referencia * bias[1] + referencia * bias[2];

  if (referenciaFinal > finalBias) finalBias += finalBias * 0.000007; //ajusta um pouco para cima
  else if (referenciaFinal < finalBias) finalBias -= finalBias * 0.000007; //ajusta um pouco para menos

  console.log(`finalBias = ${finalBias}`);
}

// Salva os bias
fs.writeFileSync('bias1.txt', bias.map(b => b + '').join('\n') + '\n' + finalBias + '\n', 'utf-8');
