/**
  * @file image.h
  * @brief Fichero de cabecera asociado a la biblioteca libimagen.a
  *
  * Implementación del TDA Imagen
  */

#ifndef _IMAGEN_H_
#define _IMAGEN_H_


#include <cstdlib>
#include "imageIO.h"


/*! unsigned char aliased as byte*/
typedef unsigned char pixel;

/*! Result for image loading*/
enum LoadResult: unsigned char {
    SUCCESS, /*! PGM Image loaded successfully */
    NOT_PGM, /*! Not a P5 PGM image */
    READING_ERROR /*! Other reading error */
};


/**
  @brief T.D.A. Imagen

  Una instancia del tipo de dato abstracto Imagen nos permite almacenar imágenes de intensidades.

  El TDA Imagen proporciona además distintas herramientas para la manipulación de dichas imágenes, como son ajustes de contraste, ecualización del histograma, binarización de la imagen, creación de un icono a partir de una imagen o hacer morphing de intensidades de una imagen a otra.

  Para poder usar el TDA Imagen se debe incluir el fichero

  \#include <Imagen.h>

  @author Javier Abad
  @date Mayo 2010

**/

class Image{
    /**
      @page repImagen Representación del TDA Imagen .

      @section invImagen Invariante de la representación.

      Un objeto válido 1 del TDA Imagen debe cumplir
        -I.rows >= O
        -I.cols >= O
        -I.img apunta a una zona de memoria con capacidad para albergar I.rows*I.cols valores de tipo byte o a NULL si la imagen está vacía.

      @section faImagen Función de abstracción

      Un objeto válido 1 del TDA Imagen representa una imagen en niveles de gris, de dimensiones I.fils*I.cols píxeles.

    **/

private :

    /**
      @brief Puntero a la imagen almacenada

      img apunta a un array-2D dinámico de bytes que contiene la imagen en sí. Almacena tantos bytes como pixeles tenga la imagen.

    **/
    pixel **img;

    /**
      @brief Número de filas de la imagen.
    **/

    int rows;


    /**
      @brief Número de columnas de la imagen.
    **/
    int cols;


    /**
      @brief Initialize una imagen.
      @param nrows Número de filas que tendrá la imagen. Por defecto, 0
      @param ncols Número de colwnnas que tendrá la imagen. Por defecto, 0
      @param buffer Puntero a un buffer de datos con los que rellenar los píxeles de la imagen. Por defecto, 0.
      @pre filas >= O y columnas >= O
      @post Reserva memoria para almacenar la imagen y la prepara para usarse.
    **/

    void Initialize (int nrows= 0, int ncols= 0,pixel *buffer= 0);

    /**
      @brief Lee una imagen PGM desde un archivo.
      @param file_path Ruta del archivo a leer
      @return LoadResult
    **/
    LoadResult LoadFromPGM(const char * file_path);

    /**
      @brief Copy una imagen .
      @param orig Referencia a la imagen original que vamos a copiar
    **/
    void Copy(const Image &orig);

    void Allocate(int nrows, int ncols, pixel * buffer = 0);

    /**
      * @brief Destroy una imagen
      *
      * Libera la memoria reservada en la que se almacenaba la imagen que llama a la función.
      * Si la imagen estaba vacía no hace nada .
      */
    void Destroy();

public :

    /**
      * @brief Constructor por defecto .
      * @post Genera una instancia de la clase Imagen con O filas y O colunmas.
      * @return Imagen, el objeto imagen creado.
      */
    Image();

    /**
      * @brief Constructor con parámetros.
      * @param nrows Número de filas de la imagen.
      * @param ncols Número de columnas de la imagen.
      * @param value defecto Valor con el que inicializar los píxeles de la imagen . Por defecto O.
      * @pre n fils > O Y n_cols > O
      * @post La imagen creada es de n_fils y n_cols columnas. Estará inicializada al valor por defecto.
      * @return Imagen, el objeto imagen creado.
      */
    Image(int nrows, int ncols, pixel value=0);

    /**
      * @brief Constructor de imágenes desde fichero.
      * @param file_path path Ruta de archivo desde el que leer la imagen .
      * @pre file_path debe contener una ruta de archivo .pgm válida .
      * @post La imagen creada será una copia de la que se encuentre en file_path.
      * @return Imagen, el objeto imagen creado .
      */
    Image(const char *file_path);

    /**
      * @brief Constructor de copias.
      * @param orig Referencia a la imagen original que se quiere copiar.
      * @return Imagen, el objeto imagen creado.
      */
    Image (const Image & orig);

    /**
      * @brief Oper ador de tipo destructor.
      * @return void
      * @post El objeto Imagen destruido no puede usarse salvo que se haga sobre él una operacion Imagen().
      */
    ~Image() ;

    /**
      * @brief Operador de asignación .
      * @param orig Referencia a la imagen original que desea copiarse.
      * @return Una referencia al objeto imagen modificado.
      * @post Destroy cualquier información que contuviera previamente la imagen que llama al operador de asignación.
      */
    Image & operator= (const Image & orig);

    /**
      * @brief Funcion para conocer si una imagen está vacía.
      * @return Si la imagene está vacía
      * @post la imagen no se modifica.
      */
    bool Empty() const;

    /**
      * @brief Filas de la imagen .
      * @return El número de filas de la i magen.
      * @post la imagen no se modifica.
      */
    int get_rows() const;

    /**
      * @brief Columnas de la imagen.
      * @return El número de columnas de la imagen.
      * @post la imagen no se modifica.
      */
    int get_cols() const;

