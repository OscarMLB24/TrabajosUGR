/**
 * @file image.cpp
 * @brief Fichero con definiciones para los métodos primitivos de la clase Image
 *
 */

#include <cstring>
#include <cassert>
#include <iostream>

#include <image.h>
#include <imageIO.h>

using namespace std;

/********************************
      FUNCIONES PRIVADAS
********************************/
void Image::Allocate(int nrows, int ncols, pixel * buffer){
    rows = nrows;
    cols = ncols;

    img = new pixel * [rows];

    if (buffer != 0)
        img[0] = buffer;
    else
        img[0] = new pixel [rows * cols];

    for (int i=1; i < rows; i++)
        img[i] = img[i-1] + cols;
}

// Función auxiliar para inicializar imágenes con valores por defecto o a partir de un buffer de datos
void Image::Initialize (int nrows, int ncols, pixel * buffer){
    if ((nrows == 0) || (ncols == 0)){
        rows = cols = 0;
        img = 0;
    }
    else Allocate(nrows, ncols, buffer);
}

// Función auxiliar para copiar objetos Imagen

void Image::Copy(const Image & orig){
    Initialize(orig.rows,orig.cols);
    for (int k=0; k<rows*cols;k++)
        set_pixel(k,orig.get_pixel(k));
}

// Función auxiliar para destruir objetos Imagen

bool Image::Empty() const{
    return (rows == 0) || (cols == 0);
}

void Image::Destroy(){
    if (!Empty()){
        delete [] img[0];
        delete [] img;
    }
}


LoadResult Image::LoadFromPGM(const char * file_path){
    if (ReadImageKind(file_path) != IMG_PGM)
        return LoadResult::NOT_PGM;

    pixel * buffer = ReadPGMImage(file_path, rows, cols);
    if (!buffer)
        return LoadResult::READING_ERROR;

    Initialize(rows, cols, buffer);
    return LoadResult::SUCCESS;
}

/********************************
       FUNCIONES PÚBLICAS
********************************/

// Constructor por defecto

Image::Image(){
    Initialize();
}

// Constructores con parámetros
Image::Image (int nrows, int ncols, pixel value){
    Initialize(nrows, ncols);
    for (int k=0; k<rows*cols; k++) set_pixel(k,value);
}

bool Image::Load (const char * file_path) {
    Destroy();
    return LoadFromPGM(file_path) == LoadResult::SUCCESS;
}

Image::Image (const char * file_path){
    LoadResult r = LoadFromPGM(file_path);
    switch (r) {
        case NOT_PGM:
            cerr << "Error: " << file_path << " no es un fichero PGM válido" << endl;
            exit (1);
        case READING_ERROR:
            cerr << "Error: no se pudo leer el fichero " << file_path << endl;
            exit (1);
        default:
            break;
    }
}

// Constructor de copias

Image::Image (const Image & orig){
    assert (this != &orig);
    Copy(orig);
}

// Destructor

Image::~Image(){
    Destroy();
}

// Operador de Asignación

Image & Image::operator= (const Image & orig){
    if (this != &orig){
        Destroy();
        Copy(orig);
    }
    return *this;
}

// Métodos de acceso a los campos de la clase

int Image::get_rows() const {
    return rows;
}

int Image::get_cols() const {
    return cols;
}

// Métodos básicos de edición de imágenes
void Image::set_pixel (int i, int j, pixel value) {
    img[i][j] = value;
}
pixel Image::get_pixel (int i, int j) const {
    return img[i][j];
}

// This doesn't work if representation changes
void Image::set_pixel (int k, pixel value) {
    int r,c;
    r = k/cols;
    c = k%cols;
    img[r][c] = value;
}

// This doesn't work if representation changes
pixel Image::get_pixel (int k) const {
    int r,c;
    r = k/cols;
    c = k%cols;
    return img[r][c];
}


// Métodos para almacenar y cargar imagenes en disco
bool Image::Save (const char * file_path) const {
    // Write data to buffer
    pixel data[rows*cols];
    for (int k=0; k<rows*cols; k++) data[k]= get_pixel(k);
    // Save data
    return WritePGMImage(file_path, data, rows, cols);;
}

