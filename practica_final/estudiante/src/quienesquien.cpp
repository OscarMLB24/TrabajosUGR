#include "../include/quienesquien.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <algorithm>

QuienEsQuien::QuienEsQuien(){
}

QuienEsQuien::QuienEsQuien(const QuienEsQuien &quienEsQuien){
}

QuienEsQuien& QuienEsQuien::operator= (const QuienEsQuien &quienEsQuien){
     return *this;
}

QuienEsQuien::~QuienEsQuien(){
     this->limpiar() ;
}

void QuienEsQuien::limpiar(){
     this->personajes.clear();
     this->atributos.clear();
     this->personajes_images.clear();
     for(vector<vector<bool>>::iterator it_tablero = this->tablero.begin();
         it_tablero != this->tablero.end();
         it_tablero++){
          (*it_tablero).clear();
     }
     this->tablero.clear();
     this->arbol.clear() ;
}

template <typename T>
std::ostream& operator<<  (std::ostream& out, const std::vector<T>& v) {
     if ( !v.empty() ) {
          out <<  '[' ;
          std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
          out <<  "\b\b]";
     }

     return out;
}

void QuienEsQuien::mostrar_estructuras_leidas(){
     cout <<  "personajes: " <<  (this->personajes) <<  endl;
     cout <<  "atributos: " <<  (this->atributos) <<  endl;
     cout <<  "tablero:    " <<  endl;
     // Escribe la cabecera del tablero
     for(vector<string>::iterator it_atributos = this->atributos.begin() ;
         it_atributos != this->atributos.end() ;
         it_atributos++){
          cout <<  *it_atributos << "\t";
     }
     cout << endl;

     int indice_personaje = 0;
     for(vector<vector<bool>>::iterator it_tablero_atributos = tablero.begin();
         it_tablero_atributos!= tablero.end();
         it_tablero_atributos++){
          string personaje = this->personajes[indice_personaje];
          int indice_atributo = 0;
          for(vector<bool>::iterator it_atributos_personaje = (*it_tablero_atributos).begin();
              it_atributos_personaje != (*it_tablero_atributos).end() ;
              it_atributos_personaje++){
               cout <<  *it_atributos_personaje<< "\t";
               indice_atributo++;
          }
          cout <<  personaje <<  endl;
          indice_personaje++;
     }
}

/**
  * @brief Devuelve una copia de la cadena original sin las subcadenas no deseadas.
  *
  * @param cadena_original Cadena de la que se eliminan las subcadenas no deseadas.
  * @param cadena_a_eliminar Subcadena que se busca y se elimina.
  *
  * @return Copia de la cadena original sin las subcadenas no deseadas.
  */

string limpiar_string(string cadena_original,string cadena_a_eliminar){
     string linea(cadena_original);
     while(linea.find_first_of(cadena_a_eliminar) != std::string::npos){
          linea.erase(linea.find_first_of(cadena_a_eliminar),cadena_a_eliminar.length());
     }

     return linea;
}

