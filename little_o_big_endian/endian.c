#include <stdio.h>

int main(){
    int a = 1;
    char* p = (char*) &a;
    if (*p == 0){
        printf ("il sistema è big endian");
    }else{
        printf ("il sistema è little endian");
    }
}