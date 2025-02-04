// Importa los módulos necesarios
var express = require("express"); // Framework web para Node.js
var router = express.Router(); // Enrutador de Express
var path = require("path"); // Módulo para trabajar con rutas de archivos
var fs = require("fs"); // Módulo para trabajar con el sistema de archivos

// Define las rutas
router.get("/", function (req, res) {
  // Lee el archivo data.json
  fs.readFile(path.join(__dirname, "..", "data.json"), function (err, data) {
    if (err) {
      console.error(err); // Imprime el error en la consola del servidor
      return res.status(500).send("Error leyendo el archivo data.json"); // Envía una respuesta de error 500
    }
    try {
      // Parsea el contenido del archivo JSON
      let contenido = JSON.parse(data);

      // Ordena los archivos por fecha de subida (la más reciente primero)
      let sortedData = Object.keys(contenido) // Obtiene las claves (nombres de archivo) del objeto
        .sort((a, b) => new Date(b.uploadDate) - new Date(a.uploadDate)) // Ordena las claves comparando las fechas de subida
        .reduce((acc, curr) => { // Reduce el array de claves a un nuevo objeto manteniendo el orden
          acc[curr] = contenido[curr]; // Asigna el valor original a la clave ordenada
          return acc;
        }, {});

      // Obtiene un array con los nombres de los archivos ordenados
      let nombres = Object.keys(sortedData);
      res.json(nombres); // Envía la lista de nombres como respuesta en formato JSON
    } catch (parseError) {
      console.error("Error parseando data.json:", parseError); // Imprime el error de parseo
      return res.status(500).send("Error parseando el archivo JSON."); // Envía una respuesta de error 500
    }
  });
});

router.get("/download/:filename", (req, res) => {
  const filename = req.params.filename; // Obtiene el nombre del archivo desde los parámetros de la URL
  const filePath = path.join(__dirname, "..", "uploads", filename); // Construye la ruta completa al archivo

  // Verifica si el archivo existe
  if (!fs.existsSync(filePath)) {
    return res.status(404).send("Archivo no encontrado."); // Envía una respuesta 404 si el archivo no existe
  }
  // Descarga el archivo
  res.download(filePath, filename, (err) => {
    if (err) {
      console.error(err);
      return res.status(500).send("Error descargando el archivo."); // Envía una respuesta 500 si hay un error durante la descarga
    }
  });
});

router.post("/", (req, res) => {
  // Verifica si se subió algún archivo
  if (!req.files) {
    return res.status(400).send("No se subieron archivos."); // Envía una respuesta 400 si no se subieron archivos
  }

  let uploadedFile = req.files.file; // Obtiene el archivo subido 

  // Mueve el archivo subido a la carpeta "uploads"
  uploadedFile.mv(
    path.join(__dirname, "..", "uploads", uploadedFile.name),
    (err) => {
      if (err) {
        return res.status(500).send(err); // Envía una respuesta 500 si hay un error al mover el archivo
      }

      // Verifica si existe el archivo data.json, si no lo crea vacío.
      fs.access(path.join(__dirname, "..", "data.json"), (err) => {
        if (err) {
          fs.writeFile("data.json", JSON.stringify({}, null, 2), (err) => {
            if (err) {
              console.error(err);
              return res.status(500).send("Error creando el archivo data.json"); // Envía una respuesta 500 si hay un error al crear el archivo
            }
            console.log("NUEVO ARCHIVO DE BASE DE DATOS JSON CREADO"); // Mensaje en la consola
          });
        }
      });

      // Lee el archivo data.json para agregar la información del nuevo archivo
      fs.readFile(
        path.join(__dirname, "..", "data.json"),
        "utf8",
        (err, fileContent) => {
          if (err) {
            console.error(err);
            return res.status(500).send("Error leyendo el archivo de base de datos"); // Envía una respuesta 500 si hay un error al leer el archivo
          }
          let data = {};
          try {
            data = JSON.parse(fileContent); // Parsea el contenido del archivo JSON
          } catch (parseError) {
            console.error("Error parseando data.json:", parseError);
            return res.status(500).send("Error parseando el archivo JSON."); // Envía una respuesta 500 si hay un error al parsear el archivo
          }

          // Agrega la información del archivo subido al objeto data
          data[uploadedFile.name] = {
            size: uploadedFile.size, // Tamaño del archivo
            location: path.join(
              __dirname,
              "..",
              "uploads",
              uploadedFile.name // Ruta completa al archivo
            ),
            uploadDate: new Date().toISOString(), // Fecha de subida en formato ISO
          };

          // Escribe el objeto data actualizado en el archivo data.json
          fs.writeFile("data.json", JSON.stringify(data, null, 2), (err) => {
            if (err) {
              return res.status(500).send("Error escribiendo el archivo"); // Envía una respuesta 500 si hay un error al escribir el archivo
            }
            console.log("JSON ACTUALIZADO"); // Mensaje en la consola
            res.send("¡Archivo subido exitosamente!"); // Envía una respuesta de éxito
          });
        }
      );
    }
  );
});

module.exports = router; // Exporta el enrutador