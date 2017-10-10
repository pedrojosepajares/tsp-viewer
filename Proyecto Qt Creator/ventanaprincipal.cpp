#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);

    // Se establece el nombre de la ventana
    this->setWindowTitle("Menú principal");

    // Vector que contiene los nombres de todos los algoritmos
    vector<string> nombres_algoritmos;

    // Inicialización de la lista de algoritmos
    inicializaAlgoritmos();

    // Se completa el vector de nombres de algoritmos
    for (unsigned int i=0; i<this->algoritmos.size(); i++){
        nombres_algoritmos.push_back(this->algoritmos[i]->getNombreAlgoritmo());
    }

    // Creación de la ventana de espera
    this->ventana_espera = new VentanaEspera();

    // Conexión entre pulsar el botón "Nueva ejecución" y el slot nuevaEjecucion()
    connect(ui->boton_nueva_ejecucion, SIGNAL(clicked()),this, SLOT(nuevaEjecucion()));

    // Conexión entre pulsar el botón "Eliminar ejecución" y el slot EliminarEjecucion()
    connect(ui->boton_eliminar_ejecucion, SIGNAL(clicked()),this, SLOT(eliminarEjecuciones()));

    // Conexión entre pulsar el botón "Eliminar todas" y el slot EliminarTodasEjecuciones()
    connect(ui->boton_eliminar_todo, SIGNAL(clicked()),this, SLOT(eliminarTodasEjecuciones()));

    // Conexión entre pulsar el botón "Representación de una solución" y el slot nuevaRepresentacionSolucion()
    connect(ui->boton_representacion_solucion, SIGNAL(clicked()),this, SLOT(nuevaRepresentacionSolucion()));

    // Conexión entre pulsar el botón "Gráfico de convergencia" y el slot nuevoGraficoConvergencia()
    connect(ui->boton_grafico_convergencia, SIGNAL(clicked()),this, SLOT(nuevaGraficoConvergencia()));

    // Conexión entre pulsar el botón "Representación en vídeo" y el slot nuevoVideo()
    connect(ui->boton_video, SIGNAL(clicked()),this, SLOT(nuevoVideo()));

    // Conexión entre pulsar la acción "Nueva Simulación" y el slot pulsadoNuevaSimulacion()
    connect(ui->accion_nueva_simulacion,SIGNAL(triggered()),this,SLOT(cambioFicheroProblema()));

    // Conexión entre pulsar la acción "Ayuda" y el slot pulsadoNuevaSimulacion()
    connect(ui->accion_ayuda,SIGNAL(triggered()),this,SLOT(abrirAyuda()));

    // Conexión entre pulsar la acción "Salir" y el slot quit()
    connect(ui->accion_salir,SIGNAL(triggered()),QApplication::instance(),SLOT(quit()));

    // Se inicializa la lista de algoritmos del ui y se inserta en su layout
    this->lista_ejecuciones = new ListaAlgoritmos(false);
    ui->layout_lista_ejecuciones->addWidget(lista_ejecuciones, Qt::AlignTop | Qt::AlignLeft);

    // Se actualiza el estado de activación de los componentes de la ventana
    this->actualizaComponentesVentana();
}

VentanaPrincipal::~VentanaPrincipal(){
    delete ui;

    // Delete del vector de algoritmos
    for (unsigned int i=0; i<this->algoritmos.size(); i++){
        delete this->algoritmos[i];
    }

    // Delete de la ventana de espera
    delete this->ventana_espera;

    // Delete del widget lista de ejecuciones
    delete this->lista_ejecuciones;
}

void VentanaPrincipal::inicializaAlgoritmos(){

    // Se crean nuevos algoritmos y se insertan en el vector de algoritmos
    this->algoritmos.push_back(new ACO());
    this->algoritmos.push_back(new GA());
    this->algoritmos.push_back(new GAAL());
    this->algoritmos.push_back(new GRASP());
    this->algoritmos.push_back(new ILS());
    this->algoritmos.push_back(new Insercion());
    this->algoritmos.push_back(new SA());
    this->algoritmos.push_back(new SAAL());
    this->algoritmos.push_back(new VecinoMasCercano());


    // Se insertan en el vector de nombres de algoritmos los nombres de todos los algoritmos
    // Se conecta cada algoritmo con la ventana principal para poder cancelar la ejecución de los mismos

    for (unsigned int i=0; i<this->algoritmos.size(); i++){
       this->nombres_algoritmos.push_back(this->algoritmos[i]->getNombreAlgoritmo());
        connect(this, SIGNAL(cancelaEjecucionAlgoritmo()),algoritmos[i], SLOT(ejecucionCancelada()));

    }
}

