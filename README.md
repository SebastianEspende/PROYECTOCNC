# TALADRO CNC
### Introduccion

Este proyecto fue pensado y realizado con el fin de diseñar y construir un enrutador CNC de bajo costo, su 
principal función es agujerear placas PCB de producción caseras por estudiantes. Con este dispositivo se 
busca facilitar el proceso de la creación de proyectos que requieran placas electrónicas, permitiendo al 
usuario una mayor precisión y eficiencia en la perforación de placas, en comparación con los métodos 
manuales. Este proyecto también tiene como objetivo fomentar el aprendizaje practico de tecnologías CNC, 
de la electrónica y programación, con el fin de que sea una herramienta útil para los proyectos de electrónica 
y robótica.

#### Repositorio
- En el mismo se encuentran todos los recursos utilizados, como la parte electronica: donde se incluyen los diagramas y circuitos; los diseños 3D de las piezas utilizadas; y el codigo de programacion.
- No se incluyen las librerias, estas estaran al final de este archivo, algunas solo el nombre y otras en enlace a la pagina de donde provienen.

## Software

Se utiliza GRBL 1.1h, se incluye su link en el apartado de librerias

El codigo del ESP32 esta incluido por completo en este repositorio

## Para el futuro
A aquellos que les toque continuar nuestro proyecto, nos gustaria saberlo, les dejamos nuestros mails para que puedan contarnos, o si tienen alguna pregunta:
- espendesebastian@gmail.com
- josemcoronado671@gmail.com

### Palabras de precaución
los pines no son aleatorios, es importante que si quieren cambiarlo tengan en cuenta los grupos o puertos de los pines de un Arduino, si entran al cpu_map de GRBL se daran cuenta de lineas como esta para los 
pines que tienen algo en común como step de cada motor, dir de cada motor, limit switches, etc; 

```javascript
#define STEP_DDR        DDRD
#define STEP_PORT       PORTD
```
DDRD y PORTD no son solo nombres, se refieren al grupo de pines utiliado por los STEP en este caso, otro ejemplo
```javascript
#define DIRECTION_DDR     DDRD
#define DIRECTION_PORT    PORTD
```
Ambos utilizan el grupo D, que son del pin 0 al 7.
Grupo B utiliza pin 8 al 13.
es por eso que la declaracion de pines pareciera incorrecta, ejemplo 
#define X_LIMIT_BIT      1
Que utiliza el pin 9 pero se declara como 1, esto se debe a que utiliza el grupo B.


Para que la comunicacion entre el ESP32 y el Arduino funcione, tienen que tener el mismo GND, o al menos, conectarlos

### Librerias

- https://lcdmenu.forntoh.dev/overview/getting-started.html#installation
- https://github.com/gnea/grbl/releases/tag/v1.1h.20190825
