const fs = require('fs');

let linhas = [];

// 25 laranjas
for (let x = 0; x < 25; x++) {
  const especie = 'l';
  const peso = 0.082 + Math.random() / 100; // entre 0.082 e 0.092
  linhas.push(`${peso} ${especie}`);
}
// 25 frutas qualquer
for (let x = 0; x < 25; x++) {
  const especie = 'q';
  const peso = Math.random() * 2; // entre 0 e 2
  linhas.push(`${peso} ${especie}`);
}

fs.writeFileSync('entradas1.txt', linhas.join('\n'), 'utf-8');

// Leitura e exibição
const conteudo = fs.readFileSync('entradas1.txt', 'utf-8').split('\n');
conteudo.forEach((linha, x) => {
  const [peso, especie] = linha.split(' ');
  console.log(`${x}) ${peso} ${especie}`);
});
