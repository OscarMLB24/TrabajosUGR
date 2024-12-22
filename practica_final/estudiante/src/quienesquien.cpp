/**
 * @file quienesquien.h
 * @brief Fichero cabecera del QuienEsQuien.
 *
 * Almacena el arbol de preguntas para jugar al ?Quien es quien?.
 */

#ifndef _QUIENESQUIEN_H_
#define _QUIENESQUIEN_H_

#define DEBUG_QUIENESQUIEN 0

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <cassert>
#include <set>
#include <sstream>
#include <cmath>
#include "pregunta.h"
#include "bintree.h"
#include "ventana.h"
#include "consola.h"
#include "tablerografico.h"

using namespace std;

/**
 * @brief T.D.A. QuienEsQuien
 *
 * Conjunto de personajes con sus atributos.
 */
class QuienEsQuien{
private:
	/**
	  * @brief Almacena el nombre de los personajes. Su indice en
	  *        este vector corresponde con el indice de su
	  *        descripcion en el tablero.
	  */
	vector<string> personajes;

	 /**
      * @brief Almacena el nombre de las imagenes en disco de los  personajes. Su indice en
      *        este vector corresponde con el indice de su
      *        descripcion en el tablero.
      */
    vector<string> personajes_images;

	/**
	  * @brief Almacena los atributos.  Su indice en este vector
	  *        corresponde con el indice correspondiente de cada
	  *        vector del tablero.
	  */
	vector<string> atributos;

	/**
	  * @brief Matriz que almacena para cada personaje su valor para
	  *        cada atributo.
	  */
	vector<vector<bool>> tablero;

	/**
	  * @brief Arbol de preguntas para adivinar personajes.
	  */
	bintree<Pregunta> arbol;

	/**
	  * @brief Nodo del arbol de preguntas correspondiente a la jugada
	  *        actual.
	  */
	bintree<Pregunta>::node jugada_actual;

	 /**
     * @brief tg es el tablero grafico donde se muestra los personajes
     */
    TableroGrafico *tg;

    /**
     * @brief con consola para interactuar con el usuario
     */
    Consola *con;

    /**
     * @brief imagen_ocultar nombre de la imagen en disco para ocultar el personaje
     */
    string imagen_ocultar;

    /**
     * @brief modo_graph flag que indica si se usa el modelo grafico o solo texto
     */
    bool modo_graph;


	int mejor_atributo(vector<string> atributos,
						vector<bool> personajes_restantes,
						vector<vector<bool>> tablero,
						int restantes,
						vector<bool> & siCumplen,
						vector<bool> & noCumplen,
						int & numSiCumplen,
						int & numNoCumplen);

	/**
	  * @brief Esta es una propuesta de cabecera de la funcion para crear el arbol.
	  */
	bintree<Pregunta> crear_arbol(vector<string> atributos,
                                    vector<string> personajes,
                                    vector<bool> personajes_restantes,
                                    vector<vector<bool>> tablero);
public:
	/**
	  * @brief Constructor basico de la clase
	  */
	QuienEsQuien();
	/**
	  * @brief Constructor de copia.
	  * @param quienEsQuien QuienEsQuien a copiar.
	  */
	QuienEsQuien(const QuienEsQuien &quienEsQuien);
	/**
	  * @brief Destructor del pregunta.
	  */
	~QuienEsQuien();
	/**
	  * @brief Vacia todos los datos del QuienEsQuien receptor.
	  */
	void limpiar();
	/**
	* @brief Sobrecarga del operador de asignaci?n.
	* @param quienEsQuien objeto a copiar.
	* @return Referencia al objeto copiado.
	*/
	QuienEsQuien& operator = (const QuienEsQuien &quienEsQuien);

	/**
	  * @brief Operador de extraccion de flujo.
	  * @param is Stream de entrada
          * @param quienEsQuien Quien es quien a leer.
	  * @return Referencia al stream de entrada.
	  *
	  * Lee de @e is un quien es quien y lo almacena en @e
	  * quienEsQuien. El formato aceptado para la lectura es un TSV
	  * (tab-separated values) en el que las columnas tienen cabecera y
	  * son las preguntas. La ultima columna corresponde al nombre del
	  * personaje. Tras la cabecera se especifica en cada linea un
	  * personaje, teniendo el valor 1 o 0 si tiene/no tiene el
	  * atributo de la columna. En la ultima columna se da el
	  * nombre del personaje.
	  */
	friend istream& operator >> (istream& is, QuienEsQuien &quienEsQuien);