vector<QFuture<vector<Solucion> > > VentanaPrincipal::resolverVariosAlgoritmos(vector<int> id_algoritmos, vector<CriterioParada>& criterios_parada){
    // Vector que almacenará los conjuntos de soluciones resultantes de la ejecución de las sucesivas iteraciones
    // de cada algoritmo
    vector<QFuture<vector<Solucion> > > soluciones_algoritmos;

    // Para cada uno de los algoritmos que hay que ejecutar
    for (unsigned int i=0; i<id_algoritmos.size(); i++){
        // Según el entero que contenga id_algoritmos[i] se ejecuta el algoritmo correspondiente.
        // Las barras de progreso en la ventana se espera se van asignando según orden de llegada
        switch(id_algoritmos[i]){
            case C_ACO:
            soluciones_algoritmos.push_back(QtConcurrent::run((ACO*)this->algoritmos[C_ACO], &ACO::resolverCP, &criterios_parada[i], this->ventana_espera, i));
                break;

            case C_GA:
                soluciones_algoritmos.push_back(QtConcurrent::run((GA*)this->algoritmos[C_GA], &GA::resolverCP, &criterios_parada[i], this->ventana_espera, i));
                break;

            case C_GRASP:
                soluciones_algoritmos.push_back(QtConcurrent::run((GRASP*)this->algoritmos[C_GRASP], &GRASP::resolverCP, &criterios_parada[i], this->ventana_espera, i));
                break;

            case C_ILS:
                soluciones_algoritmos.push_back(QtConcurrent::run((ILS*)this->algoritmos[C_ILS], &ILS::resolverCP, &criterios_parada[i], this->ventana_espera, i));
                break;

            case C_INSERCION:
                soluciones_algoritmos.push_back(QtConcurrent::run((Insercion*)this->algoritmos[C_INSERCION], &Insercion::resolverCP, &criterios_parada[i], this->ventana_espera, i));
                break;

            case C_SA:
                soluciones_algoritmos.push_back(QtConcurrent::run((SA*)this->algoritmos[C_SA], &SA::resolverCP, &criterios_parada[i], this->ventana_espera, i));
                break;

            case C_VECINO:
                soluciones_algoritmos.push_back(QtConcurrent::run((VecinoMasCercano*)this->algoritmos[C_VECINO], &VecinoMasCercano::resolverCP, &criterios_parada[i], this->ventana_espera, i));
                break;

            case C_GAAL:
                soluciones_algoritmos.push_back(QtConcurrent::run((GAAL*)this->algoritmos[C_GAAL], &GAAL::resolverCP, &criterios_parada[i], this->ventana_espera, i));
                break;

            case C_SAAL:
                soluciones_algoritmos.push_back(QtConcurrent::run((SAAL*)this->algoritmos[C_SAAL], &SAAL::resolverCP, &criterios_parada[i], this->ventana_espera, i));
                break;
        }
    }

    return soluciones_algoritmos;
}

bool VentanaPrincipal::cancelaEjecucionesNoTerminadas(vector<QFuture<vector<Solucion> > > ejecuciones){
    bool hay_ejecuciones_canceladas = false;

    // Se comprueba se hay algoritmos que aún se estén ejecutando
    for (unsigned int i=0; i<ejecuciones.size() && !hay_ejecuciones_canceladas; i++){
        // Si hay alguna ejecución corriendo
        if (ejecuciones[i].isRunning()){
            // Se emite la señal para cancelar todas las ejecuciones
            emit cancelaEjecucionAlgoritmo();
            // pone la bandera a true
            hay_ejecuciones_canceladas = true;
        }
    }

    // Se espera a que las ejecuciones que están acabando lo hagan
    for (unsigned int i=0; i<ejecuciones.size() && hay_ejecuciones_canceladas; i++){
        ejecuciones[i].waitForFinished();
    }

    return hay_ejecuciones_canceladas;
}

