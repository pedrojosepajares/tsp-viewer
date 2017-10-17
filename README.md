# Traveling Salesman Problem Viewer
La aplicación genera soluciones para el problema del viajante de comercio utilizando algoritmos de muy distintas familias. Es posible ver la evolución de la solución durante el proceso de construccuión de la misma. Este proyecto fue presentado como trabajo de fin de grado de ingeniería informática en la Universidad de Granada.

## Empezando
El sistema fue desarollado en un entorno Windows y está pensado para ser ejecutado en el mismo. También es posible utilizar la aplicación en un entorno Linux, como Ubuntu, haciendo uso de algunas herramientas.

## Prerrequisitos e instalación

### Windows
No hace falta realizar ningún paso previo para arrancar la aplicación

### Ubuntu
Es necesario instalar [Wine](https://www.winehq.org/) utilizando las instrucciones proporcionadas en su página web

## Ejecutando la aplicación

### Windows
Sólo es necesario hacer doble click en el ejecutable **HVCAH.exe** que se encuentra en el directorio */run*

### Ubuntu
Hay que emular el ejecutable de Windows **HVCAH.exe** utilizando Wine
 ```sh
wine ./run/HVCAH.exe
```

## Desarrollo
La aplicación ha sido desarrollado en un entorno Windows, utilizando [QtCreator](https://www.qt.io/qt-features-libraries-apis-tools-and-ide/#ide).
Los ficheros *.tsp* que contienen la especificación de cada problema han sido proporcionados por la ETSIIT de la Universidad de Granada.

## Tecnologías
Las tecnologías utilizadas para la construcción de este proyecto son:
* C++ - Lenguaje de desarrollo
* [QtCreator](https://www.qt.io/qt-features-libraries-apis-tools-and-ide/#ide) - IDE 
* [Qt](https://www.qt.io/) - Gestión de componentes gráficos de la aplicación, comunicación entre ellos y control de ejecuciones concurrentes
* [OpenCV](https://opencv.org/) - Creación de simulaciones en vídeo


