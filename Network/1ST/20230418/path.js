const path = require('path');

console.log(path.join(__dirname, '1.js'));
console.log(path.join(__dirname, '..', '/1.js'));
console.log(path.resolve(__dirname, '..', '/1.js'));