void VentanaPrincipal::actualizaNuevasEjecuciones(vector<vector<Solucion> > soluciones_ejecuciones, vector<int> id_algoritmos, vector<CriterioParada> criterios_parada){
    Ejecucion ejecucion;
    string texto_algoritmo;
    stringstream stream_n_mejoras, stream_coste;

    // Para cada vector de soluciones y nombres de algoritmos
    for (unsigned int i=0; i<soluciones_ejecuciones.size(); i++){
        // Se añade la nueva ejecución al vector de ejecuciones de la ventana
        ejecucion.soluciones = soluciones_ejecuciones[i];
        ejecucion.id_algoritmo = id_algoritmos[i];

        //ejecucion.iteraciones = iteraciones;
        ejecucion.criterio_parada = &criterios_parada[i];

        ejecucion.nombre_algoritmo = this->nombres_algoritmos[id_algoritmos[i]];
        this->ejecuciones.push_back(ejecucion);
    }

    // Se añaden las nuevas ejecuciones a la lista de ejecuciones en la ventana
    for (unsigned int i=0; i<id_algoritmos.size(); i++){
        stream_n_mejoras.str("");
        stream_coste.str("");
        stream_n_mejoras << soluciones_ejecuciones[i].size()-1;
        stream_coste << soluciones_ejecuciones[i].back().getCoste();
        texto_algoritmo = this->nombres_algoritmos[id_algoritmos[i]] + " (" + stream_n_mejoras.str() +" mejoras, mejor coste: "+ stream_coste.str() + ")";
        this->lista_ejecuciones->agregaAlgoritmo(texto_algoritmo);
    }
}

void VentanaPrincipal::actualizaComponentesVentana(){
    // Si todavía no se ha leído ningún fichero de problemas
    if(this->datos_problema.getNumeroCiudades() == -1){
        ui->boton_nueva_ejecucion->setEnabled(false);
        ui->boton_eliminar_ejecucion->setEnabled(false);
        ui->boton_eliminar_todo->setEnabled(false);
        this->lista_ejecuciones->setEnabled(false);
        ui->boton_representacion_solucion->setEnabled(false);
        ui->boton_grafico_convergencia->setEnabled(false);
        ui->boton_video->setEnabled(false);
    }
    else{
        // Si no hay ejecuciones
        if(this->ejecuciones.empty()){
            ui->boton_nueva_ejecucion->setEnabled(true);
            ui->boton_eliminar_ejecucion->setEnabled(false);
            ui->boton_eliminar_todo->setEnabled(false);
            this->lista_ejecuciones->setEnabled(true);
            ui->boton_representacion_solucion->setEnabled(false);
            ui->boton_grafico_convergencia->setEnabled(false);
            ui->boton_video->setEnabled(false);

        }
        else{
            ui->boton_representacion_solucion->setEnabled(true);
            ui->boton_grafico_convergencia->setEnabled(true);
            ui->boton_eliminar_ejecucion->setEnabled(true);
            ui->boton_eliminar_todo->setEnabled(true);
            ui->boton_video->setEnabled(true);
        }
    }
}

