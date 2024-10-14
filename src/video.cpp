
#include "video.h"

void read_directory(const std::string& name, vector<string>& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp; 
    while ((dp = readdir(dirp)) != NULL) {

        v.push_back(dp->d_name);
    }
    closedir(dirp);
}

/**************************************************/

Video::Video(){}

/**************************************************/
Video::Video(int n)
{
    seq.reserve(n);
}
/**************************************************/
Video::Video(const Video &V)
{
    seq = V.seq;
}
/**************************************************/

Video::~Video(){}

/**************************************************/
Video &Video::operator=(const Video &V)
{
    if (this != &V) seq = V.seq;
    return * this;
}
/**************************************************/
int Video::size() const
{
    return static_cast<int>(seq.size());
}
/**************************************************/
Image &Video::operator[](int foto)
{
    return seq.at(foto);
}
/**************************************************/
const Image &Video::operator[](int foto) const
{
    return seq.at(foto);
}
/**************************************************/
void Video::Insertar(int k, const Image &I)
{
    seq.insert(seq.begin() + k, I);
}
/**************************************************/
void Video::Borrar(int k)
{
    seq.erase(seq.begin() + k);
}
/**************************************************/
bool Video::LeerVideo(const string &path)
{
    bool exito = true;
    std::filesystem::path filepath = path;
    bool filepathExists = std::filesystem::is_directory(filepath);

    if(!filepathExists) {

        cout << "No existe el directorio " << path << endl;
        return false;
    }
    else {

        vector<string> aux;
        read_directory(path, aux);
    }
    //USA read_directory PARA LEER los fichero de un directorio
    //COMPLETAR POR EL ESTUDIANTE
}

bool Video::EscribirVideo(const string & path, const string &prefijo)const{

    bool exito=true;
    std::filesystem::path filepath =path;
    bool filepathExists = std::filesystem::is_directory(filepath);

    if (!filepathExists){

        bool created_new_directory= std::filesystem::create_directory(filepath);
        if (!created_new_directory){
            cout<<"No se puede crear el directorio "<<path<<endl;
            return false;
        }
        else{
            cout<<" Se ha creado el directorio "<< path<<endl;
        }
    }

    //COMPLETAR POR EL ESTUDIANTE


}
