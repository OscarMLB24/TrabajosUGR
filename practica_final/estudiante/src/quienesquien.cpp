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
     while( is.good()) {
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

int QuienEsQuien::mejor_atributo(vector<string> atributos,
                    vector<bool> personajes_restantes,
                    vector<vector<bool>> tablero,
                    int restantes,
                    vector<bool> & siCumplen,
                    vector<bool> & noCumplen,
                    int & numSiCumplen,
                    int & numNoCumplen) {

     vector<float> entropias(atributos.size());
     vector<vector<bool>> vectorSiCumplen;
     vector<vector<bool>> vectorNoCumplen;
     vector<int> vectorNumSiCumplen;
     vector<int> vectorNumNoCumplen;

     for(int i = 0; i < atributos.size(); ++i) {
          vectorSiCumplen.push_back(personajes_restantes);
          vectorNoCumplen.push_back(personajes_restantes);
          vectorNumSiCumplen.push_back(0);
          vectorNumNoCumplen.push_back(0);
     }

     for(int pos_at = 0; pos_at < atributos.size(); pos_at++) {

          int pos_per = 0;
          while(restantes - vectorNumSiCumplen[pos_at] - vectorNumNoCumplen[pos_at] > 0) {

               if(personajes_restantes[pos_per]) {

                    if(tablero[pos_at][pos_per]) {
                         vectorNumSiCumplen[pos_at]++;
                         vectorNoCumplen[pos_at][pos_per] = false;
                    }
                    else {
                         vectorNumNoCumplen[pos_at]++;
                         vectorSiCumplen[pos_at][pos_per] = false;
                    }
                    pos_per++;
               }
          }

          float prob_no = static_cast<float>(vectorNumNoCumplen[pos_at]) / static_cast<float>(restantes);
          float prob_si = static_cast<float>(vectorNumSiCumplen[pos_at]) / static_cast<float>(restantes);
          entropias[pos_at] =
                         static_cast<float>((prob_no * log(prob_no)/log(2) - prob_si * log(prob_si)/log(2)) * (-1));
     }

     int mejor_atributo = 0;

     for(int i = 0; i < entropias.size(); ++i) {
          if(entropias[i] > entropias[0]) mejor_atributo = i;
     }

     siCumplen = vectorSiCumplen[mejor_atributo];
     noCumplen = vectorNoCumplen[mejor_atributo];
     numSiCumplen = vectorNumSiCumplen[mejor_atributo];
     numNoCumplen = vectorNumNoCumplen[mejor_atributo];

     return mejor_atributo;
}

bintree<Pregunta> QuienEsQuien::crear_arbol( vector<string> atributos,
                                             int indice_atributo,
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

     if(numSiCumplen == 1){

          int indice_persona = -1;
          int i = 0;

          do {
               if(siCumplen[i]) indice_persona = i;
               else i++;
          } while(indice_persona == -1);

          Pregunta persona(personajes[indice_persona], 1);
          return persona;
     }

     if(numNoCumplen == 1) {

          int indice_persona = -1;
          int i = 0;

          do {
               if(noCumplen[i]) indice_persona = i;
               else i++;
          } while(indice_persona == -1);

          Pregunta persona(personajes[indice_persona], 1);
          return persona;
     }

     Pregunta raiz(atributos[atributo], restantes);
     bintree<Pregunta> arbol(raiz);

     vector<string> newAtributos = atributos;
     newAtributos.erase(next(atributos.begin(), atributo));

     bintree<Pregunta> arbolIzq = crear_arbol(newAtributos,indice_atributo,personajes,siCumplen,tablero);
     bintree<Pregunta> arbolDer = crear_arbol(newAtributos,indice_atributo,personajes,noCumplen,tablero);
     arbol.insert_left(raiz,arbolIzq);
     arbol.insert_left(raiz,arbolDer);

     return arbol;
}

bintree<Pregunta> QuienEsQuien::crear_arbol(){
     int indice_atributo = 0;
     vector<bool> personajes_restantes;
     for(vector<string>::iterator it = personajes.begin();it!=personajes.end();it++){
          personajes_restantes.push_back(true);
     }

     return crear_arbol( this->atributos, indice_atributo, this->personajes,
                         personajes_restantes, this->tablero);
}

void QuienEsQuien::usar_arbol(bintree<Pregunta> arbol_nuevo){
     arbol = arbol_nuevo;
}

void QuienEsQuien::iniciar_juego(){

    Ventana v(tg,con,"WisW");
    if (modo_graph){
        v.show();
    }

     bool jugar = true;
     string respuesta;
     set<string> respuestaPosibles = {"si","Si","SI","no","No","NO"};

     while(jugar) {

          jugada_actual = arbol.root();

          while((*jugada_actual).es_pregunta()) {

               do {
                    cout << "¿" << (*jugada_actual).obtener_pregunta() << "?";
                    cin  >> respuesta;
               } while(respuestaPosibles.count(respuesta) != 1);

               transform(respuesta.begin(),respuesta.end(),respuesta.begin(),::tolower);

               if(respuesta == "si")
                    jugada_actual = jugada_actual.left();
               else
                    jugada_actual = jugada_actual.right();
          }

          cout << "¡Ya lo se?! Tu personaje es " << (*jugada_actual).obtener_personaje();

          do {
               cout << "¿Quieres jugar de nuevo? ";
               cin  >> respuesta;
          }while(respuestaPosibles.count(respuesta) != 1);

          transform(respuesta.begin(),respuesta.end(),respuesta.begin(),::tolower);

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

     set<string> personajes_levantados;

     if((*jugada_actual).es_personaje()) {
          personajes_levantados.insert((*jugada_actual).obtener_personaje());
          return personajes_levantados;
     }

     if(jugada_actual == arbol.root()) {
          for(const string &personaje : personajes) personajes_levantados.insert(personaje);
          return personajes_levantados;
     }

     personajes_levantados = informacion_jugada(jugada_actual.parent());
     string atributo_padre = (*jugada_actual.parent()).obtener_pregunta();
     int posicion_atributo_padre = 0;
     int i = 0;

     while(i < atributos.size()) {
          if(atributo_padre == atributos[i]) {
               posicion_atributo_padre = i;
               break;
          }
          i++;
     }

     if(jugada_actual.parent().left() == jugada_actual) {

          for(const string &personaje : personajes_levantados) {

               int posicion_personaje = 0;

               for(i = 0; i < personajes.size(); i++) {
                    if(personaje == personajes[i]) posicion_personaje = i;
               }
               if(!tablero[posicion_personaje][posicion_atributo_padre])
                    personajes_levantados.erase(personaje);
          }
     }
     else {
          for(const string &personaje : personajes_levantados) {

               int posicion_personaje = 0;

               for(i = 0; i < personajes.size(); i++) {
                    if(personaje == personajes[i]) posicion_personaje = i;
               }
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

     for(bintree<Pregunta>::preorder_iterator it = arbol.begin_preorder(); it != arbol.end_preorder(); ++it) {

          bintree<Pregunta>::node nodo = *it;

          if(nodo.left().null() && !nodo.right().null()) {

               bintree<Pregunta> subarbol;
               arbol.prune_right(*it, subarbol);

               if(nodo == nodo.parent().left())
                    arbol.insert_left(nodo.parent(),subarbol);
               else
                    arbol.insert_right(nodo.parent(),subarbol);
          }
          else if(!nodo.left().null() && nodo.right().null()) {

               bintree<Pregunta> subarbol;
               arbol.prune_left(*it, subarbol);

               if(nodo == nodo.parent().left())
                    arbol.insert_left(nodo.parent(),subarbol);
               else
                    arbol.insert_right(nodo.parent(),subarbol);
          }
     }
}

float QuienEsQuien::profundidad_promedio_hojas(){

     float profundidad_promedio = 0;

     for(bintree<Pregunta>::preorder_iterator it = arbol.begin_preorder(); it != arbol.end_preorder(); ++it) {

          if((*it).es_personaje()) {

               float profundidad = 1;
               bintree<Pregunta>::node padre = *it;

               while(padre.parent() != arbol.root()) {
                    profundidad++;
                    padre = padre.parent();
               }
               profundidad_promedio += profundidad;
          }
     }

     return profundidad_promedio / static_cast<float>(personajes.size());
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

void QuienEsQuien::preguntas_formuladas(bintree<Pregunta>::node jugada) {

     cout << endl;
     cout << "El personaje oculto tiene las siguientes caracteri?sticas:";
     cout << endl << endl;

     while(jugada.parent() != arbol.root()) {

          cout << "\t" << (*jugada).obtener_personaje() << " - ";

          if(jugada == jugada.parent().left()) cout << "si" << endl << endl;
          else cout << "no" << endl << endl;
     }

     if((*jugada).es_pregunta()) cout << "pero au?n no se cua?l es";
}

void QuienEsQuien::aniade_personaje(string nombre, vector<bool> caracteristicas, string nombre_imagen_personaje) {

     bintree<Pregunta>::node nodo = arbol.root();
     int i = 0;

     while(!(*nodo).es_personaje()) {

          if(caracteristicas[i]) nodo = nodo.left();
          else nodo = nodo.right();
          i++;
     }

     string personaje = (*nodo).obtener_personaje();
     int posicion_personaje = -1;

     for(int a = 0; a < personajes.size(); a++) {
          if(personaje == personajes[a]) posicion_personaje = a;
     }

     while((tablero[posicion_personaje][i]) != caracteristicas[i]) i++;
     int pos_atributo_diferente = i;

     Pregunta nueva_pregunta(atributos[pos_atributo_diferente], 2);
     bintree<Pregunta> nuevo_subarbol(nueva_pregunta);

     Pregunta personaje_antiguo(personaje,1);
     Pregunta personaje_nuevo(nombre,1);

     if(tablero[posicion_personaje][pos_atributo_diferente]) {
          nuevo_subarbol.insert_left(nuevo_subarbol.root(),personaje_antiguo);
          nuevo_subarbol.insert_right(nuevo_subarbol.root(),personaje_nuevo);
     }
     else {
          nuevo_subarbol.insert_left(nuevo_subarbol.root(),personaje_nuevo);
          nuevo_subarbol.insert_right(nuevo_subarbol.root(),personaje_antiguo);
     }

     //Añadimos el personaje al vector de personajes
     personajes.insert(personajes.end(),nombre);

     //Añadimos el nombre de la imagen del personaje al vector de nombre de ima?genes de personajes
     personajes_images.insert(personajes_images.end(),nombre_imagen_personaje);

     //Añadimos los atributos del personaje al tablero
     for(int i = 0; i < atributos.size(); i++) {
          tablero[i].insert(tablero[i].end(),caracteristicas[i]);
     }
}

void QuienEsQuien::elimina_personaje(string nombre){

     int pos_personaje = -1;
     for (int i = 0; i < personajes.size(); ++i) if(personajes[i] == nombre) pos_personaje=i;

     if(pos_personaje != -1) {

          auto it_personajes = personajes.begin() + pos_personaje;
          personajes.erase(it_personajes,it_personajes);
          personajes_images.erase(it_personajes,it_personajes);

          for (int j = 0; j < atributos.size(); ++j) {

               auto it_atributos = tablero[j].begin();
               tablero[j].erase(it_atributos,it_atributos);
          }

          bintree<Pregunta>::preorder_iterator it = arbol.begin_preorder();


          bool encontrado = false;

          while(!encontrado){

               encontrado = (*it).es_personaje() && (*it).obtener_personaje() == nombre;
               ++it;
          }

          bintree<Pregunta>::node nodo = *it;
          nodo.remove();
          eliminar_nodos_redundantes();
     }
}
