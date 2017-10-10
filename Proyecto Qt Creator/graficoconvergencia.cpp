#include "graficoconvergencia.h"

GraficoConvergencia::GraficoConvergencia(vector<Ejecucion>& ejecuciones, const string nombre_problema){
    QString titulo_grafico;
    vector<QwtPlotCurve*> curvas;
    vector<qreal> datos_ajuste_eje;
    QPointF punto_auxiliar;
    int coste_auxiliar;
    int numero_curvas = ejecuciones.size();
    this->nombre_problema = QString::fromStdString(nombre_problema);
}

GraficoConvergencia::GraficoConvergencia(vector<Ejecucion>* ejecuciones, const string nombre_problema){
    // Se utiliza para dibujar la línea del final de las curvas
    QPen pen;

    // Se asignan a la variable de la clase las ejecuciones
    this->ejecuciones = ejecuciones;

    this->nombre_problema = QString::fromStdString(nombre_problema);

    // Se asignan valores iniciales para las variables máximas y mínimas
    this->max_tiempo = this->min_tiempo = ejecuciones->at(0).soluciones.back().getTiempo();
    this->max_evaluaciones = this->min_evaluaciones = ejecuciones->at(0).soluciones.back().getEvaluacion();
    this->max_iteraciones = this->min_iteraciones = ejecuciones->at(0).soluciones.back().getIteracion();
    this->min_coste = this->max_coste = ejecuciones->at(0).soluciones.back().getCoste();
    this->peor_coste_inicial = ejecuciones->at(0).soluciones.front().getCoste();
    this->algoritmo_mejor_coste = QString::fromStdString(ejecuciones->at(0).nombre_algoritmo);
    this->algoritmo_peor_coste = QString::fromStdString(ejecuciones->at(0).nombre_algoritmo);



    // Para cada uno de conjuntos de puntos correspondientes a una ejecución
    for (unsigned int i=0; i<ejecuciones->size(); i++){


        // Cálculo de los valores máximos
        if (ejecuciones->at(i).soluciones.back().getTiempo() > this->max_tiempo){
            this->max_tiempo = ejecuciones->at(i).soluciones.back().getTiempo();
        }

        if (ejecuciones->at(i).soluciones.back().getEvaluacion() > this->max_evaluaciones){
            this->max_evaluaciones = ejecuciones->at(i).soluciones.back().getEvaluacion();
        }

        if (ejecuciones->at(i).soluciones.back().getIteracion() > this->max_iteraciones){
            this->max_iteraciones = ejecuciones->at(i).soluciones.back().getIteracion();
        }

        // Cálculo de los valores mínimos
        if (ejecuciones->at(i).soluciones.front().getTiempo() < this->min_tiempo){
            this->min_tiempo = ejecuciones->at(i).soluciones.front().getTiempo();
        }

        if (ejecuciones->at(i).soluciones.front().getEvaluacion() < this->min_evaluaciones){
            this->min_evaluaciones = ejecuciones->at(i).soluciones.front().getEvaluacion();
        }

        if (ejecuciones->at(i).soluciones.front().getIteracion() < this->min_iteraciones){
            this->min_iteraciones = ejecuciones->at(i).soluciones.front().getIteracion();
        }

        // Se agrega un nuevo conjunto de puntos
        this->conjuntos_puntos_tiempo.push_back(QPolygonF());
        this->conjuntos_puntos_evaluaciones.push_back(QPolygonF());
        this->conjuntos_puntos_iteraciones.push_back(QPolygonF());



        // Se añade el primer punto, con el coste de la primera solución y el tiempo = 0
        this->conjuntos_puntos_tiempo[i].append(
                    QPointF(0, ejecuciones->at(i).soluciones[0].getCoste()));
        this->conjuntos_puntos_evaluaciones[i].append(
                    QPointF(0, ejecuciones->at(i).soluciones[0].getCoste()));
        this->conjuntos_puntos_iteraciones[i].append(
                    QPointF(0, ejecuciones->at(i).soluciones[0].getCoste()));

        // Para cada una de las soluciones en una ejecución
        for (unsigned int j=0; j<ejecuciones->at(i).soluciones.size(); j++){

            // Se añade al conjunto de puntos el punto correspondiente al coste/tiempo
            this->conjuntos_puntos_tiempo[i].append(
                        QPointF(ejecuciones->at(i).soluciones[j].getTiempo(), ejecuciones->at(i).soluciones[j].getCoste()));
            this->conjuntos_puntos_evaluaciones[i].append(
                        QPointF(ejecuciones->at(i).soluciones[j].getEvaluacion(), ejecuciones->at(i).soluciones[j].getCoste()));
            this->conjuntos_puntos_iteraciones[i].append(
                        QPointF(ejecuciones->at(i).soluciones[j].getIteracion(), ejecuciones->at(i).soluciones[j].getCoste()));

            // Se existe la siguiente solución
            if (j+1 < ejecuciones->at(i).soluciones.size()){
                // Se añade otro punto extra para que el gráfico tome la forma correcta
                this->conjuntos_puntos_tiempo[i].append(
                        QPointF(ejecuciones->at(i).soluciones[j+1].getTiempo(), ejecuciones->at(i).soluciones[j].getCoste()));
                this->conjuntos_puntos_iteraciones[i].append(
                        QPointF(ejecuciones->at(i).soluciones[j+1].getIteracion(), ejecuciones->at(i).soluciones[j].getCoste()));
                this->conjuntos_puntos_evaluaciones[i].append(
                        QPointF(ejecuciones->at(i).soluciones[j+1].getEvaluacion(), ejecuciones->at(i).soluciones[j].getCoste()));
            }
        }

        // Cálculo del coste máximo
        if (ejecuciones->at(i).soluciones.back().getCoste() > this->max_coste){
            this->max_coste = ejecuciones->at(i).soluciones.back().getCoste();
            this->algoritmo_peor_coste = QString::fromStdString(ejecuciones->at(i).nombre_algoritmo);
        }

        // Cálculo del coste mínimo
        if (ejecuciones->at(i).soluciones.back().getCoste() < this->min_coste){
            this->min_coste = ejecuciones->at(i).soluciones.back().getCoste();
            this->algoritmo_mejor_coste = QString::fromStdString(ejecuciones->at(i).nombre_algoritmo);

        }

        // Cálculo del peor coste inicial
        if (ejecuciones->at(i).soluciones.front().getCoste() > this->peor_coste_inicial){
            this->peor_coste_inicial = ejecuciones->at(i).soluciones.front().getCoste();
        }
    }

    // Ajustes en el gráfico
    // Título
    // Se añade el título para el gráfico
    QwtText titulo("Convergencia del coste de las soluciones a " + this->nombre_problema);
    QFont fuente_titulo = titulo.font();
    fuente_titulo.setBold(false);
    fuente_titulo.setPointSize(15);
    titulo.setFont(fuente_titulo);
    this->setTitle(titulo);
    // Fondo de color blanco
    this->setCanvasBackground( Qt::white );
    // Eje de abscisas
    this->setAxisScale( QwtPlot::xBottom, this->min_tiempo, this->max_tiempo);
    this->setAxisAutoScale(0);
    this->setAxisTitle(QwtPlot::xBottom, "Tiempo (s)");
    // Eje de ordenadas
    this->setAxisScale( QwtPlot::yLeft, this->min_coste,this->peor_coste_inicial);
    this->setAxisAutoScale(1);
    this->setAxisTitle(QwtPlot::yLeft, "Coste");

    // Leyenda
    this->insertLegend( new QwtLegend() );
    // Redimensionado del gráfico
    this->resize(600,400);


    // Para cada una de las curvas que se pueden formar a partir de los conjuntos de puntos
    for (unsigned int i=0; i<this->conjuntos_puntos_tiempo.size(); i++){
        // Se añade una nueva curva
        this->curvas.push_back(new QwtPlotCurve());

        // Se agregan los puntos a la última curva añadida
        this->curvas.back()->setSamples( this->conjuntos_puntos_tiempo[i]);

        // Se selecciona un color distinto para cada curva, el tipo de renderizado, se le
        // añade un nombre a la curva, se agrega la leyenda y se redimensiona el gráfico
        this->curvas.back()->setPen(QColor( Qt::GlobalColor( Qt::red+i ) ), 1);
        this->curvas.back()->setRenderHint( QwtPlotItem::RenderAntialiased, true );
        this->curvas.back()->setTitle(QString::fromStdString(ejecuciones->at(i).nombre_algoritmo));

        // Se añade esta curva al gráfico
        this->curvas.back()->attach( this );

    }

    // Se añade a cada curva los dos puntos restantes para completar el gráfico hasta el máximo de tiempo
    // Para cada uno de conjuntos de puntos correspondientes a una ejecución
    for (unsigned int i=0; i<ejecuciones->size(); i++){

        // Se agrega un nuevo conjunto de puntos
        this->conjuntos_puntos_final_tiempo.push_back(QPolygonF());
        this->conjuntos_puntos_final_evaluaciones.push_back(QPolygonF());
        this->conjuntos_puntos_final_itereaciones.push_back(QPolygonF());


        // Se añade el primer punto, igual al último del conjunto de puntos correspondiente
        this->conjuntos_puntos_final_tiempo[i].append(this->conjuntos_puntos_tiempo[i].back());
        this->conjuntos_puntos_final_evaluaciones[i].append(this->conjuntos_puntos_evaluaciones[i].back());
        this->conjuntos_puntos_final_itereaciones[i].append(this->conjuntos_puntos_iteraciones[i].back());


        // Se añade el segundo punto, con el mismo coste que el anterior añadido y el máximo tiempo
        this->conjuntos_puntos_final_tiempo[i].append(QPointF(this->max_tiempo, this->conjuntos_puntos_tiempo[i].back().y()));
        this->conjuntos_puntos_final_evaluaciones[i].append(QPointF(this->max_evaluaciones, this->conjuntos_puntos_evaluaciones[i].back().y()));
        this->conjuntos_puntos_final_itereaciones[i].append(QPointF(this->max_iteraciones, this->conjuntos_puntos_iteraciones[i].back().y()));

    }

    // Se añaden los finales de las curvas
    for (unsigned int i=0; i<this->conjuntos_puntos_final_tiempo.size(); i++){

        // Se añade una nueva curva
        this->curvas_final.push_back(new QwtPlotCurve());

        // Se agregan los puntos a la última curva añadida
        this->curvas_final.back()->setSamples( this->conjuntos_puntos_final_tiempo[i]);


        pen.setColor(QColor( Qt::GlobalColor( Qt::red+i )));
        pen.setStyle(Qt::DashLine);
        this->curvas_final.back()->setPen(pen);
        this->curvas_final.back()->setRenderHint( QwtPlotItem::RenderAntialiased, true );

        // No se muestra en la leyenda
        this->curvas_final.back()->setItemAttribute( QwtPlotItem::Legend, false );

        // Se añade esta curva al gráfico
        this->curvas_final.back()->attach( this );
    }
}

