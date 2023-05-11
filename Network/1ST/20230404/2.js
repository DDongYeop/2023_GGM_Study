const {odd, even} = require('./1.js');

function CheckOddOrEven(num)
{
    if (num % 2)
        return odd;
    return even;
}

module.exports = CheckOddOrEven;