const express = require('express');
const app = express();
const port = 9999;

app.use((req, res, next) => {
    console.log(req.path);
    next();
});

app.use(express.static('public'));

app.listen(port, () => {
    console.log('Server is running on : ${port}');
});