void VentanaPrincipal::cambioFicheroProblema(){
    // Ruta sin modificar añadiendo el carácter de escape "/"
    QString ruta_simple;

    // Las que contiene las palabras de la ruta cuando se eliminan los separadores "/"
    QStringList palabras_ruta;

    this->ruta_fichero_problema = QFileDialog::getOpenFileName(this,
        tr("Seleccione fichero de especificación TSP"), "ejemplos", tr("Fichero de especificación TSP (*.tsp)"));
    if (this->ruta_fichero_problema != ""){
        ruta_simple = this->ruta_fichero_problema;

        // Se eliminan las ejecuciones que ya existían en el sistema
        this->eliminarTodasEjecuciones();

        // Se separa el nombre del fichero del resto de la ruta
        palabras_ruta = this->ruta_fichero_problema.split("/");
        this->nombre_problema = palabras_ruta.back();

        // Se convierte la ruta del fichero del problema en una ruta válida para abrir el fichero
        // procurando no añadir "\\" al final de la ruta

        this->ruta_fichero_problema.clear();
        for (int i=0; i<palabras_ruta.size(); i++){
            this->ruta_fichero_problema.push_back(palabras_ruta.value(i));
            if (palabras_ruta.value(i) != this->nombre_problema){
                this->ruta_fichero_problema.push_back("\\");
            }
        }

        // Se hace una lectura de los datos del problema
        this->datos_problema.leeFichero(this->ruta_fichero_problema.toStdString());

        // Se pasa a cada algoritmo la matriz de distancias entre ciudades
        for (unsigned int i=0; i<this->algoritmos.size(); i++){
            this->algoritmos[i]->setDistanciasCiudades(this->datos_problema.getDistanciasCiudades());

        }

        // Se reflejan en los labels los datos del problema
        ui->label_nombre_problema->setText(QString::fromStdString(this->datos_problema.getNombreProblema()));
        ui->label_numero_ciudades->setText(QString::number(this->datos_problema.getNumeroCiudades()));
        if (this->datos_problema.getDistanciaOptima() != -1){
            ui->label_optimo->setText(QString::number(this->datos_problema.getDistanciaOptima()));
        }

        // Actualiza los componentes de la ventana
        this->actualizaComponentesVentana();
    }
}

void VentanaPrincipal::abrirAyuda(){
    VentanaAyuda *v_ayuda = new VentanaAyuda();
    v_ayuda->exec();
}

void VentanaPrincipal::nuevaGraficoConvergencia(){
    // Indices de las ejecuciones selecionadas
    vector<int> indices_ejecuciones;
    // Ejecuciones a representar
    vector<Ejecucion> ejecuciones_seleccionadas;

    // Ventana para seleccionar los algoritmos que se desean representar
    VentanaSeleccionVariosAlgoritmos* v_seleccion_varios_algoritmos =
            new VentanaSeleccionVariosAlgoritmos(this->lista_ejecuciones) ;
    // Ventana donde se presenta un gráfico de convergencia con los algoritmos seleccionados
    VentanaGraficoConvergencia* v_grafico_convergencia;

    // Se ejecuta la ventana de seleccion y si se acepta se continúa la ejecución
    // y se ha seleccionado alguna opción
    if (v_seleccion_varios_algoritmos->exec() && v_seleccion_varios_algoritmos->getEjecucionesSeleccionadas().size() != 0){

        // Se obtienen las ejecuciones seleccionados
        indices_ejecuciones = v_seleccion_varios_algoritmos->getEjecucionesSeleccionadas();

        // Se completa el vector de ejecuciones seleccionadas a partir de los índices
        for (unsigned int i=0; i<indices_ejecuciones.size(); i++){
            ejecuciones_seleccionadas.push_back(this->ejecuciones[indices_ejecuciones[i]]);
        }

        // Generación de una nueva ventana que contiene el gráfico de convergencia
        v_grafico_convergencia = new VentanaGraficoConvergencia(ejecuciones_seleccionadas,
                                                            this->datos_problema.getNombreProblema());

        // Se ejecuta
        v_grafico_convergencia->exec();


        // Se libera memoria
        delete v_grafico_convergencia;
    }

    // Se libera memora
    delete v_seleccion_varios_algoritmos;
}

