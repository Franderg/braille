
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sstream>

using namespace std;

//array<char,2> diccionario = {'1-0-0-0-0-0-','0-1-0-0-0-0-'}; 
string diccinario[2] = {"1-0-0-0-0-0-", "0-1-0-0-0-0-"};

string letras(string letra) {
   // cout << letra << endl;
    for (int i = 0; i <= 1; i++) {
        if (letra == diccinario[i]) {
            cout << "Palabra encontrada" << endl;
        }
    }
    return letra;

}

int main() {
    string letra;
    stringstream l;
    char buf[255];
    int fd = open("/dev/ttyACM1", O_RDONLY);
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
                    printf(buf);
                    //printf("aaaaaaaaaaa a");
                    //cout << res << endl;
                    letras(letra);
                    //printf(buf);
                }
            }
            //printf(res);
        }
    }
    return 0;
}