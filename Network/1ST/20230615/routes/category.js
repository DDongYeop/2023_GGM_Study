const express = require('express');
const router = express.Router();

router.get('/park', (req, res) =>
{
    res.render('../views/title.html', {title: '박부부성성이'});
});

router.get('/:name', (req, res) =>
{
    res.send(`hello ${req.params.name}`);
});

module.exports = router;