void VentanaPrincipal::nuevaRepresentacionSolucion(){
    // Índice para seleccionar en las ejecuciones la que contiene la solución que se desea representar
    int indice_ejecucion;
    // Ventana en la que se selecciona el algoritmos que se quiere representar
    VentanaSeleccionUnAlgoritmo* v_seleccion_un_algoritmo = new VentanaSeleccionUnAlgoritmo(this->ejecuciones);
    // Ventana en la que se representa la evolución de una ejecuión
    VentanaEvolucionSolucion* v_evolucion_solucion;

    // Se ejecuta la ventana y en el caso de que se acepte se continúa con la ejecución
    if(v_seleccion_un_algoritmo->exec()){

        // Se obtiene el índice seleccionado
        indice_ejecucion = v_seleccion_un_algoritmo->getEjecucionSeleccionada();

        // Se crea una nueva ventana con la ejecución correspondiente
        v_evolucion_solucion = new VentanaEvolucionSolucion(
                this->datos_problema.getPosicionesCiudades(),
                this->ejecuciones[indice_ejecucion],
                this->datos_problema.getNombreProblema());

        // Se ejecuta
        v_evolucion_solucion->exec();

        // Se libera memoria
        delete v_evolucion_solucion;
    }

    // Se libera memoria
    delete v_seleccion_un_algoritmo;
}

void VentanaPrincipal::nuevoVideo(){
    // Ventana de configuración del vídeo
    VentanaVideo* v_video = new VentanaVideo(&(this->ejecuciones));

    // Índice para seleccionar en las ejecuciones la que contiene la solución que se desea representar
    int indice_ejecucion;

    // Ventana en la que se selecciona el algoritmos que se quiere representar
    VentanaSeleccionUnAlgoritmo* v_seleccion_un_algoritmo = new VentanaSeleccionUnAlgoritmo(this->ejecuciones);

    // Frecuencia del vídeo
    double soluciones_por_segundo = 1;

    // Puntero al vídeo compuesto por la sucesión del imágenes del gráfico
    Video* video;

    // Puntero al gráfico del cuál se extraen las imágines para conforma el vídeo
    GraficoEvolucionSolucion* grafico;

    // Contiene las distintas palabras de la ruta que quedan cuando se eliminan los separadores
    QStringList palabras_ruta;

    // Nombre fichero
    QString nombre_fichero;

    // Ruta del fichero
    QString ruta;

    if (v_video->exec()){
        // Se genera un gráfico que es el que proporciona los mapas de píxeles al video
        indice_ejecucion = v_video->getIndiceEjecucion();
        grafico = new GraficoEvolucionSolucion(this->datos_problema.getPosicionesCiudades(),this->ejecuciones[indice_ejecucion],this->datos_problema.getNombreProblema());
        // Se genera el vídeo
        soluciones_por_segundo = (double)this->ejecuciones[indice_ejecucion].soluciones.size() / (double)v_video->getDuracionVideo();
        if (soluciones_por_segundo < 1){
            soluciones_por_segundo = 1;
        }
        video = new Video(grafico, soluciones_por_segundo, 600, 800);
        video->guardaVideo(v_video->getRuta().toStdString());
        delete video;
    }

    delete v_video;
}