istream& operator >>  (istream& is, QuienEsQuien &quienEsQuien) {

     quienEsQuien.limpiar();

     if(is.good()){ //Lee la linea con los nombres de las columnas
          string linea;
          getline(is, linea, '\n');
          linea = limpiar_string(linea,"\r");
          bool salir=false;
          while(!salir && linea.find('\t') != string::npos ){
               string atributo = linea.substr(0,linea.find('\t'));
               quienEsQuien.atributos.push_back(atributo);
               linea = linea.erase(0,linea.find('\t')+1);
               if (linea.substr(0,linea.find('\t'))=="Nombre personaje")
                   salir=true;
          }
     }
     //LEE los atributos para cada personaje
     while(is.good()) {
          string linea;
          getline(is, linea, '\n');
          linea = limpiar_string(linea,"\r");

          //Si la linea contiene algo extrae el personaje.
          //Si no la ignora.
          if(linea != ""){;
               vector<bool> atributos_personaje;
               int indice_atributo=0;
               bool salir=false;
               while(!salir && linea.find('\t') != string::npos){
                   string valor = linea.substr(0,linea.find('\t'));
                   if (valor == "0" || valor == "1"){
                    bool valor_atributo = valor == "1";
                    atributos_personaje.push_back(valor_atributo);
                    linea = linea.erase(0,linea.find('\t')+1) ;
                    indice_atributo++;
                   }
                   else{
                       salir=true;
                   }
               }
               string nombre_personaje;
               string imagen_personaje;
               if (linea.find('\t') == string::npos){
                nombre_personaje = linea;
                imagen_personaje=""; //no tiene imagen
               }
               else{
                nombre_personaje=linea.substr(0,linea.find('\t'));
                linea = linea.erase(0,linea.find('\t')+1) ;
                imagen_personaje=linea;

               }
               quienEsQuien.personajes.push_back(nombre_personaje);
               quienEsQuien.tablero.push_back(atributos_personaje);
               quienEsQuien.personajes_images.push_back(imagen_personaje);
          }
     }

     quienEsQuien.mostrar_estructuras_leidas();
     quienEsQuien.arbol = quienEsQuien.crear_arbol();
     quienEsQuien.tg=nullptr; //puntero al tablero grafico
     quienEsQuien.con=nullptr; //puntero a la consola
     if (quienEsQuien.modo_graph){
        int nper = quienEsQuien.personajes.size();
        int nrows,ncols=3;
        if (nper<8)
           nrows = nper/ncols;
        else{
            ncols=4;
            nrows = nper/ncols;
        }
        //se crea un tablero grafico
        quienEsQuien.tg = new TableroGrafico(400,400,nrows,ncols);
        //ponemos en el tablero grafico las im?genes
        for (int i=0;i<nper;i++){

            quienEsQuien.tg->putImagen(i/ncols,i%ncols,quienEsQuien.personajes_images[i].c_str());
        }
        //creamos la consola
        quienEsQuien.con=new Consola();
     }
     return is;
}

ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien){
     //Escribimos la cabecera, que contiene los atributos y al final una columna para el nombre

     cout<<"NUmero de Atributos "<<quienEsQuien.atributos.size()<<endl;
     for(vector<string>::const_iterator it_atributos = quienEsQuien.atributos.begin();
         it_atributos != quienEsQuien.atributos.end();
         it_atributos++){
          os << *it_atributos << "\t";
     }

     os << "Nombre personaje" << endl;
     
     //Rellenamos con ceros y unos cada linea y al final ponemos el nombre del personaje.
     for(int indice_personaje=0;indice_personaje<quienEsQuien.personajes.size();indice_personaje++){
          for(int indice_atributo=0;indice_atributo<quienEsQuien.atributos.size();indice_atributo++){
               os << quienEsQuien.tablero[indice_personaje][indice_atributo] << "\t";
          }
          os << quienEsQuien.personajes[indice_personaje] << endl;
     }
     
     return os;
}

/**
* @brief Convierte un numero a un vector de bool que corresponde
*        con su representadon en binario con un numero de digitos
*              f i j o.
*
* @param n Numero a convertir en binario.
* @param digitos Numero de digitos de la representaddn binaria.
*
* @return Vector de booleanos con la representadon en binario de @e n
*      con el numero de elementos especificado por @e digitos.
*/
vector<bool> convertir_a_vector_bool(int n, int digitos) {
     vector<bool> ret;
     while(n) {
          if (n&1)
               ret.push_back(true);
          else
               ret.push_back(false);

          n>>=1;
     }

     while(ret.size()<digitos)
          ret.push_back(false);

     reverse(ret.begin(),ret.end());
     return ret;
}

/**
 * @brief Calcula la entropia de una respuesta determinada
 * @param num Numero de respuestas favorables
 * @param total Nuumero total de respuestas posibles
 * @return La entropiia de la respuesta deseada
 */
inline float calcularEntropia(int num, int total) {

     //Calculamos la probabilidad de la respuesta
     float prob = static_cast<float>(num) / static_cast<float>(total);

     //Calculamos la entropía de la respuesta
     if(prob > 0) prob *= log(prob) / log(2);
     else prob = 0;

     return prob;
}

