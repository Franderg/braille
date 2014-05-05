
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sstream>

using namespace std;

string diccinario[27] = {"1-0-0-0-0-0-", "1-1-0-0-0-0-", "1-0-0-1-0-0-",
    "1-0-0-1-1-0-", "1-0-0-0-1-0-", "1-1-0-1-0-0-", "1-1-0-1-1-0-",
    "1-1-0-0-1-0-", "0-1-0-1-0-0-", "0-1-0-1-1-0-", "1-0-1-0-0-0-",
    "1-1-1-0-0-0-", "1-0-1-1-0-0-", "1-0-1-1-1-0-", "1-1-0-1-1-1-",
    "1-0-1-0-1-0-", "1-1-1-1-0-0-", "1-1-1-1-1-0-", "1-1-1-0-1-0-",
    "0-1-1-1-0-0-", "0-1-1-1-1-0-", "1-0-1-0-0-1-", "1-1-1-0-0-1-",
    "0-1-0-1-1-1-", "1-0-1-1-0-1-", "1-0-1-1-1-1-", "1-0-1-0-1-1-",};

string listaLetras[27] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
    "L", "M", "N", "NY", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y",
    "Z"};

string letras(string letra) {
    for (int i = 0; i < 27; i++) {
        if (letra == diccinario[i]) {
            return listaLetras[i];
        }
    }
    return letra;
}

int main() {
    string letra;
    int bits;
    char buf[11];
    int fd = open("/dev/ttyACM0", O_RDONLY);
    if (fd == -1) {
        printf("El puerto no esta disponible");
    } else {
        int res;
        while (true) {
            while ((res = read(fd, buf, bits)) == 0);
            {
                if (res > 0) {
                    buf[res] = 0;
                    letra += buf;
                }
                if (letra.size() == 12) {
                    cout << letras(letra) << endl;
                    letra = "";
                }
            }
        }
    }
    return 0;
}