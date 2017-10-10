#ifndef SOLUCION_H
#define SOLUCION_H

#include <vector>
#include <sstream>

using namespace std;

/**
 * @brief Conjunto de rutas donde cada una de ellas es la mejor que algoritmo había construido hasta ese momento. También encapsula los criterios de parada para la detencíon de la ejecución del algoritmo.
 */
class Solucion
{
public:
    /**
     * @brief Constrcutor por defecto.
     */
    Solucion();

    /**
     * @brief Constructor por parámetros
     * @param ruta Orden en el que se visitan las ciudades.
     * @param coste Coste del camino.
     */
    Solucion(vector<int> ruta, int coste);

    /**
     * @brief Operador utilizado para ordenar vectores de Soluciones.
     * @param sol_1 Solución.
     * @param sol_2 Solución.
     * @return  Verdadero si sol_1 es menos que sol_2
     */
    static bool menorQue(Solucion sol_1, Solucion sol_2){return sol_1 < sol_2;};

    /**
     * @brief Establece una ruta como ruta de la solución.
     * @param ruta Orden en el que se visitan las ciudades.
     */
    inline void setRuta(vector<int> ruta){this->ruta = ruta;}

    /**
     * @brief Establece un coste como coste de la solución.
     * @param coste oste del camino.
     */
    inline void setCoste(int coste){this->coste = coste;}

    /**
     * @brief Consultor de la ruta.
     * @return Ruta.
     */
    inline vector<int> getRuta(){return this->ruta;}

    /**
     * @brief Consultor del coste.
     * @return Coste.
     */
    inline int getCoste(){return this->coste;}

    /**
     * @brief Consultor de criterio de parada iteración del algoritmo.
     * @return Iteración del algoritmo.
     */
    inline int getIteracion(){return this->iteracion;}

    /**
     * @brief Consultor del criterio de parada evaluación de la función objetivo.
     * @return Evaluación de la función objetivo.
     */
    inline int getEvaluacion(){return this->evaluacion;}

    /**
     * @brief Consultor del criterio de parada tiempo.
     * @return Criterio de parada tiempo.
     */
    inline double getTiempo(){return this->tiempo;}

    /**
     * @brief Establece una iteración del algoritmo como criterio de parada de la solución.
     * @param iteracion Criterio de parada iteración del algoritmo.
     */
    inline void setIteracion(int iteracion){this->iteracion = iteracion;}

    /**
     * @brief Establece una evaluacines de la función objetivo como criterio de parada de la solución.
     * @param evaluacion Evaluaciones de la función objetivo.
     */
    inline void setEvaluacion(int evaluacion){this->evaluacion = evaluacion;}

    /**
     * @brief Establece tiempo como criterio de parada de la solución.
     * @param tiempo Tiempo.
     */
    inline void setTiempo(double tiempo){this->tiempo = tiempo;}

    /**
     * @brief Operador <
     * @param otra_solucion Solución
     * @return Verdadero si el propio objeto es menor que otra_solucion
     */
    bool operator <(Solucion otra_solucion);

    /**
     * @brief Operador >
     * @param otra_solucion Solución
     * @return Verdadero si el propio objeto es mayor que otra_solucion
     */
    bool operator >(Solucion otra_solucion);

    /**
     * @brief Operador ==
     * @param otra_solucion Solución
     * @return Verdadero si el propio objeto es igual que otra_solucion
     */
    bool operator ==(Solucion otra_solucion);

    /**
     * @brief Operador =
     * @param otra_solucion Solución.
     * @return El propio objeto.
     */
    Solucion operator =(Solucion otra_solucion);

    /**
     * @brief Genera una cadena con el contenido de la solución.
     * @return Cadena con el contenido de la solución.
     */
    string toString();


private:
    /**
     * @brief Ruta de la solución.
     */
    vector<int> ruta;

    /**
     * @brief Coste de la solución.
     */
    int coste;

    /**
     * @brief Criterio de parada iteración del algoritmo.
     */
    int iteracion;

    /**
     * @brief Criterio de parada evaluación de la función objetivo.
     */
    int evaluacion;

    /**
     * @brief Criterio de parada tiempo.
     */
    double tiempo;

};

#endif // SOLUCION_H