void VentanaPrincipal::nuevaEjecucion(){
    // Nombres de los algoritmos seleccionados
    vector<string> nombres_algoritmos_seleccionados;
    // Índices de los algoritmos seleccionados para su ejecución
    vector<int> indices_algoritmos_seleccionados;
    // Contiene el vector de soluciones correspondientes a una ejecución para cada algoritmo
    vector<QFuture<vector<Solucion> > > resultado_ejecuciones_futuras;
    // Contiene el vector de soluciones correspondientes a una ejecución para cada algoritmos
    // una vez se extraen de las variables QFuture
    vector<vector<Solucion> > resultado_ejecuciones;
    // Criterios de parada
    vector<CriterioParada> criterios_parada;
    // Ventana en la que se seleccionan los algoritmos a ejecutar así como las iteraciones
    VentanaEjecucionAlgoritmos* v_seleccion_algoritmos =
            new VentanaEjecucionAlgoritmos(this->nombres_algoritmos);

    // Se ejecuta al ventana y se continúa la ejecución si el usuario ha aceptado
    if (v_seleccion_algoritmos->exec()){

        // Se obtiene la información proporcionada por la ventana
        indices_algoritmos_seleccionados = v_seleccion_algoritmos->getAlgoritmosAEjecutar();

        // Se completa el vector de nombres de algoritmos en función de los índices seleccionados
        for (unsigned int i=0; i<indices_algoritmos_seleccionados.size(); i++){
            nombres_algoritmos_seleccionados.push_back(
                        this->nombres_algoritmos[indices_algoritmos_seleccionados[i]]);
        }

        // Se generan los criterios de parada
        for (unsigned int i=0; i<indices_algoritmos_seleccionados.size(); i++){
            criterios_parada.push_back(CriterioParada(
                                           v_seleccion_algoritmos->getTiempo(),
                                           v_seleccion_algoritmos->getEvaluaciones(),
                                           v_seleccion_algoritmos->getIteraciones()));
        }

        // Se inicializan las barras de progreso de la ventana de espera
        this->ventana_espera->inicializaBarrasProgreso(nombres_algoritmos_seleccionados);

        // Ejecución de los algoritmos
        resultado_ejecuciones_futuras = this->resolverVariosAlgoritmos(indices_algoritmos_seleccionados, criterios_parada);

        // Se ejecuta la ventana de espera
        // Si todas las barras han llegado a 100
        if(this->ventana_espera->exec()){
            // Se espera a que todos los procesos concurrentes acaben y se separan de la
            // variable QFuture
            for (unsigned int i=0; i<resultado_ejecuciones_futuras.size(); i++){
                resultado_ejecuciones_futuras[i]. waitForFinished();
                resultado_ejecuciones.push_back(resultado_ejecuciones_futuras[i].result());

            }
            // Se actualizan las ejecuciones en la clase y en la interfaz
            this->actualizaNuevasEjecuciones(resultado_ejecuciones, indices_algoritmos_seleccionados, criterios_parada);

        }

        // En el caso de que la ventana de espera se haya cerrado sin concluir
        else{
            emit cancelaEjecucionAlgoritmo();
            // Se espera a que todos los procesos concurrentes acaben y se separan de la
            // variable QFuture
            for (unsigned int i=0; i<resultado_ejecuciones_futuras.size(); i++){
                resultado_ejecuciones_futuras[i]. waitForFinished();
            }
        }
    }

    // Se libera memoria
    delete v_seleccion_algoritmos;

    // Se actualiza la ventana
    this->actualizaComponentesVentana();
}

void VentanaPrincipal::eliminarEjecuciones(){
    // Se genera una nueva ventana de selección de varios algoritmos
    VentanaSeleccionVariosAlgoritmos* ventana_seleccion = new VentanaSeleccionVariosAlgoritmos(this->lista_ejecuciones);

    // Se ejecuta
    ventana_seleccion->exec();

    // Se obtienen las ejecuciones seleccionadas
    vector<int> ejecuciones_a_eliminar = ventana_seleccion->getEjecucionesSeleccionadas();

    // Vector de iteradores que apuntan a los elementos que se quieren borrar
    vector<vector<Ejecucion>::iterator> iteradores_a_eliminar;

    // Se completa el vector de iteradores
    for (unsigned int i=0; i<ejecuciones_a_eliminar.size(); i++){
        iteradores_a_eliminar.push_back(this->ejecuciones.begin() + ejecuciones_a_eliminar[i]-i);
    }

    // Se elimina las ejecuciones seleccionadas del vector de ejecuciones de la clase
    for (unsigned int i=0; i<ejecuciones_a_eliminar.size(); i++){
        this->ejecuciones.erase(iteradores_a_eliminar[i]);
    }

    // También se eliminan de la lista de ejecuciones de la interfaz
    this->lista_ejecuciones->eliminaVariosAlgoritmos(ejecuciones_a_eliminar);

    // Se elimina la ventana de selección
    delete ventana_seleccion;

    // Se actualiza la ventana
    this->actualizaComponentesVentana();
}

void VentanaPrincipal::eliminarTodasEjecuciones(){
    vector<int> ejecuciones_a_eliminar;

    // Se eliminan todas las ejecuciones de la lista de ejecuciones
    for (unsigned int i=0; i<this->ejecuciones.size(); i++){
        ejecuciones_a_eliminar.push_back(i);
    }
    this->lista_ejecuciones->eliminaVariosAlgoritmos(ejecuciones_a_eliminar);

    // Se eliminan las ejecuciones de la clase
    this->ejecuciones.clear();

    // Se actualiza la ventana
    this->actualizaComponentesVentana();

}

