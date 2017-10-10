Estructura del directorio:


	- HVCAH: Herramienta para la Visualización de Algoritmos Heurísticos. 
	Ejecutable de la herramienta.

	- ayuda: directorio que contiene los ficheros HTML donde está expresada la ayuda.
	También contiene los ficheros de ayuda comprimidos y la especificación de los mismos.

	-ficheros config: ficheros de configuración de los algoritmos heurísticos con los
	que cuenta la HVCAH. Estos ficheros son opcionales. En caso de no existir la herramienta
	suministra a los algoritmos unos parámetros por defecto.

	-problemas TSP: ficheros de especificación de problemas TSP. Pueden ser cargados
	desde la herramienta para resolverlos.

	-platforms: contiene un fichero dll que es imprescindible para la ejecución de la
	herramienta en Windows

	-resto de ficheros dll: bibliotecas de enlace dinámico necesarias para la 
	ejecución de la herramienta.

	-vídeo de ejemplo: vídeo de ejemplo generado por la herramienta donde se observa
	el proceso de resolución del problema kroA100 mediante SA.