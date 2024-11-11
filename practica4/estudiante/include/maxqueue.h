/**
 * @file maxqueue.h
 * @brief  Archivo de especificación del TDA MaxQueue
 * @author Pablo Vargas Diaz, Oscar Alfonso Mitillo López-Barajas
 */

#include <list>
#include <iostream>
using namespace std;


struct Element {
    int value;
    int maximum;
};

ostream& operator<< (ostream& os, Element element);

class MaxQueue {

private:

    list<Element> elements;

public:

    /*----------------------------------------------------------------------------------------------------------------*/
    /*
     * @brief constructor por defecto del objeto MaxQueue
    */
    MaxQueue();
    /*----------------------------------------------------------------------------------------------------------------*/
    /*
    * @brief metodo que comprueba si la cola esta vacia
    * @return devuelve true si la cola no tiene elementos, false en otro caso
    */
    bool empty() const;
    /*----------------------------------------------------------------------------------------------------------------*/
    /*
     *@brief metodo que consulta el tamaño de la cola
     *@return devuelve el numero de elementos en la cola
    */
    int size() const;
    /*----------------------------------------------------------------------------------------------------------------*/
    /*
     *@brief metodo que consulta el elemento "mas antiguo" de la cola, al principio de ella
     *@pre la cola no puede estar vacia
     *@return devuelve el primer elemento de la cola
    */
    const Element& front() const;
    /*----------------------------------------------------------------------------------------------------------------*/
    /*
     *@brief mmetodo que consulta el elemento "mas reciente" de la cola, al final de ella
     *@pre la cola no puede estar vacia
     *@return devuelve el ultimo elemento de la cola
    */
    const Element& back() const;
    /*----------------------------------------------------------------------------------------------------------------*/
    /*
     *@brief metodo que inserta un elemento al final de la cola
     *@param newValue: elemento a insertar
    */
    void push(int newValue);
    /*----------------------------------------------------------------------------------------------------------------*/
    /*
     *@brief metodo que elimina el elemento "mas antiguo" de la cola, al principio de ella
     *@pre la cola no puede estar vacia
    */
    void pop();
    /*----------------------------------------------------------------------------------------------------------------*/
    /*
     *@brief metodo que intercambia el contenido de la cola por otra
     *@pre la cola no puede estar vacia
    */
    void swap(MaxQueue& newQueue);
    /*----------------------------------------------------------------------------------------------------------------*/
    /*
     *@brief sobrecarga del operador <<
     *@param salida(parametro de salida): flujo de salida donde se presenta el resultado
     */
    ostream& operator<<(ostream& salida) const;
    /*----------------------------------------------------------------------------------------------------------------*/
};
 
