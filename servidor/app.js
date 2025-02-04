var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var filesRouter = require('./routes/files');
const fileUpload = require('express-fileupload');
var app = express();
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
app.use('/files', filesRouter);
const port = 3000;

app.listen(port, ()=> console.log(`Dolphin app listening on port ${port}!`));
module.exports = app;