int QuienEsQuien::mejor_atributo(vector<string> atributos,
                    vector<bool> personajes_restantes,
                    vector<vector<bool>> tablero,
                    int restantes,
                    vector<bool> & siCumplen,
                    vector<bool> & noCumplen,
                    int & numSiCumplen,
                    int & numNoCumplen) {

     //Posición del que consideramos el "mejor" atributo
     int mejor_atributo = 0;
     //Entropía del "mejor" atributo
     float mejor_entropia = 0;

     //Recorremos el vector de atributos para determinar cuál tiene mejor entropía
     for(int pos_at = 0; pos_at < atributos.size(); pos_at++) {

          //Hacemos dos copias de personajes_restantes. En una vamos a eliminar los personajes que no cumplen la
          //condición del atributo y en la otra vamos a eliminar los que sí la cumplen
          vector<bool> auxSiCumplen = personajes_restantes;
          vector<bool> auxNoCumplen = personajes_restantes;

          //Variables para contar cuántos personajes de los restantes cumplen o no cumplen la condición del atributo
          int auxNumSiCumplen = 0;
          int auxNumNoCumplen = 0;

          //Variable auxiliar para iterar sobre los personajes
          int pos_per = 0;

          //Recorremos el vector de personajes_restantes para determinar cual cumple la condición del atributo
          while(pos_per < personajes_restantes.size() && restantes - auxNumSiCumplen - auxNumNoCumplen > 0) {

               //Si el personaje no ha sido aún eliminado
               if(personajes_restantes[pos_per]) {

                    //Si cumple la condición del atributo
                    if(tablero[pos_at][pos_per]) {
                         //Incrementamos el contador de personajes que sí lo cumplen
                         auxNumSiCumplen++;
                         //Eliminamos al personaje del vector de personajes que no lo cumplen
                         auxNoCumplen[pos_per] = false;
                    }
                    //Si no cumple la condición del atributo
                    else {
                         //Incrementamos el contador de personajes que no lo cumplen
                         auxNumNoCumplen++;
                         //Eliminamos al personaje del vector de personajes sí que lo cumplen
                         auxSiCumplen[pos_per] = false;
                    }
               }
               pos_per++;
          }

          //Calculamos la entropía de ambas respuestas (Si/No)
          float entropiaSI = calcularEntropia(auxNumSiCumplen, restantes);
          float entropiaNO = calcularEntropia(auxNumNoCumplen, restantes);
          //Calculamos la entropía de la pregunta
          float entropia = - entropiaSI - entropiaNO;

          //Si la entropía de la pregunta es mayor que la del supuesto "mejor" atributo, actualizamos dicho "mejor"
          //atributo, así como el valor de la "mejor" entropía, los vectores de personajes que si/no cumplen la
          //condición del atributo y el número de personajes que si/no lo cumplen
          if(entropia > mejor_entropia) {
               mejor_atributo = pos_at;
               mejor_entropia = entropia;
               siCumplen = auxSiCumplen;
               noCumplen = auxNoCumplen;
               numSiCumplen = auxNumSiCumplen;
               numNoCumplen = auxNumNoCumplen;
          }
     }
     return mejor_atributo;
}

bintree<Pregunta> QuienEsQuien::crear_arbol( vector<string> atributos,
                                             vector<string> personajes,
                                             vector<bool> personajes_restantes,
                                             vector<vector<bool>> tablero) {
     int restantes = 0;
     for(bool personaje : personajes_restantes) {
          if(personaje) restantes++;
     }

     vector<bool> siCumplen, noCumplen;
     int numSiCumplen, numNoCumplen;

     int atributo = mejor_atributo(atributos, personajes_restantes, tablero, restantes, siCumplen,
          noCumplen, numSiCumplen, numNoCumplen);

     Pregunta raiz(atributos[atributo], restantes);
     bintree<Pregunta> arbol(raiz);

     vector<string> newAtributos = atributos;
     newAtributos.erase(next(atributos.begin(), atributo));

     if(numSiCumplen == 0) {
          bintree<Pregunta> nodo_nulo;
          arbol.insert_left(raiz,nodo_nulo);
     }
     else if(numSiCumplen == 1){

          int indice_persona = -1;

          for (int i = 0; i < siCumplen.size(); ++i) {
               if (siCumplen[i]) {
                    indice_persona = i;
                    break;
               }
          }
          Pregunta persona(personajes[indice_persona], 1);
          arbol.insert_left(raiz,persona);
     }
     else {
          bintree<Pregunta> arbolIzq = crear_arbol(newAtributos,personajes,siCumplen,tablero);
          arbol.insert_left(raiz,arbolIzq);
     }

     if(numNoCumplen == 0) {
          bintree<Pregunta> nodo_nulo;
          arbol.insert_right(raiz, nodo_nulo);
     }
     else if(numNoCumplen == 1) {

          int indice_persona = -1;

          for (int i = 0; i < noCumplen.size(); ++i) {
               if (noCumplen[i]) {
                    indice_persona = i;
                    break;
               }
          }

          Pregunta persona(personajes[indice_persona], 1);
          arbol.insert_right(raiz,persona);
     }
     else {
          bintree<Pregunta> arbolDer = crear_arbol(newAtributos,personajes,noCumplen,tablero);
          arbol.insert_right(raiz,arbolDer);
     }

     return arbol;
}

