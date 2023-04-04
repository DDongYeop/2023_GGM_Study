const {odd, even} = require('./1.js');
const CheckNum = require('./2.js');

function CheckStringOddOrEven(str)
{
    if (str.length%2)
        return odd;
    return even;
}

console.log(CheckNum(10));
console.log(CheckStringOddOrEven('Hello'));