    /**
      * @brief Asigna el valor valor al píxel (fil, col) de la imagen.
      * @param i Fila de la imagen en la que se encuentra el píxel a escribir .
      * @param j Columna de la imagen en la que se encuentra el píxel a escribir.
      * @param value Valor que se escribirá en el píxel (fil, col) .
      * @pre O <= fil < I . get_rows() II O <= col < I.get_cols() II O <= valor <= 255
      * @return void
      * @post El píxel (fil, col) de la imagen se modificará y contendrá valor.
      * Los demás píxeles permanecerán iguales.
      */
    void set_pixel (int i, int j, pixel value);

    /**
      * @brief Consulta el valor del píxel (fil, col) de la imagen.
      * @param i Fila de la imagen en la que se encuentra el píxel a consultar.
      * @param j Columna de la imagen en la que se encuentra el píxel a consultar.
      * @pre O <= fil < I.Num_ Filas() II O <= col < I.Num Columnas()
      * @return el valor del píxel contenido en (fil,col)
      * @post La imagen no se modifica.
      */
    pixel get_pixel (int i, int j) const;

    /**
      * @brief Consulta el valor del píxel k de la imagen desenrrollada.
      * @param k Índice del píxel
      * @pre 0 <= k < filas*columnas
      * @return el valor del píxel contenido en (k/filas,k%filas)
      * @post La imagen no se modifica.
      */
    pixel get_pixel (int k) const;

    /**
      * @brief Asigna el valor valor al píxel k de la imagen desenrollada.
      * @param k Índice del píxel a escribir .
      * @param value Valor que se escribirá en el píxel k.
      * @pre 0 <= k < filas*columnas && O <= valor <= 255
      * @post El píxel k se modificará con el valor de value.
      */
    void set_pixel (int k, pixel value);

    /**
      * @brief Almacena imágenes en disco.
      * @param file_path Ruta donde se almacenará la imagen.
      * @pre file path debe ser una ruta válida donde almacenar el fichero de salida.
      * @return Devuelve true si la imagen se almacenó con éxito y false en caso contrario.
      * @post La imagen no se modifica.
      */
    bool Save (const char * file_path) const;

    /**
      * @brief Carga en memoria una imagen de disco .
      * @param file_path path Ruta donde se encuentra el archivo desde el que cargar la imagen.
      * @pre file path debe ser una ruta válida que contenga un fichero . pgm
      * @return Devuelve true si la imagen se carga con éxito y false en caso contrario.
      * @post La imagen previamente almacenada en el objeto que llama a la función se destruye.
      */
    bool Load (const char * file_path);


    /**
      * @brief Modifica el contraste de una Imagen .
      * @param in1 Umbral inferior de la imagen de entrada
      * @param in2 Umbral superior de la imagen de entrada
      * @param out1 Umbral inferior de la imagen de salida
      * @param out2 Umbral superior de la imagen de salida
      * @pre 0 <= ( in1, in2, out1, out2 ) <= 255
      * @pre in1 < in2
      * @pre out1 < out2
      * @post El objeto que llama a la función es modificado.
      */
    void AdjustContrast (pixel in1, pixel in2, pixel out1, pixel out2);


    /**
      * @brief Calcula la media de los píxeles de una imagen entera o de un fragmento de ésta.
      *
      * Puede cal cular la media de los píxeles de toda la imagen o se le puede
      * pasar la fila y la columna de un punto de la imagen a partir del cual
      * hacer la media usándolo como esquina superior izquierda de la sub-imagen.
      * También se le pueden especificar las dimensiones en alto y ancho de la
      * sub-imagen.
      *
      * @param i Columna donde comienza la sub-imagen a la que haremos la media. Por defecto O.
      * @param j Fila donde comienza la sub-imagen a la que haremos la media. Por defecto Ott'
      * @param height Altura de la sub-imagen a la que haremos la media. Por defecto o.
      * @param width Anchura de la sub-imagen a la que haremos la media. Por defecto O.
      * @pre pos i >= O, pos j >= O, height >= O, width >= O
      * @return La media de los valores de los píxeles de la sub-imagen sobre la que se ha calculado.
      * @post La imagen no se modifica.
      */
    double Mean (int i, int j, int height, int width) const;

    /**
      * @brief Genera un icono como reducción de una imagen.
      * @param factor Factor de reducción de la imagen original con respecto al icono .
      * @pre factor > O
      * @return La imagen iconizada.
      * @post La imagen no se modifica.
      * @post La imagen resultante tendrá tamaño int(filas/factor) X int(columnas/factor). Descartando los decimales de la división
      */
    Image Subsample(int factor) const;

    /**
      * @brief Genera una subimagen.
      * @param nrow Fila inicial para recortar
      * @param ncol Columna inicial para recortar
      * @param height Número de filas
      * @param width Número de columnas
      * @return Imagen con el recorte.
      * @post El objeto que llama a la función no se modifica.
      */
    Image Crop(int nrow, int ncol, int height, int width) const;

    /**
      * @brief Genera una imagen aumentada 2x.
      * @return Imagen con el recorte.
      * @post El objeto que llama a la función no se modifica.
      */
    Image Zoom2X() const;

    /**
      * @brief Copia el contenido de la imagen pasada como parámetro a la imagen que llama en la posición indicada.
      * @param in Imagen de entrada
      * @param i fila para comenzar la copia
      * @param j columna para comenzar la copia
      * @post El objeto que llama a la función se modifica.
      */
    void PaintIn(Image & in, int i, int j);


} ;


#endif // _IMAGEN_H_

