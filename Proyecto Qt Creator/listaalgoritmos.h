#ifndef LISTAALGORITMOS_H
#define LISTAALGORITMOS_H

#include <QListWidget>
#include <QWidget>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief Panel que presenta un conjunto de objetos que pueden ser seleccionables.
 */
class ListaAlgoritmos : public QListWidget{
public:
    /**
     * @brief Constructor por parámetros.
     * @param lista_nombres_algoritmos Vector de nombres de objetos.
     * @param checkable Verdadero si los objetos son seleccionables.
     * @param parent Padre.
     */
    ListaAlgoritmos(vector<string> lista_nombres_algoritmos, bool checkable = true, QWidget* parent = 0);

    /**
     * @brief Constructor por parámetros.
     * @param checkable Verdadero si los objetos son seleccionables.
     * @param parent Padre.
     */
    ListaAlgoritmos(bool checkable = true, QWidget* parent = 0);

    /**
     * @brief Constructor de copia.
     * @param otra_lista Objeto a copiar.
     * @param checkable Verdadero si los objetos son seleccionables.
     * @param parent Padre.
     */
    ListaAlgoritmos(ListaAlgoritmos* otra_lista, bool checkable = true, QWidget* parent = 0);

    /**
     * @brief Incluye un nuevo objeto en la lista.
     * @param texto_algoritmo Nombre del objeto.
     */
    void agregaAlgoritmo(string texto_algoritmo);

    /**
     * @brief Elimina un objeto.
     * @param Índice que ocupa el objeto a eliminar en la lista de objetos.
     */
    void eliminaAlgoritmo(int posicion);

    /**
     * @brief Elimina un conjunto de objetos.
     * @param posiciones Índice que ocupan los objetos a eliminar en la lista de objetos.
     */
    void eliminaVariosAlgoritmos(vector<int> posiciones);


    /**
     * @brief Calcula los índices de los objetos seleccionados.
     * @return Índices de los objetos seleccionados.
     */
    vector<int> getAlgoritmosSeleccionados();

    /**
     * @brief Pone todos los objetos de lista como no seleccionados.
     */
    void deseleccionaAlgoritmos();

private:
    /**
     * @brief Verdadero cuando los objetos de la lista son seleccionables.
     */
    bool checkable;
};

#endif // LISTAALGORITMOS_H
