var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
<<<<<<< HEAD
  res.render('index', { title: 'Expresssss' });
=======
  res.render('index', { title: 'Express' });
>>>>>>> c57fea8db6fed42fead1b7035eccb23a59c29767
});

module.exports = router;
