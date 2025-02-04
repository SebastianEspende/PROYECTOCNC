var express = require('express');
var router = express.Router();
const fileUpload = require('express-fileupload');

router.post('/', 
    fileUpload({ createParentPath: true }),
  (req, res) => {
    if (!req.files) {
      return res.status(400).send('No files were uploaded.');
    }
    
    const file = req.files.file;
    file.mv(`./uploads/${file.name}`, (err) => {
        if (err) {
          return res.status(500).send(err);
        }
        res.send(`File ${file.name} uploaded!`);
      });

      return res.status(200).send;

});

module.exports = router;
