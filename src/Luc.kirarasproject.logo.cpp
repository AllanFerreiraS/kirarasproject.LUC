#include <iostream>
#include <stdlib.h>
#include "Luc.h"

void Luc::print_kirarasproject_logo() {

    FILE * p_kirarasproject_txt;
    char ch = ' ';

    p_kirarasproject_txt = fopen("./src/Luc.kirarasproject_logo.txt", "r");
    if (p_kirarasproject_txt == NULL) {

        std::cout << "It was not possible to print kirarasproject logo. Instead, I'll do this:\n";
        std::cout << "---------------------------------------\n";
        std::cout << "\t>> KIRARA'S PROJECT\n";
        std::cout << "---------------------------------------\n";
        return;
    }

    while ( ( ch = fgetc(p_kirarasproject_txt) ) != EOF )
        putchar(ch);

    fclose(p_kirarasproject_txt);

    return;
}