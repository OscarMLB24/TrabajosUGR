#include "image.h"
#include "video.h"
#include <iostream>
using namespace std;

/**
 * @brief invertir un vídeo, es decir, el fotograma v.size()-1 se pondrá en la posición 0 del vídeo rebobinado, el
 * v.size()02 en la posición 1, y así hasta llegar al fotograma 0 que se colocará en la posición v.size()-1.
 * @param V vídeo a invertir
 * @return devuelve el vídeo invertido
 */
Video Rebobinar(const Video &V)
{
    int n = V.size();
    Video invertido(n);

    for(int i = 0; i < n; i++)
        invertido.Insertar(i,V[n-i-1]);

    return invertido;
}

int main(int argc, char * argv[])
{
    if(argc != 3) {
        cerr << "Debe introducir 2 parametros:"
             << "\n\t1) El directorio donde se encuentran los fotogramas del video de entrada."
             << "\n\t2) El directorio donde se escribe el video rebobinado.";
        return 1;
    }

    bool exito = true;
    Video video;
    Video rebobinado;
    exito = video.LeerVideo(argv[1]);

    if(exito) {

        string ruta_entrada = argv[1];
        string path_sin_barra = ruta_entrada.substr(0,ruta_entrada.size()-1);
        int pos_ultima_barra = static_cast<int>(path_sin_barra.find_last_of('/'));
        string prefijo = path_sin_barra.substr(pos_ultima_barra+1);

        rebobinado = Rebobinar(video);
        exito = rebobinado.EscribirVideo(argv[2], prefijo);
    }

    if(exito) {
        cout << "Se ejecuto con exito" << endl;
        return 0;
    }
    else {
        cout << "Hubo un error de ejecucion" << endl;
        return 1;
    }
}