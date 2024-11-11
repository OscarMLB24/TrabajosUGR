/**
 * @file maxstack.h
 * @brief  Archivo de especificación del TDA MaxStack
 * @author Pablo Vargas Diaz
 */

#ifndef MAXSTACK_H
#define MAXSTACK_H

#include <queue>
#include <iostream>
using namespace std;

struct element {
 int value; // Current value to store
 int maximum; // Current max value in the structure
};

/*
  *@brief Sobrecarga del operador << del objeto element
  *@param salida Flujo de salida donde se presenta el resultado
  */
inline ostream& operator<<(ostream& salida,const element& obj) {
 salida << to_string(obj.value) << "|" << to_string(obj.maximum);
 return salida;
}


class MaxStack {

 queue<element> elements;
 priority_queue<int> max_values;

public:
 /*
  *@brief Constructor por defecto
  */
 MaxStack();
 /*
  *@brief Inserta un elemento en la parte superior de la pila
  *@param value Valor nuevamente introducido
 */
 void push(int value);
 /*
  *@brief Metodo que consulta el elemento en la parte superior de la pila permitiendo cambios
  *@pre La pila no puede estar vacía
  *@return Devuelve el ultimo elemento de la pila
 */
 element top();
 /*
  *@brief Metodo constante que consulta el elemento en la parte superior de la pila
  *@pre La pila no puede estar vacía
  *@return Devuelve una referencia constante ael ultimo elemento de la pila
 */
  const element top() const;
 /*
  *@brief Metodo que extrae el elemento de la parte superior de la pila
  *@pre La pila no puede estar vacía
 */
 void pop();
 /*
  *@brief Metodo que consulta el tamaño de la pila
  *@return Número de elementos de la pila
 */
 int size() const;
 /*
  * @brief Metodo que consulta si la pila está vacía
  * @return Devuelve si está vacía o no
 */
 bool empty() const;
};

#endif
