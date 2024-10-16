
#ifndef PRACTICA2_VIDEO_H
#define PRACTICA2_VIDEO_H
#include "image.h"
#include <vector>
#include <set>
#include <map>
#include <sys/types.h>
#include <dirent.h>
#include <cmath>
#include <string>
#include <filesystem>
#include <iostream>
#include <list>
using namespace std;

/**
 * @brief función que crea un vector de strings con los nombres de cada archivo
 * @param name nombre del directorio
 * @param v vector donde se almacenan los nombres
 */
void read_directory(const std::string& name, vector<string>& v);

class Video {
private:
    vector<Image> seq;

public:
    /**
     * @brief constructor por defecto
     */
    Video();

    /**
     * @brief constructor. Crear un vídeo en memoria con la posibilidad para albergar n imágenes. Reserva memoria
     * para alojar el vídeo
     * @param n número de imágenes que puede albergar
     * @pre n > 0
     * @post 1. El vídeo creado tiene n casillas
     *       2. El vídeo creado contiene valores "basura" (no está inicializado)
     */
    Video(int n);

    /**
     * @brief constructor de copia
     * @param V vídeo que se quiere copiar
     */
    Video(const Video &V);

    /**
     * @brief destructor. Liberar los recursos ocupados por el vídeo
     * @post 1. No devuelve nada
     *       2. El vídeo destruido no puede volver a usarse, salvo que se vuelva a realizar sobre él otra operación de
     *       construcción
     */
    ~Video();

    /**
     * @brief sobrecarga del operador =
     * @param V video a copiar
     * @return devuelve una referencia al video modificado
     */
    Video &operator=(const Video &V);

    /**
     * @brief calcular el número de fotogramas del vídeo
     * @return devuelve el tamaño del vídeo
     * @post el vídeo no se modifica
     */
    int size() const;

    /**
     * @brief sobrecarga del operador []. Consultar un fotograma del vídeo
     * @param foto posición del vídeo a obtener
     * @pre 0 <= n < size()
     * @return devuelve la imagen asociada al fotograma foto-ésimo del vídeo
     */
    Image &operator[](int foto);

    /**
     * @brief sobrecarga del operador []. Consultar un fotograma del vídeo
     * @param foto posición del vídeo a obtener
     * @return devuelve la imagen asociada al fotograma foto-ésimo del vídeo
     */
    const Image &operator[](int foto) const;

    /**
     * @brief insertar un nuevo fotograma I en la posición k
     * @param k posición en la que se inserta la imagen
     * @param I imagen a insertar
     * @pre k debe indicar una posición válida dentro del vídeo, es decir, en el rango [0,V.size()]
     * @post  el vídeo es modificado teniendo un nuevo fotograma más
    */

    void Insertar(int k, const Image &I);

    /**
     * @brief eliminar el fotograma de la posición dada por un entero k
     * @param k posición cuya imagen va a ser borrada
     * @pre k deber ser una posición válida dentro del vídeo, es decir, que pertenezca al rango [0,V.size()-1]
     * @post el vídeo es modificado teniendo un fotograma menos
     */
    void Borrar(int k);

    /**
     * @brief leer un vídeo de disco
     * @param path ruta del directorio leer el vídeo
     * @pre en el directorio path debe almacenarse una secuencia temportal de fotogramas
     * @return devuelve true si la lectura tiene éxito y false en caso contrario
     */
    bool LeerVideo(const string & path);

     /**
     * @brief escribir un vídeo de disco
     * @param path ruta del directorio donde escribir el vídeo
     * @param prefijo nombre para cada fotograma
     * @pre los fotogramas tomarán como nombre <prefijo>_01.pgm,...,<prefijo>_0n.pgm siendo n el número de fotogramas
     * @return devuelve true si la escritura tiene éxito y false en caso contrario
     */
    bool EscribirVideo(const string & path, const string &prefijo)const;
};

#endif //PRACTICA2_VIDEO_H
