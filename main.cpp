
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <math.h>
#include <fstream>
#include <typeinfo>

using namespace std;

//diccionarios con el alfabeto
string diccinario[] = {"100000", "110000", "100100", "100110", "100010",
    "110100", "110110", "110010", "010100", "010110", "101000", "111000",
    "101100", "101110", "110111", "101010", "111100", "111110", "111010",
    "011100", "011110", "101001", "111001", "010111", "101101", "101111",
    "101011", "110001", "001110", "001001", "001010"};

string listaLetrasM[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
    "L", "M", "N", "NY", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y",
    "Z"};

string listaLetrasm[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
    "l", "m", "n", "NY", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y",
    "z", "(", ")", "-", "*"};

string listaNum[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};

//Buscamos la letra leida con el sensor en el diccionario

string letras(string letra, bool mayus, bool num) {
    if (num == true) {
        for (int i = 0; i < 10; i++) {//buscamos en el diccionario
            if (letra == diccinario[i]) {//si la letra de entrada esta en el diccionario
                return listaNum[i]; //si la encontramos se retorna
            }
        }
    } else {
        if (mayus == false) { // verificamos si es mayuscula
            for (int i = 0; i < 27; i++) {//buscamos en el diccionario
                if (letra == diccinario[i]) {//si la letra de entrada esta en el diccionario
                    return listaLetrasm[i]; //si la encontramos se retorna
                }
            }
        } else {
            for (int i = 0; i < 27; i++) {//buscamos en el diccionario
                if (letra == diccinario[i]) {//si la letra de entrada esta en el diccionario
                    return listaLetrasM[i]; //si la encontramos se retorna
                }
            }
        }
    }
    return ""; //en caso de no encontrar la letra se retorna la entrada
}

//Pasamos lo que leemos del puerto serial a string para concatenarlo

string conv(string dec) {
    int letra[] = {0, 0, 0, 0, 0, 0}; //arreglo con la letra leida
    int numero = atoi(dec.c_str()); //pasamos el numero a binario
    int residuo;
    int i = 5;
    while (numero >= 1) {//obtenemos el numero
        residuo = numero % 2;
        numero = numero / 2;
        letra[i] = residuo;
        i -= 1;
    }
    string lett = "";
    std::stringstream o;
    for (int i = 0; i <= 5; i++) {//pasamos el int a string
        o << letra[i];
    }
    lett = o.str();
    return lett;
}

bool mayus = false; //iniciamos la bandera de mayusculas
bool corchete = false;
bool barra = false;
bool num = false;

int main() {
    string letra; //Variable a escribir en el archivo TEC
    string let;
    int bits;
    char buf[36];
    ofstream salida("salida.txt"); //archivo de salida
    int fd = open("/dev/ttyACM0", O_RDONLY); //abrimos el puerto
    if (fd == -1) {//si la lectura es de -1 quiere decir que el puerto no se esta usando
        printf("El puerto no esta disponible");
    } else {
        int res;
        while (true) {
            while ((res = read(fd, buf, bits)) == 0); //lectura del puerto
            {
                /*   if (res > 0) {
                       buf[res] = 0;
                       letra += buf;
                       cout << buf << " - " << endl;
                   }*/
                if (res > 0) {
                    buf[res] = 0;
                    let = buf;
                    cout << letras(conv(let), mayus, num) << endl;
                    if (conv(let) == "000101") {//si se tiene que la letra es mayuscula, activamos nuna bandera
                        mayus = true;
                    } else if (conv(let) == "001111") {//simbolo para numeros
                        num = true;
                    } else if (let == "s") {//si viene un espacio se agrega
                        cout << "espacio" << endl;
                        letra += " ";
                    } else if (let == "e") {//el salto de linea ("enter") 
                        salida << letra << endl;
                        letra = "";
                        mayus = false;
                        num = false;
                        barra = false;
                        corchete = false;
                    } else if (conv(let) == "111000" && corchete == true) {//corchete
                        letra += "{";
                        corchete = false;
                    } else if (conv(let) == "010000" && corchete == true) {//corchete
                        letra += "}";
                        corchete = false;
                    } else if (conv(let) == "000010" or conv(let) == "000111") {//corchete
                        corchete == true;
                        num = false;
                    } else if (barra == true && conv(let) == "010000") {//signo de div
                        letra += "/";
                        barra = false;
                    } else if (conv(let) == "000001") {//para div
                        barra = true;
                    } else {
                        letra += letras(conv(let), mayus, num); //buscamos la letra
                        //cout << letras(conv(buf), mayus, num) << endl;
                        mayus = false;
                        corchete = false;
                        barra = false;
                    }
                }
            }
        }
    }
    salida.close(); //se cierra el archivo 
    return 0;
}