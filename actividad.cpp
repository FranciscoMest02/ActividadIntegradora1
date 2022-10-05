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
#include <unordered_set> //sets

using namespace std;

//Inicia lectura de archivos ---------------------------------------------------
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
//Termina lectura de archivos ---------------------------------------------------



// Inicia z-funcion -----------------------
// A partir de aqui es la zfuncion, para encontrar las ocurrencias de un substring en el string general 
vector<int> zfunction(string texto) {
    int n = texto.size();
    vector<int> z(n,0);

    for(int i = 1, l = 0, r = 0; i < n; i++){
        if(i <= r){
            z[i] = min(r - i + 1, z[i-1]);
        }
        while (i+z[i] < n && texto[z[i]] == texto[i + z[i]]){
            z[i]++;
        }
        if(i + z[i] - 1 > r){
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

//Complejidad O(n + m)
vector<int> pmp(string texto, string patron){
    string general = patron + "$" + texto;
    vector<int> zf = zfunction(general);
    vector<int> salida;
    for(int i = 0; i < zf.size(); i++){
        if(zf[i] == patron.size()){
            salida.push_back(i - patron.size() - 1);
        }
    }
    return salida;
}
// Termina z-funcion -----------------------

//Funcion que obtiene una transmision y un substring y que guarda las posiciones donde se encontro el substring en el archivo
void substring(string transmission, string mCode, int transNum, ofstream &file){
    vector<int> pos;
    pos = pmp(transmission, mCode); //Ejecutamos el codigo de la z-function

    //Escribimos el numero de transmision y las veces que se repitio el substring
    file << "Transmission" << transNum << ".txt ==> " << pos.size() << " veces" << endl;
    
    //Escribimos los indices donde se encontro el substring
    if(pos.size() == 0){
        file << "No hay coincidencias" << endl;
    } else {
        for(int i = 0; i < pos.size(); i++){
            file << pos[i] << " ";
        }
        file << endl;
    }
}

//Funcion que se usa para saber la cantidad de veces que se encuentra la subsequencia c dentro de t
//Complejidad O(t*c), donde t es el tamanio de la transmicion y c el tamanio del codigo que se esta buscando
int countSubsequence(string t, string code){
    //Creamos e inicializamos la matriz
    vector<vector<int>> mat;
    for(int i = 0; i <= code.length(); i++){
        if(i == code.length()){
            vector<int> aux(t.length() + 1, 1);   
            mat.push_back(aux); 
        } else {
            vector<int> aux(t.length() + 1, 0);
            mat.push_back(aux);
        }
    }

    //Realizamos el codigo, se usa programacion dinamica. Empieza del final de la matriz hacia el inicio
    //La respuesta se encuentra en mat[0][0]
    for(int j = t.length() - 1; j >= 0; j--){
        for(int i = code.length() - 1; i >= 0; i--){
            if(code.substr(i, 1) == t.substr(j,1)){
                //Si el caracter de la c y de la t en la posicion que vamos son iguales, entoces le sumamos la diagonal al valor que tenemos
                mat[i][j] = mat[i][j] + mat[i + 1][j + 1];
            }
            //Siempre sumamos el valor que esta a la derecha en la matriz
            mat[i][j] = mat[i][j] + mat[i][j + 1];
        }
    }

    return mat[0][0];
    /*
    cout << "Imprimimos" << endl;
    for(int i = 0; i <= code.length(); i++){
        for(int j = 0; j <= t.length(); j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }*/
}

//Funcion que recibe las tres transmisiones y decide cual subsequence aparece mas en ellas
void subsequence(string t1, string t2, string t3, string mCode, ofstream &file){
    //Creamos el set con las opciones para el string del mCode
    unordered_set<string> options;
    //Metemos al set las combinaciones del string sin un caracter
    string start = "";
    string end = mCode;
    for(int i = 1; i <= mCode.length(); i++){
        options.insert(start + mCode.substr(i));
        start = start + mCode.substr(i - 1, 1);
    }

    //Buscamos las subsequencias en las transmiciones de cada codigo que se hizo
    int max = 0, maxTrans = 0;
    string maxSubsq = "";
    for(auto i = options.begin(); i != options.end(); i++){
        int subT1 = countSubsequence(t1, *i);
        int subT2 = countSubsequence(t2, *i);
        int subT3 = countSubsequence(t3, *i);

        if(subT1 > max){
            max = subT1;
            maxSubsq = *i;
            maxTrans = 1;
        } else if(subT2 > max){
            max = subT2;
            maxSubsq = *i;
            maxTrans = 2;
        } else if(subT3 > max){
            max = subT3;
            maxSubsq = *i;
            maxTrans = 3;
        }
    }

    file << "La subsecuencia mas encontrada fue " << maxSubsq << " con " << max << " veces en el archivo transmission" << maxTrans << ".txt" << endl;
    file << "-----------------" << endl;
}

//Esta funcion resuelve el primer tercio de la tarea
void substringSubsequence(string t1,  string t2, string t3, vector<string> mCode, ofstream &file){
    vector<int> pos;
    int subsequences[3] = {0};
    for(int i = 0; i < mCode.size(); i++){
        //Ponemos en el archivo el mCode
        file << "Código: " << mCode[i] << endl;

        //Guardamos los substrings en el archivo, de acuerdo al mCode en el que vamos
        substring(t1, mCode[i], 1, file);
        substring(t2, mCode[i], 2, file);
        substring(t3, mCode[i], 3, file);

        subsequence(t1, t2, t3, mCode[i], file);
    }
    file << "======================================" << endl;
}

string substringFromTransmissions(string string1, string string2) {
    int max = 0; // El tamanio del LCS encontrado
    int coord;

    //Creamos e inicializamos la matriz
    vector<vector<int>> mat;
    for(int i = 0; i <= string1.length(); i++){
        vector<int> aux(string2.length() + 1, 1);   
        mat.push_back(aux); 
    }

    //Llenamos la columna de comparacion del primer valor del string 2 con todos los valores del uno, es decir la columna mat[i][0]
    for(int i = 0; i < string1.length(); i++){
        if(string2[0] == string1[i]){
            mat[i][0] = 1;
            max = 1;
        } else {
            mat[i][0] = 0;
        }
    }

    //Ahora recorremos el primer renglon, comparando el primer valor del string 1 con todos los del string dos, sera el renglon mat[0][i]
    for(int i = 0; i < string2.length(); i++){
        if(string1[0] == string2[i]){
            mat[0][i] = 1;
            max = 1;
        } else {
            mat[0][i] = 0;
        }
    }

    //Recorremos el resto de la matriz con un doble for
    int aux; //Lo usamos para almacenar el valor que se agrega a una celda y compararlo con el max
    for(int i = 1; i < string1.length(); i++){
        for(int j = 1; j < string2.length(); j++){
            if(string1[i] == string2[j]){
                //El caracter en la posicion i en el string1 es igual al caracter j en el string 2
                aux = mat[i - 1][j - 1] + 1;
                mat[i][j] = aux;
                if(max < aux){
                    max = aux;
                    coord = i;
                }
            } else {
                //Son diferentes los caracteres de los strings en la posicion i y j
                mat[i][j] = 0;
            }
        }
    }

    //En coord tenemos guardada la posicion en donde termina el substring mas largo
    //Y en max tenemos el tamanio del substring. Entonces si los restamos tenemos el
    //Indice donde empieza el substring. 

    int startSub = coord - max + 1;
    return string1.substr(startSub, max); //Obtenemos el substring
}

void findSubstrings(string t1, string t2, string t3, ofstream &file){
    file << "Los substrings mas largos son:" << endl;
    file << "T1-T2 ==> " << substringFromTransmissions(t1, t2) << endl;
    file << "T1-T3 ==> " << substringFromTransmissions(t1, t3) << endl;
    file << "T2-T3 ==> " << substringFromTransmissions(t2, t3) << endl;
}

void manacher(string texto, int numarch, ofstream &file){
	string T = "";
    int posicionInicial = 0;
	int n = texto.length();
	for (int i=0; i<n; i++){
		T += "|";
		T += texto[i];
	}
	T += "|";
	n = T.length();
	vector<int> L(n);
	L[0] = 0;
	L[1] = 1;
	int maxLong=0, maxCentro=0;
	bool exp;
	for (int c=1, li=0, ri=2; ri<n; ri++){
		li = c-(ri-c);
		exp = false;
		if (c-maxLong <= ri && ri >= c+maxLong){
			if (L[li] < (c+L[c]-ri)){
				L[ri] = L[li];
			}
			else if(L[li] == (c + L[c]) - ri && (c + L[c]) == 2*n){
				L[ri] = L[li];
			}
			else if(L[li] == (c + L[c]) - ri && (c + L[c]) < 2*n){
				L[ri] = L[li];
				exp = true;
			}
			else if(L[li] > (c + L[c]) - ri && (c + L[c]) < 2*n){
				L[ri] = (c+L[c]) - ri;
				exp = true;
			}
		}
		else{
			L[ri] = 0;
			exp = true;
		}
		if (exp){
			while((ri + L[ri] < n) && (ri - L[ri] > 0) && (T[ri - L[ri] - 1] == T[ri + L[ri] + 1])){
				L[ri]++;
			}
		}
		c = ri;
		if (L[ri] > maxLong){
	    	maxLong = L[ri];
	    	maxCentro = ri;
	    }
	}
	int inicio = (maxCentro - maxLong) / 2;
	string salida = "";
	for (int i=inicio; i<(inicio+maxLong); i++){
		salida+=texto[i];
    if(i == inicio){
      posicionInicial = i;
    }
	}

  if(numarch == 1){
    file << "Transmission1.txt ==> Posición: " << posicionInicial + 1 << endl;
    file << salida << endl;
  }else if(numarch == 2){
    file << "Transmission2.txt ==> Posición: " << posicionInicial + 1 << endl;
    file << salida << endl;
  }else if(numarch == 3){
    file << "Transmission3.txt ==> Posición: " << posicionInicial + 1 << endl;
    file << salida << endl;
  }
}

void palindromos(string t1, string t2, string t3, ofstream &file) {
    file << "Palíndromo más grande:" << endl;
    manacher(t1, 1, file);
    file << "------------" << endl;
    manacher(t2, 2, file);
    file << "------------" << endl;
    manacher(t3, 3, file);
    file << "===================================" << endl;
}

int main() {
    //Leemos y guardamos el string de cada archivo
    string t1, t2, t3;
    t1 = readTransmission("transmission1.txt");
    t2 = readTransmission("transmission2.txt");
    t3 = readTransmission("transmission3.txt");

    //Guardamos el codigo malicioso en un vector
    vector<string> mCode;
    readMaliciousCode("mcode.txt", mCode);

    ofstream file("checking.txt"); //Abrimos el archivo

    substringSubsequence(t1, t2, t3, mCode, file);
    palindromos(t1, t2, t3, file);
    findSubstrings(t1, t2, t3, file);

    //cout << substringFromTransmissions("abcdefgh", "efghijkl");

    file.close(); //Cerramos el archivo

    return 0;
}