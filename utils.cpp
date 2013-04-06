#include "header.h"
#include "utils.h"

void videBuf(char *buf, int taille){
    for(int i = 0; i < taille; i++){
        *(buf+i) = '\0';
    }

}

void printError(const char *msg){
    QFile file;
    file.open(stderr, QIODevice::WriteOnly);
    file.write(msg, qstrlen(msg));
    file.close();
 }
