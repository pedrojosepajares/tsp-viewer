#include "ListaAlgoritmos.h"

ListaAlgoritmos::ListaAlgoritmos(vector<string> lista_nombres_algoritmos, bool checkable, QWidget* parent): QListWidget(parent){
    Qt::ItemFlags banderas;
    this->checkable = checkable;
    for (unsigned int i=0; i<lista_nombres_algoritmos.size(); i++){
        QListWidgetItem* item = new QListWidgetItem(QString(lista_nombres_algoritmos[i].c_str()));
        banderas = item->flags();
        if (this->checkable){
            banderas |= Qt::ItemIsUserCheckable;
        }
        banderas &= ~Qt::ItemIsSelectable;
        item->setFlags(banderas); // Permite que se pueda hacer check en el item
        if (this->checkable){
            item->setCheckState(Qt::Unchecked); // Inicializa a unchecked el estado inicial del item
        }
        this->addItem(item);
    }
}

ListaAlgoritmos::ListaAlgoritmos(bool checkable, QWidget *parent): QListWidget(parent){
    this->checkable = checkable;
}

ListaAlgoritmos::ListaAlgoritmos(ListaAlgoritmos* otra_lista,  bool checkable, QWidget *parent) : QListWidget(parent){
    Qt::ItemFlags banderas;
    this->checkable = checkable;
    vector<QString> lista_nombres_algoritmos;
    // Para cada uno de los elementos de la lista se guardan en el vector de nombres
    for (int i=0; i<otra_lista->count(); i++){
        lista_nombres_algoritmos.push_back(otra_lista->item(i)->text());
    }

    // Se incluyen en la clase los items
    for (unsigned int i=0; i<lista_nombres_algoritmos.size(); i++){
        QListWidgetItem* item = new QListWidgetItem(lista_nombres_algoritmos[i]);
        banderas = item->flags();
        if (this->checkable){
            banderas |= Qt::ItemIsUserCheckable;
        }
        banderas &= ~Qt::ItemIsSelectable;
        item->setFlags(banderas); // Permite que se pueda hacer check en el item
        if (this->checkable){
            item->setCheckState(Qt::Unchecked); // Inicializa a unchecked el estado inicial del item
        }
        this->addItem(item);
    }
}


void ListaAlgoritmos::agregaAlgoritmo(string texto_algoritmo){
    Qt::ItemFlags banderas;
    QListWidgetItem* item = new QListWidgetItem(QString(texto_algoritmo.c_str()));
    banderas = item->flags();
    banderas |= Qt::ItemIsUserCheckable;
    banderas &= ~Qt::ItemIsSelectable;
    item->setFlags(banderas); // Permite que se pueda hacer check en el item
    if (this->checkable){
        item->setCheckState(Qt::Unchecked); // Inicializa a unchecked el estado inicial del item
    }
    this->addItem(item);
}

void ListaAlgoritmos::eliminaAlgoritmo(int posicion){
    delete this->item(posicion);
}

void ListaAlgoritmos::eliminaVariosAlgoritmos(vector<int> posiciones){
    // Vector que almacena punteros a los elementos a borrar
    vector<QListWidgetItem*> punteros_borrar;

    // Se guardan punteros a los elementos a borrar
    for (unsigned int i=0; i<posiciones.size(); i++){
        punteros_borrar.push_back(this->item(posiciones[i]));
    }

    // Se eliminan
    for (unsigned int i=0; i<posiciones.size(); i++){
        delete punteros_borrar[i];
    }
}

vector<int> ListaAlgoritmos::getAlgoritmosSeleccionados(){
    vector<int> indices_seleccionados;
    vector<QListWidgetItem*> items;

    // Para todos los items
    for (int i=0; i<this->count(); i++){
        // Si un item está seleccionado
        if(this->item(i)->checkState() == Qt::Checked){
            // Inserta su posición en el vector de índices de items seleccionados
            indices_seleccionados.push_back(i);
        }
    }
    return indices_seleccionados;
}

void ListaAlgoritmos::deseleccionaAlgoritmos(){
    // Para todos los items
    for (int i=0; i<this->count(); i++){
        // Si un item está seleccionado
        if(this->item(i)->checkState() == Qt::Checked){
            // Lo deselecciona
            this->item(i)->setCheckState(Qt::Unchecked);
        }
    }
}
