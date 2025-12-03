const fs = require('fs');

// Lê amostras
const linhas = fs.readFileSync('entradas1.txt', 'utf-8').trim().split('\n');
const amostra = linhas.map(linha => {
  const [peso, especie] = linha.split(' ');
  return { peso: parseFloat(peso), especie };
});

// Inicializa bias aleatório
let bias = Math.random();

for (let x = 0; x < 4000; x++) { //ajusta o bias centenas de vezes
  const fruta = amostra[Math.floor(Math.random() * 25)]; //uma laranja aleatoria

  if (fruta.peso > bias) bias += bias * 0.01; //ajusta o bias um pouco a mais
  else if (fruta.peso < bias) bias -= bias * 0.01; //ajusta o bias um pouco a menos
}

console.log(`O valor que diferencia (bias): ${bias}`);
