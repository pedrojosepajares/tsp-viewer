#include "graficoevolucionsolucion.h"

GraficoEvolucionSolucion::GraficoEvolucionSolucion(const vector<vector<double> >& posiciones_ciudades, Ejecucion& ejecucion, const  string nombre_problema){
    // Variable que contiene los límites de los ejes
    vector<int> limites_x_y;

    int numero_ciudades = posiciones_ciudades.size();
    int numero_soluciones = ejecucion.soluciones.size();

    // Se utiliza para actualizar el título del gráfico
    stringstream indice_solucion_string;
    indice_solucion_string << 0;

    // Se actualizan los datos privados de la clase
    for (int i=0; i<numero_ciudades; i++){
        this->posiciones_ciudades.push_back(QPointF(posiciones_ciudades[i][0], posiciones_ciudades[i][1]));
    }
    this->soluciones = ejecucion.soluciones;
    this->nombre_algoritmo = QString::fromStdString(ejecucion.nombre_algoritmo);
    this->nombre_problema = QString::fromStdString(nombre_problema);

    // Se añaden las posiciones de las ciudades en el orden marcado por la solución con el objetivo de dibujar
    // los arcos entre ciudades correctamente
    this->arcos.resize(numero_soluciones);

    for (int n_sol = 0; n_sol<numero_soluciones; n_sol++){
        for(int i=0; i<numero_ciudades; i++){
            this->arcos[n_sol].push_back(this->posiciones_ciudades[this->soluciones[n_sol].getRuta()[i]]);
        }
        this->arcos[n_sol].push_back(this->posiciones_ciudades[this->soluciones[n_sol].getRuta()[0]]);
    }

    // Se añade el título para el gráfico
    QwtText titulo("Evolución de la solución para " + this->nombre_problema);
    QFont fuente_titulo = titulo.font();
    fuente_titulo.setBold(false);
    fuente_titulo.setPointSize(15);
    titulo.setFont(fuente_titulo);
    this->setTitle(titulo);


    // Se pone el fondo del gráfico a color blanco
    this->setCanvasBackground( Qt::white );

    // Cálculo y aplicación de los límites de los ejes en función de las posiciones de las ciudades
    limites_x_y = this->LimitesMaxMinXY();
    this->setAxisScale( QwtPlot::xBottom, limites_x_y[0]-1,limites_x_y[1]+1);
    this->setAxisScale( QwtPlot::yLeft, limites_x_y[2]-1, limites_x_y[3]+1);

    // Se desactivan los ejes para que no se vean
    this->enableAxis(QwtPlot::yLeft, false);
    this->enableAxis(QwtPlot::xBottom, false);

    // Las ciudades se representan como una elipse coloreada y se realizan algunos ajustes en la forma en la
    // cual se observan los arcos que las unen
    this->simbolo_ciudad = new QwtSymbol( QwtSymbol::Ellipse, QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    this->linea_union_ciudades = new QwtPlotCurve();
    this->linea_union_ciudades->setSymbol( this->simbolo_ciudad );
    this->linea_union_ciudades->setPen( Qt::blue, 1 ),
    this->linea_union_ciudades->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    // Se hace que la línea represente los arcos de la primera solución que unen las ciudades
    this->linea_union_ciudades->setSamples( this->arcos[0] );
    // Se añade al gráfico
    this->linea_union_ciudades->attach( this );

    // Se establece el índice de la solución actual reflejada en el gráfico a cero
    this->indice_solucion_grafico = 0;

    // Se calcula la altura y la anchura del gráfico
    this->altura_grafico = this->height();
    this->anchura_grafico = this->width();
}

GraficoEvolucionSolucion::~GraficoEvolucionSolucion(){
    delete this->linea_union_ciudades;
}

void GraficoEvolucionSolucion::actualiza(){

    stringstream indice_solucion_string;
    indice_solucion_string << (int)this->indice_solucion_grafico;

    // Se añade el título para el gráfico
    QwtText titulo("Evolución de la solución para " + this->nombre_problema);
    QFont fuente_titulo = titulo.font();
    fuente_titulo.setBold(false);
    fuente_titulo.setPointSize(15);
    titulo.setFont(fuente_titulo);
    this->setTitle(titulo);

    // Se hace que la línea conecte
    this->linea_union_ciudades->setSamples( this->arcos[this->indice_solucion_grafico] );
    // Se añade al gráfico
    this->linea_union_ciudades->attach( this );
    // Se redibuja el gráfico
    this->replot();
    this->repaint();
}

void GraficoEvolucionSolucion::avanza(){
    // Si no se ha llegado al último gráfico
    if (this->indice_solucion_grafico < this->soluciones.size()-1){
        this->indice_solucion_grafico++;
        this->actualiza();
    }

}

void GraficoEvolucionSolucion::avanza(double porcentaje){
    // Si no se ha llegado al último gráfico
    this->indice_solucion_grafico = (this->soluciones.size()*porcentaje) / 100;
    actualiza();
}

void GraficoEvolucionSolucion::retrocede(){
    // Si no se ha llegado al último gráfico
    if (this->indice_solucion_grafico > 0){
        this->indice_solucion_grafico--;
        this->actualiza();
    }

}

void GraficoEvolucionSolucion::play(){
    while(this->indice_solucion_grafico < this->soluciones.size()-1){
        this->avanza();
        Sleep(1000);
    }
}

QPixmap GraficoEvolucionSolucion::getImagen(int ancho, int alto){
    stringstream indice_solucion_string, coste_solucion_string;
    indice_solucion_string << this->indice_solucion_grafico;
    coste_solucion_string << this->soluciones.at(this->indice_solucion_grafico).getCoste();
    this->resize(ancho, alto);
    this->actualiza();
    this->setTitle(QwtText("Solución para " + this->nombre_problema + " (" + this->nombre_algoritmo + " mejora "+ QString::fromStdString(indice_solucion_string.str()) + ", coste: "
                           + QString::fromStdString(coste_solucion_string.str()) +")"));
    return QWidget::grab();
}

vector<int> GraficoEvolucionSolucion::LimitesMaxMinXY(){

    vector<int> v_min_max;
    int max_x, min_x;
    int max_y, min_y;

    max_x = min_x = this->posiciones_ciudades[0].x();
    max_y = min_y = this->posiciones_ciudades[0].y();

    for (unsigned int i=1; i<this->posiciones_ciudades.size(); i++){
        if(max_x < this->posiciones_ciudades[i].x()){max_x = this->posiciones_ciudades[i].x();}
        if(min_x > this->posiciones_ciudades[i].x()){min_x = this->posiciones_ciudades[i].x();}
        if(max_y < this->posiciones_ciudades[i].y()){max_y = this->posiciones_ciudades[i].y();}
        if(min_y > this->posiciones_ciudades[i].y()){min_y = this->posiciones_ciudades[i].y();}
    }

    v_min_max.push_back(min_x);
    v_min_max.push_back(max_x);
    v_min_max.push_back(min_y);
    v_min_max.push_back(max_y);

    return v_min_max;
}
