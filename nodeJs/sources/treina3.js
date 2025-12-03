const fs = require('fs');

const imagens = 120;
let amostra = new Array(imagens).fill(0);

for (let i = 0; i < imagens; i++) {
  const buf = fs.readFileSync(`imagens/amostra${i.toString().padStart(4, '0')}.bmp`);
  let soma = 0;
  for (let j = 54; j < buf.length; j++) {
    soma += buf[j];
  }
  amostra[i] = soma;
}

let bias = 1;

for (let x = 0; x < 300000; x++) { //treina milhares de vezes

  const alguma = Math.floor(Math.random() * imagens); //uma imagem qualquer

  if (amostra[alguma] > bias) bias += bias * 0.0001; //um pouco a mais
  else if (amostra[alguma] < bias) bias -= bias * 0.0001; //um pouco a menos

  console.log(`finalBias: ${bias}`);
}

fs.writeFileSync('bias2.txt', `${bias}\n`, 'utf-8');