void GraficoConvergencia::cambioEje(int tipo) {

    // Se cambia el eje de abcisas
    switch(tipo){
    case 0:
        this->setAxisScale( QwtPlot::xBottom, this->min_tiempo, this->max_tiempo);
        this->setAxisTitle(QwtPlot::xBottom, "Tiempo (s)");

        break;

    case 1:
        this->setAxisScale( QwtPlot::xBottom, this->min_evaluaciones, this->max_evaluaciones);
        this->setAxisTitle(QwtPlot::xBottom, "Evaluaciones");

        break;

    case 2:
        this->setAxisScale( QwtPlot::xBottom, this->min_iteraciones, this->max_iteraciones);
        this->setAxisTitle(QwtPlot::xBottom, "Iteraciones");

        break;
    }

    // Para cada una de las curvas
    for (unsigned int i=0; i<this->curvas.size(); i++){
        switch(tipo){
        case 0:
            this->curvas[i]->setSamples(this->conjuntos_puntos_tiempo[i]);
            this->curvas_final[i]->setSamples(this->conjuntos_puntos_final_tiempo[i]);
            break;

        case 1:
            this->curvas[i]->setSamples(this->conjuntos_puntos_evaluaciones[i]);
            this->curvas_final[i]->setSamples(this->conjuntos_puntos_final_evaluaciones[i]);
            break;


        case 2:
            this->curvas[i]->setSamples(this->conjuntos_puntos_iteraciones[i]);
            this->curvas_final[i]->setSamples(this->conjuntos_puntos_final_itereaciones[i]);
            break;
        }
    }

    this->replot();
    this->repaint();

}

vector<qreal> GraficoConvergencia::getDatosAjusteEje(){
    vector<qreal> datos_ajuste_eje;
    qreal mayor_coste;
    qreal menor_coste;
    qreal mayor_momento;
    QPolygonF aux_polygon;
    QPointF aux_punto;

    /*mayor_coste = menor_coste = ((QPointF)this->conjuntos_puntos[0][0]).y();
    mayor_momento = ((QPointF)this->conjuntos_puntos[0][0]).x();

    for (unsigned int i=0; i < this->conjuntos_puntos.size(); i++){
        aux_polygon = this->conjuntos_puntos[i];
        for (int j=0; j<aux_polygon.size(); j++){
            aux_punto = aux_polygon[j];

            if (mayor_coste < aux_punto.y()){
                mayor_coste =  aux_punto.y();
            }

            if (menor_coste > aux_punto.y()){
                menor_coste =  aux_punto.y();
            }

            if (mayor_momento < aux_punto.x()){
                mayor_momento =  aux_punto.x();
            }

        }
    }

    datos_ajuste_eje.push_back(mayor_coste);
    datos_ajuste_eje.push_back(menor_coste);
    datos_ajuste_eje.push_back(mayor_momento);*/

    return datos_ajuste_eje;
}
