/* 
Actividad integradora 1

Francisco Mestizo Hernandez
Adrian Emmanuel Faz Mercado
Pablo Navarro Zepeda
*/

#include <iostream>
#include <string> //Para manejar strings
#include <fstream> //Lectura de archivos
#include <vector> //vectores

using namespace std;

//Funcion que lee un archivo y retorna el string de la transmision
string readTransmission(string _fileName){
    ifstream file(_fileName); //Creamos el stream para el archivo
    string transmission; //Creamos la variable donde vamos a guardar el string
    
    getline(file, transmission); //Obtenemos la linea (solo lo hacemos una vez porque sabemos que los archivos solo tienen un string)
    file.close(); //Cerramos el stream del archivo
    
    return transmission; //Retornamos el string que obtuvimos
}

//Lee el archivo con el codigo malicioso y retorna un vector con los strings
void readMaliciousCode(string _fileName, vector<string> &arr){
    ifstream file(_fileName); //Abrimos el archivo
    string aux; //Creamos un string auxiliar para guardar cada linea del archivo mientras lo leemos

    //Leemos el archivo mientras no se quede vacio y guardamos las lineas en un vector
    while(getline(file, aux)){
        arr.push_back(aux);
    }
}

//Funcion que recibe un string y substring y retorna un vector con las ocurrencias que tuvo el substring en el string
vector<string> findSubstrings(string text, string substring){
    //Aqui implementamos el codigo de substring y retornamos un vector con los 
    //indices de donde se encontro
}

int main() {
    //Leemos y guardamos el string de cada archivo
    string transmission1, transmission2, transmission3;
    transmission1 = readTransmission("transmission1.txt");
    transmission2 = readTransmission("transmission2.txt");
    transmission3 = readTransmission("transmission3.txt");

    //Guardamos el codigo malicioso en un vector
    vector<string> mCode;
    readMaliciousCode("mcode.txt", mCode);

    asdjks
    return 0;
}