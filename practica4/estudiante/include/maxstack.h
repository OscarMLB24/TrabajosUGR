/**
 * @file maxstack.h
 * @brief  Archivo de especificación del TDA MaxStack
 * @author Pablo Vargas Diaz, Óscar Alfonso Mitillo López-Barajas
 */
include <queue>
include <priority_queue>
include <iostream>
using namespace std;


class MaxStack {

private:
 
 queue <int> elements;
 priority_queue <int> max_values;
 int n_elements;
 
public:

 /*
  * @brief Constructor por defecto del objeto maxstack
 */
 MaxStack();
 /*
  *@brief Inserta un elemento en la parte superior de la pila
 */
 void push();
 /*
  *@brief Metodo que consulta el elemento en la parte superior de la pila
  *@pre La pila no puede estar vacía
  *@return Devuelve el ultimo elemento de la pila
 */
 const& MaxStack top();
 /*
  *@brief Metodo que extrae el elemento de la parte superior de la pila
  *@pre La pila no puede estar vacía
 */
 void pop();
 /*
  *@brief Metodo que consulta el tamaño de la pila
  *@return Número de elementos de la pila
 */
 int n_elements();
 /*
  * @brief Metodo que consulta si la pila está vacía
  * @return Devuelve si está vacía o no
 */
 bool esta_vacia();

 /*
  *@brief Sobrecarga del operador <<
  *@param salida Flujo de salida donde se presenta el resultado
  */
 ostream& operator<<(ostream& salida);
};