	/**
	  * @brief Operador de insercion de flujo.
	  * @param os Stream de salida
	  * @param quienEsQuien Quien es quien a escribir.
	  * @return Referencia al stream de salida.
	  *
	  * Escribe en @e is un quien es quien.
	  * El formato usado para la escritura es un TSV
	  * (tab-separated values) en el que las columnas tienen cabecera y
	  * son las preguntas. La ultima columna corresponde al nombre del
	  * personaje. Tras la cabecera se especifica en cada linea un
	  * personaje, teniendo el valor 1 o 0 si tiene/no tiene el
	  * atributo de la columna. En la ultima columna se da el
	  * nombre del personaje.
	  */
	friend ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien);

	/**
	  * @brief Escribe en la salida estandard las estructuras atributos, personajes y tablero.
	  */
	void mostrar_estructuras_leidas();

	/**
	  * @brief Este metodo construye el arbol de preguntas para todos los personajes del tablero.
	  */
	bintree<Pregunta> crear_arbol();

	/**
	  * @brief Sustituye el arbol actual por el arbol pasado por parametro.
	  *
	  * @param arbol_nuevo Arbol de preguntas que sustituye al actual.
	  *
	  */
	void usar_arbol(bintree<Pregunta> arbol_nuevo);

	/**
	  * @brief Escribe el arbol generado en la salida estandard.
	  */
	void escribir_arbol_completo() const;

	/**
	  * @brief Metodo que modifica el arbol de preguntas para que haya
	  *        preguntas redundantes.
	  * @post El arbol de preguntas se modifica.
	  */
	void eliminar_nodos_redundantes();

	/**
	  * @brief Inicializa el juego.
	  * @post  Si la partida anterior no habia terminado se
	  *        pierde el progreso.
	  */
	void iniciar_juego();

	/**
	  * @brief Dado un estado del tablero devuelve los nombres de
	  *        los personajes que aun no han sido tumbados en el
	  *        tablero.
	  *
	  * @param jugada_actual Nodo del estado del tablero.
	  *
	  * @return Conjunto de personajes que no han sido tumbados en el tablero.
	  *
	  * @pre El arbol del QuienEsQuien receptor debe haber sido construido previamente.
	  * @pre El nodo indicado debe ser un nodo del arbol del QuienEsQuien receptor.
	  */
	set<string> informacion_jugada(bintree<Pregunta>::node jugada_actual);

	/**
	  * @brief Este metodo permite calcular la media de la profundidad de las hojas del arbol.
	  * Este valor representa el numero (promedio) de preguntas necesarias para adivinar cada personaje.
	  * A menor profundidad promedio, mejor solucion.
	  *
	  * @return Profundidad media del arbol de preguntas.
	  *
	  * @pre El arbol de preguntas debe haber sido construido previamente.
	  */
	float profundidad_promedio_hojas();

	/**
	  * @brief Rellena los datos del QuienEsQuien con un tablero calculado aleatoriamente.
	  *
	  * @param numero_de_personajes Numero de personajes que tiene el tablero a crear.
	  */
	void tablero_aleatorio(int numero_de_personajes);

    /**
     * @brief setImagenOcultar Modifica el nombre de la imagen en disco para ocultar los personajes en modo
     * grafico
     * @param n:nombre del fichero en disco
     */
    void setImagenOcultar(const char * n);

    /**
     * @brief setModoGraph Modifica el modelo grafico
     * @param m: True si se desea modo grafico false solo texto
     */
    void setModoGraph(bool m);

     /**
     * @brief Oculta en el tablero grafico los personajes que no estan activos
     * @param personajes_activos: personajes que estan activos
     */
    void ocultar_personajes_graph(const set<string> &personajes_activos);

	/**
	 * @brief Imprime las preguntas ya formuladas y sus respectivas respuestas
	 * @param jugada nodo del que se quieren saber las preguntas anteriores
	 * @pre jugada != null
	 */
	void preguntas_formuladas(bintree<Pregunta>::node jugada);

	/**
	 * @brief Aniade un nuevo personaje al arbol
	 * @param nombre nombrer del personaje
	 * @param caracteristicas atributos del personaje
	 * @param nombre_imagen_personajes nombre de la imagen del personaje
	 */
	void aniade_personaje(string nombre, vector<bool> caracteristicas, string nombre_imagen_personaje="");

	/**
	* @brief Elimina un personaje del arbol y lo reestructura
	* @param nombre Nombre del personaje a eliminar
	* @pre El personaje a eliminar existe
	*/
	void elimina_personaje(string nombre);
};

#endif

