#include "Luc.h"
#include <iostream>

/*
    Function to print a vector<string>
    @param <v> vector<string>
*/
void Luc::print_vector(std::vector<std::string> v) {

    std::cout << ">> [ ";
    for (int i = 0; i < v.size(); i++) {
        if (i < v.size() - 1)
            std::cout << v[i] << ", ";
        else
            std::cout << v[i];
    }
    std::cout << " ]" << std::endl << std::endl;
}

void Luc::print_vector_long_double(std::vector<long double> v) {

    std::cout << ">> [ ";
    for (int i = 0; i < v.size(); i++) {
        if (i < v.size() - 1)
            std::cout << v[i] << ", ";
        else
            std::cout << v[i];
    }
    std::cout << " ]" << std::endl;
}

/*
    Function to print a vector<Unit_dimension>
    @param <v> vector<Unit_dimension>
*/
void Luc::print_vector_dimension(std::vector<Unit_dimension> v) {

    std::cout << ">> { ";
    for (int i = 0; i < v.size(); i++) {
        std::cout << "[";

        for (int j = 0; j < 7; j++) {
            if (j < 6)
                std::cout << v[i].exp_base[j] << ",";
            else
                std::cout << v[i].exp_base[j];
        }
        if (i < v.size() - 1)
            std::cout << "], ";
        else
            std::cout << "]";
    }
    std::cout << " }" << std::endl;
}

/*
    Function to print a Unit_dimension
    @param <v> Unit_dimension
*/
void Luc::print_dimension(Unit_dimension v) {

    std::cout << "[";
    for (int i = 0; i < 7; i++) {
        if (i < 6)
            std::cout << v.exp_base[i] << ",";
        else
            std::cout << v.exp_base[i];
    }
    std::cout << "]";
}

void Luc::luc_help() {

    std::cout << "LUC - Luc Unit Converter\n\n";
    std::cout << "Usage:\n";
    std::cout << "\tluc [command] [arguments]\n\n";
    std::cout << "Commands:\n";
    std::cout << "\t-h, --help\n";
    std::cout << "\t\tShow this help message\n\n";
    std::cout << "\t-cu, --conversion-unit <arg1> <arg2> [-v, --verbose]\n";
    std::cout << "\t\tPerform unit conversion\n\n";
    std::cout << "\t\tThere are two modes:\n\n";
    std::cout << "\t\t1) General Unit Conversion\n";
    std::cout << "\t\tConvert between unit expressions\n\n";
    std::cout << "\t\tExample:\n";
    std::cout << "\t\t\tluc -cu \"km/h\" \"m/s\"\n";
    std::cout << "\t\t\tluc -cu 10m cm\n\n";
    std::cout << "\t\t2) Temperature Conversion\n";
    std::cout << "\t\tConvert temperature values\n\n";
    std::cout << "\t\tSyntax:\n";
    std::cout << "\t\t\tluc -cu <value> <UNIT1><OPERATOR><UNIT2>\n\n";
    std::cout << "\t\tOperators:\n";
    std::cout << "\t\t\t> Convert from UNIT1 to UNIT2\n";
    std::cout << "\t\t\t< Convert from UNIT2 to UNIT1\n";
    std::cout << "\t\tExamples:\n";
    std::cout << "\t\t\tluc -cu 12.3 C>K   (Celsius to Kelvin)\n";
    std::cout << "\t\t\tluc -cu 12.3 C<K   (Kelvin to Celsius)\n\n";
    std::cout << "\tOptions:\n";
    std::cout << "\t\t-v, --verbose:\n";
    std::cout << "\t\t\tShow detailed conversion steps\n\n";
    std::cout << "\t--kirarasproject\n";
    std::cout << "\t\tPrint Kirara's Project logo\n\n";
    std::cout << "Notes:\n";
    std::cout << "\t- Unit expressions support: *, /, ^, and parentheses\n";
    std::cout << "\t- Example: kg*m^2/(s^2*A)\n";

    return;
}