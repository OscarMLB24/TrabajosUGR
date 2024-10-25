#include "image.h"
#include "video.h"
#include <iostream>
#include <cassert>
using namespace std;

/**
 * @brief cambiar una imagen en otra o para proporcionar una transición sueva de una imagen a otra creando la ilusión de
 * una transformación.
 * @param I1 imagen 1 a transformar
 * @param I2 imagen 2 a transformar
 * @param nframes número de fotogramas a obtener
 * @return devuelve el vídeo de la transformación
 */

Video Morphing(const Image &I1, const Image &I2, int nframes)
{
    Video video(nframes);
    int num_cols = I1.get_cols();
    int num_rows = I1.get_rows();

    if( num_cols == I2.get_cols() && num_rows == I2.get_rows()) {

        for(int i = 0; i < nframes; ++i) {

            Image imagen(num_rows,num_cols);
            double coef = static_cast<double>(i)/nframes;

            for(int r = 0; r < num_rows; ++r) {
                for(int c = 0; c < num_cols; ++c){

                    pixel p1 = I1.get_pixel(r,c);
                    pixel p2 = I2.get_pixel(r,c);
                    imagen.set_pixel(r,c , (1 - coef) * p1 + coef * p2);
                }
            }
            video.Insertar(i,imagen);
        }
    }
    return video;
}

int main(int argc, char * argv[])
{
    const string PREFIJO = "morphed";

    if(argc != 5) {
        cerr << "Debe introducir 4 parametros:"
             << "\n\t1) El nombre del fichero que contiene la imagen inicial de la que se parte."
             << "\n\t2) El nombre del fichero que contiene la imagen final a la que se pretende llegar."
             << "\n\t3) El directorio donde se almacena el video creado."
             << "\n\t4) El numero de frames de la transformacion.";
        return 1;
    }

    bool exito = true;

    Image imagen_inicial(argv[1]);
    Image imagen_final(argv[2]);
    int nf = stoi(argv[4]);

    Video video(Morphing(imagen_inicial,imagen_final,nf));
    exito = video.EscribirVideo(argv[3], PREFIJO);

    if(exito) {
        cout << "Se ejecuto con exito" << endl;
        return 0;
    }
    else {
        cout << "Hubo un error de ejecucion" << endl;
        return 1;
    }
}