bintree<Pregunta> QuienEsQuien::crear_arbol(){

     vector<bool> personajes_restantes;

     for(string personaje : personajes){
          personajes_restantes.push_back(true);
     }

     return crear_arbol(this->atributos,this->personajes, personajes_restantes, this->tablero);
}

void QuienEsQuien::usar_arbol(bintree<Pregunta> arbol_nuevo){
     arbol = arbol_nuevo;
}

void QuienEsQuien::iniciar_juego(){

     Ventana v(tg,con,"WisW");
     if (modo_graph){
        v.show();
     }
     //Variable para controlar la finalización del juego
     bool jugar = true;
     //Variable para almacenar las respuestas del jugador
     string respuesta;
     //Conjunto de respuestas permitidas
     set<string> respuestasPosibles = {"si","Si","SI","no","No","NO"};

     //Comienzo del juego hasta que el usuario quiera terminar
     while(jugar) {

          //Primera pregunta
          jugada_actual = arbol.root();

          //Seguimos haciendo preguntas hasta llegar a un personajes
          while((*jugada_actual).es_pregunta()) {

               //Preguntamos al usuario sobre su personaje, esperando una respuesta de respuestasPosibles
               do {
                    cout << "¿" << (*jugada_actual).obtener_pregunta() << "?";
                    cin  >> respuesta;
               } while(respuestasPosibles.count(respuesta) != 1);

               //Transformamos la respuesta a minúsculas
               transform(respuesta.begin(),respuesta.end(),respuesta.begin(),::tolower);

               //Si la respuesta es sí, pasamos al hijo izquierda. Pasamos al hijo derecha en caso contrario
               if(respuesta == "si")
                    jugada_actual = jugada_actual.left();
               else
                    jugada_actual = jugada_actual.right();
          }

          //Cuando llegamos a un personaje, informamos al usuario
          cout << "¡Ya lo se?! Tu personaje es " << (*jugada_actual).obtener_personaje();

          //Preguntamos al usuario si quiere continuar jugando
          do {
               cout << "¿Quieres jugar de nuevo? ";
               cin  >> respuesta;
          }while(respuestasPosibles.count(respuesta) != 1);

          //Transformamos la respuesta a minúsculas
          transform(respuesta.begin(),respuesta.end(),respuesta.begin(),::tolower);

          //Si la respuesta es "no", salimos del juego. En caso contrario, volvemos a empezar
          if(respuesta == "no") jugar = false;
     }

    if (modo_graph){
     con->WriteText("Cuando completes QuienEsQuien, este mensaje lo podr?s quitar");
     char c;
     do{
        con->WriteText("Pulsa 0 para salir");
	c = con->ReadChar();
     
     }while (c!='0');
     
    }
    v.cerrar();
}	

