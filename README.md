# Traveling Salesman Problem Viewer
La aplicación genera soluciones para el [problema del viajante de comercio](https://es.wikipedia.org/wiki/Problema_del_viajante) utilizando algoritmos de muy distintas familias. Es posible ver la evolución de la solución durante el proceso de construccuión de la misma. Este proyecto fue presentado como trabajo de fin de grado de ingeniería informática en la Universidad de Granada.

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

## Realizando una simulación
A grandes rasgos, la aplicación resuelve un problema TSP a partir de una especificación proporcionada previamente y muestra los resultados. El sistema cuenta con varios algoritmos heurísticos, de distintas familias, para obtener las soluciones.

Tras arrancar la aplicación, se aprecian cuatro zonas diferenciadas en la interfaz principal:
1. Barra superior
2. Datos del problema
3. Ejecuciones
4. Resultados

Una simulación se realiza en varios pasos
1. **Lectura del fichero de especificación**. El usuario debe hacer click en *Archivo*, en la barra superior, y en *Nueva simulación*. En la interfaz de selección de ficheros hay que seleccionar una especificación para un problema TSP, contenida en un fichero con extensión *.tsp*. En el directorio *run/problemas TSP/* existen varios ficheros que se pueden utilizar.
Se puede observar en el apartado *Datos del problema* algunas características de la especificación seleccionada.

2. **Generación de ejecuciones**. Si el usuario hace click en el botón *Nueva simulación* del apartado *Ejecuciones* accede a un menú donde puede seleccionar qué algoritmos heurísticos desea que resuelva el problema y establecer criterios de parada para los mismos.
Tras hacer click en *Ejecutar* y esperar el tiempo oportuno, en el apartado *Ejecuciones* apareceran uno o varios items que se corresponden con las ejecuciones realizadas

3. **Representación de resultados**. El usuario puede elegir entre varios modos de representar las soluciones obtenidas mediante la ejecuciones
    * Paso a paso, viendo la solución actual para cada iteración del algoritmo
    * Mediante un gráfico de convergencia, donde se observa la distancia de la mejor solución obtenida en cada iteración del algoritmo
    * Evolución de la solución paso a paso en vídeo

## Desarrollo
La aplicación ha sido desarrollado en un entorno Windows, utilizando [QtCreator](https://www.qt.io/qt-features-libraries-apis-tools-and-ide/#ide).
Los ficheros *.tsp* que contienen la especificación de cada problema han sido proporcionados por la ETSIIT de la Universidad de Granada.

## Tecnologías
Las tecnologías utilizadas para la construcción de este proyecto son:
* C++ - Lenguaje de desarrollo
* [QtCreator](https://www.qt.io/qt-features-libraries-apis-tools-and-ide/#ide) - IDE 
* [Qt](https://www.qt.io/) - Gestión de componentes gráficos de la aplicación, comunicación entre ellos y control de ejecuciones concurrentes
* [OpenCV](https://opencv.org/) - Creación de simulaciones en vídeo


