const express = require('express')();
const app = express();
const PORT = 8080;
app.use(express.json());
app.listen(
    PORT,
    () => console.log(`Server is running on port ${PORT}`)
);

app.get('/tshirt', (req, res) => {
    res.status(200).send({
        size: 'Medium',
        color: 'Red',
        design: 'Floral',
        price: 20.00
    })
});

app.post('/tshirt/:id', (req, res) => {
    const { id } = req.params;
    const { size, color, design, price } = req.body;
    if (!size || !color || !design || !price) {
        res.status(418).send({ message: 'Invalid'});
    }
    res.send({
        tshirt: '${size}, ${color}, ${design}, ${price}',
    });
})