set<string> QuienEsQuien::informacion_jugada(bintree<Pregunta>::node jugada_actual){

     //Conjunto de personajes aún no eliminados
     set<string> personajes_levantados;

     //Si nos encontramos sobre un personaje, devolvemos el conjunto con únicamente dicho personaje
     if((*jugada_actual).es_personaje()) {
          personajes_levantados.insert((*jugada_actual).obtener_personaje());
          return personajes_levantados;
     }

     //Si nos encontramos al inicio del juego, devolvemos el conjunto con todos los personajes
     if(jugada_actual == arbol.root()) {
          for(const string &personaje : personajes) personajes_levantados.insert(personaje);
          return personajes_levantados;
     }

     //Calculamos los personajes restantes de la jugada anterior (padre de este nodo)
     personajes_levantados = informacion_jugada(jugada_actual.parent());
     //Obtenemos el atributo del padre
     string atributo_padre = (*jugada_actual.parent()).obtener_pregunta();

     //Calculamos la posición del atributo del padre en el vector de atributos
     int posicion_atributo_padre = 0;
     int i = 0;

     while(i < atributos.size()) {
          if(atributo_padre == atributos[i]) {
               posicion_atributo_padre = i;
               break;
          }
          i++;
     }

     //Si nos encontramos a la izquierda del padre, nos quedamos con los personajes que sí cumplen la condición
     if(jugada_actual.parent().left() == jugada_actual) {

          //Recorremos el vector de personajes sin eliminar
          for(const string &personaje : personajes_levantados) {

               //Para cada personaje, buscamos su posición en el vector de todos los personajes
               int posicion_personaje = 0;

               for(i = 0; i < personajes.size(); i++) {
                    if(personaje == personajes[i]) posicion_personaje = i;
               }

               //Si el personaje no cumple la condición del padre, se elimina del vector
               if(!tablero[posicion_personaje][posicion_atributo_padre])
                    personajes_levantados.erase(personaje);
          }
     }
     //Si nos encontramos a la derecha del padre, nos quedamos con los personajes que no cumplen la condición
     else {
          //Recorremos el vector de personajes sin eliminar
          for(const string &personaje : personajes_levantados) {

               //Para cada personaje, buscamos su posición en el vector de todos los personajes
               int posicion_personaje = 0;

               for(i = 0; i < personajes.size(); i++) {
                    if(personaje == personajes[i]) posicion_personaje = i;
               }

               //Si el personaje sí cumple la condición del padre, se elimina del vector
               if(tablero[posicion_personaje][posicion_atributo_padre])
                    personajes_levantados.erase(personaje);
          }
     }
     return personajes_levantados;
}

void escribir_esquema_arbol(ostream& ss, const bintree <Pregunta>& a,
                            bintree<Pregunta>::node n, string& pre){
     if (n.null())
          ss <<  pre <<  "-- x" <<  endl;
     else {
          ss <<  pre <<  "-- " <<  (*n) <<  endl;
          if ( !n.right().null() || !n.left().null()) {// Si no es una hoja
               pre += "   |";
               escribir_esquema_arbol(ss,a, n.right(), pre);
               pre.replace(pre.size()-4, 4, "    ");
               escribir_esquema_arbol (ss,a, n.left(), pre);
               pre.erase(pre.size()-4, 4);
          }
     }
}

void QuienEsQuien::escribir_arbol_completo() const{
     string pre = "";
     escribir_esquema_arbol(cout,this->arbol,this->arbol.root(),pre);
}

void QuienEsQuien::eliminar_nodos_redundantes(){

     //Recorremos todos los nodos del árbol
     for(bintree<Pregunta>::preorder_iterator it = arbol.begin_preorder(); it != arbol.end_preorder(); ++it) {

          //Nodo actual en el que nos encontramos
          bintree<Pregunta>::node nodo = *it;

          //Si el nodo no tiene hijo izquierda y sí tiene hijo derecho
          if(nodo.left().null() && !nodo.right().null()) {

               //Podamos el subárbol con raíz dicho hijo derecho y lo almacenamos en un árbol auxiliar
               bintree<Pregunta> subarbol;
               arbol.prune_right(*it, subarbol);

               //Eliminamos este nodo, sustituyéndolo por dicho subárbol auxiliar
               if(nodo == nodo.parent().left())
                    arbol.insert_left(nodo.parent(),subarbol);
               else
                    arbol.insert_right(nodo.parent(),subarbol);
          }
          //Si el nodo tiene hijo izquierda y no tiene hijo derecho
          else if(!nodo.left().null() && nodo.right().null()) {

               //Podamos el subárbol con raíz dicho hijo izquierdo y lo almacenamos en un árbol auxiliar
               bintree<Pregunta> subarbol;
               arbol.prune_left(*it, subarbol);

               //Eliminamos este nodo, sustituyéndolo por dicho subárbol auxiliar
               if(nodo == nodo.parent().left())
                    arbol.insert_left(nodo.parent(),subarbol);
               else
                    arbol.insert_right(nodo.parent(),subarbol);
          }
     }
}

