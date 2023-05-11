const fs = require('fs').promises;

fs.writeFile('./writeme.txt', '네트워크 하고 시프다')
.then(() =>
{
    return fs.readFile('./writeme.txt');
})
.then((data) =>
{
    console.log(data.toString());
})
.catch((err) =>
{
    console.error(err);
})
