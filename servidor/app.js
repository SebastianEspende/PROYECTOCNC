var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
<<<<<<< HEAD
var filesRouter = require('./routes/files');
const fileUpload = require('express-fileupload');
var app = express();
=======
var usersRouter = require('./routes/users');

var app = express();
const fileUpload = require('express-fileupload');
>>>>>>> c57fea8db6fed42fead1b7035eccb23a59c29767
app.use(logger('dev'));
app.use( fileUpload({
    createParentPath: true,
  })
);
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
<<<<<<< HEAD
app.use('/archivos', filesRouter);
const port = 3000;

app.listen(port, ()=> console.log(`Dolphin app listening on port ${port}!`));
module.exports = app;
=======
app.use('/users', usersRouter);

const port = 3000;

app.listen(port, ()=> console.log(`Dolphin app listening on port ${port}!`));
module.exports = app;
>>>>>>> c57fea8db6fed42fead1b7035eccb23a59c29767