float QuienEsQuien::profundidad_promedio_hojas(){

     float profundidad_promedio = 0;

     //Recorremos el árbol
     for(bintree<Pregunta>::preorder_iterator it = arbol.begin_preorder(); it != arbol.end_preorder(); ++it) {

          //Si nos encontramos en un personaje, calculamos su profundidad
          if((*it).es_personaje()) {

               //Establecemos su profundidad a uno
               float profundidad = 1;
               bintree<Pregunta>::node padre = *it;

               //Hasta no llegar a la raíz del arbol, sumamos uno por cada nodo por el que pasamos
               while(padre.parent() != arbol.root()) {
                    profundidad++;
                    padre = padre.parent();
               }
               //Sumamos la profundidad del personaje al total
               profundidad_promedio += profundidad;
          }
     }
     //Devolvemos la media de profundidades
     return profundidad_promedio / static_cast<float>(personajes.size());
}

void QuienEsQuien::preguntas_formuladas(bintree<Pregunta>::node jugada) {

     cout << endl;
     cout << "El personaje oculto tiene las siguientes caracteristicas:";
     cout << endl << endl;

     //Hasta llegar a la raíz del árbol, vamos mostrando las preguntas realizadas y sus respuestas
     while(jugada.parent() != arbol.root()) {

          cout << "\t" << (*jugada).obtener_personaje() << " - ";
          if(jugada == jugada.parent().left()) cout << "si" << endl << endl;
          else cout << "no" << endl << endl;
     }

     if((*jugada).es_pregunta()) cout << "pero aun no se cual es";
}

void QuienEsQuien::aniade_personaje(string nombre, vector<bool> caracteristicas, string nombre_imagen_personaje) {

     //Comenzamos en la raíz del árbol
     bintree<Pregunta>::node nodo = arbol.root();
     int i = 0;

     //Hasta llegar a un personaje, vamos bajando según las características del personaje que queremos añadir
     while(!(*nodo).es_personaje()) {

          if(caracteristicas[i]) nodo = nodo.left();
          else nodo = nodo.right();
          i++;
     }

     //Cuando llegamos a un personaje, obtenemos su nombre
     string personaje = (*nodo).obtener_personaje();
     int posicion_personaje = -1;

     //Buscamos la posición del personaje en el vector de personajes
     for(int a = 0; a < personajes.size(); a++) {
          if(personaje == personajes[a]) posicion_personaje = a;
     }

     //Buscamos en el tablero el atributo en el que se diferencia el personaje del que queremos añadir
     while((tablero[posicion_personaje][i]) != caracteristicas[i]) i++;
     int pos_atributo_diferente = i;

     //Creamos una nueva subárbol con raíz dicho atributo en el que se diferencian
     Pregunta nueva_pregunta(atributos[pos_atributo_diferente], 2);
     bintree<Pregunta> nuevo_subarbol(nueva_pregunta);

     //Creamos los dos nuevos nodos de personaje
     Pregunta personaje_antiguo(personaje,1);
     Pregunta personaje_nuevo(nombre,1);

     //Añadimos ambos personajes al subárbol dependiendo de cual cumple la condición y cual no
     if(tablero[posicion_personaje][pos_atributo_diferente]) {
          nuevo_subarbol.insert_left(nuevo_subarbol.root(),personaje_antiguo);
          nuevo_subarbol.insert_right(nuevo_subarbol.root(),personaje_nuevo);
     }
     else {
          nuevo_subarbol.insert_left(nuevo_subarbol.root(),personaje_nuevo);
          nuevo_subarbol.insert_right(nuevo_subarbol.root(),personaje_antiguo);
     }

     //Añadimos el subárbol al árbol principal, eliminando el antiguo nodo del personajes
     if(nodo == nodo.parent().left())
          arbol.insert_left(nodo.parent(),nuevo_subarbol);
     else
          arbol.insert_right(nodo.parent(),nuevo_subarbol);

     //Añadimos el personaje al vector de personajes
     personajes.insert(personajes.end(),nombre);

     //Añadimos el nombre de la imagen del personaje al vector de nombre de imágenes de personajes
     personajes_images.insert(personajes_images.end(),nombre_imagen_personaje);

     //Añadimos los atributos del personaje al tablero
     for(int i = 0; i < atributos.size(); i++) {
          tablero[i].insert(tablero[i].end(),caracteristicas[i]);
     }
}

