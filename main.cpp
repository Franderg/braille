
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sstream>

using namespace std;


string diccinario[2] = {"1-0-0-0-0-0-", "0-1-0-0-0-0-"};
string listaLetras[2] = {"A", "B"};

string letras(string letra) {
    for (int i = 0; i < 2; i++) {
        if (letra == diccinario[i]) {
            return listaLetras[i];
        }   
    }
    return letra;
}

int main() {
    string letra;
    string lett;
    stringstream l;
    char buf[255];
    int fd = open("/dev/ttyACM0", O_RDONLY);
    if (fd == -1) {
        printf("El puerto no esta disponible");
    } else {
        int res;
        while (true) {
            while ((res = read(fd, buf, 255)) == 0);
            {
                if (res > 0) {
                    buf[res] = 0;
                    l << buf;
                    l >> letra;
                    lett += letra; 
                }
                cout << letras(lett) << endl;
                lett="";
            }
        }
    }
    return 0;
}