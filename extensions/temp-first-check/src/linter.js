const fs = require('fs');

const fileName = process.argv[2];
if (!fileName) {
  console.error('No file specified');
  process.exit(1);
}

const exampleLintOutput = `2:4: Example warning message in ${fileName}\n3:10: Another example error`;

console.log(exampleLintOutput);