void QuienEsQuien::elimina_personaje(string nombre){

     //Buscamos la posción del personaje en el vector de personajes
     int pos_personaje = -1;
     for (int i = 0; i < personajes.size(); ++i) if(personajes[i] == nombre) pos_personaje = i;

     //Nos aseguramos de que el personaje ha sido encontrado
     if(pos_personaje != -1) {

          //Eliminamos el personaje del vector de personajes y del vector de imágenes de personajes
          auto it_personajes = personajes.begin() + pos_personaje;
          personajes.erase(it_personajes,it_personajes);
          personajes_images.erase(it_personajes,it_personajes);

          //Iteramos sobre las columnas del tablero, cada una representado un atrbituo, eliminando el valor del
          //atributo del personaje que se desea eliminar
          for (int j = 0; j < atributos.size(); ++j) {
               auto it_valores_atributos = tablero[j].begin();
               tablero[j].erase(next(it_valores_atributos,pos_personaje));
          }

          //Iterador para recorrer el árbol en preorden hasta encontrar al personaje deseado
          bintree<Pregunta>::preorder_iterator it = arbol.begin_preorder();
          bool encontrado = false;

          while(!encontrado){

               encontrado = (*it).es_personaje() && (*it).obtener_personaje() == nombre;
               ++it;
          }

          //Una vez encontrado el personaje, lo eliminamos
          bintree<Pregunta>::node nodo = *it;
          nodo.remove();

          //Reestructuramos el aŕbol para que no quede una pregunta con un único personaje como respuestas y otro nulo
          eliminar_nodos_redundantes();
     }
}

/**
* @brief Genera numero enteros positivos aleatorios en el rango [min,max].
**/
int generaEntero(int min, int max){
     int tam= max-min;
     return ((rand( )%tam)+min) ;
}

void QuienEsQuien::tablero_aleatorio(int numero_de_personajes){
     srand(0);
     this->limpiar();
     float log_2_numero_de_personajes = log(numero_de_personajes)/log(2);
     int numero_de_atributos = ceil(log_2_numero_de_personajes);

     cout <<  "Peticion para generar " <<  numero_de_personajes << " personajes ";
     cout <<  "con " << numero_de_atributos <<  " atributos" << endl;
     cout <<  "Paso 1: generar " <<  pow(2, numero_de_atributos) <<  " personajes" << endl;

     //Fase 1: completar el tablero con todos los personajes posibles
     //Complete el tablero y los nombres de personajes a la vez
     for(int indice_personaje=0;indice_personaje< pow(2,numero_de_atributos);indice_personaje++){
          vector<bool> atributos_personaje =
                                    convertir_a_vector_bool(indice_personaje,numero_de_atributos);
          string nombre_personaje = "Personaje_"+to_string(indice_personaje);

          this->personajes.push_back(nombre_personaje);
          this->tablero.push_back(atributos_personaje);
     }

     // Completo los nombres de los atributos.
     for( int indice_atributo=0;indice_atributo<numero_de_atributos;indice_atributo++){
          string nombre_atributo = "Atributo_"+to_string(indice_atributo);
          this->atributos.push_back(nombre_atributo);
     }
     cout <<  "Paso 2: eliminar " << (pow(2,numero_de_atributos)-numero_de_personajes) <<  "personajes" << endl;

     //Fase 2. Borrar personajes aleatoriamente hasta que quedan solo los que hemos pedido.
     while(personajes.size()>numero_de_personajes){
          int personaje_a_eliminar = generaEntero(0,personajes.size());
          personajes.erase(personajes.begin()+personaje_a_eliminar);
          tablero.erase(tablero.begin()+personaje_a_eliminar);
     }
}

void QuienEsQuien::ocultar_personajes_graph(const set<string> &personajes_activos){
    //ocultamos los personajes
    int idx=0;
    int ncols=tg->getNcols();
    for (auto it=personajes.begin();it!=personajes.end();++it,idx++){
        if ( personajes_activos.find(*it)==personajes_activos.end())
            tg->putImagen(idx/ncols,idx%ncols,imagen_ocultar.c_str());
    }
}

void QuienEsQuien::setImagenOcultar(const char * n){
    imagen_ocultar=n;
}

void QuienEsQuien::setModoGraph(bool m){
    modo_graph=m;
}
