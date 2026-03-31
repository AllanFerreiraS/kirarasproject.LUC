#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "src/Luc.h"

typedef struct Str_luc_command {
    std::string str_command;
    int         value_command;
} Luc_command;

const int luc_command_size = 5;
Luc_command luc_command[luc_command_size] = {
    { .str_command="-cu",                   .value_command=0 },
    { .str_command="--conversion-unit",     .value_command=0 },
    { .str_command="--kirarasproject",      .value_command=1 },
    { .str_command="-h",                    .value_command=2 },
    { .str_command="--help",                .value_command=2 },
};


void ignore_quotation_mark_if_any(std::string & s) {
    
    int s_size = s.size();
    std::string s_temp = "";

    for (int i = 0; i < s_size; i++) {
        
        if (i == 0 && ( (s[i] == '\'') || (s[i] == '\"') ) )
            continue;
        else if (i == (s_size - 1) && ( (s[i] == '\'') || (s[i] == '\"') ) )
            continue;
        
        s_temp.push_back(s[i]);
    }

    s.clear();
    s = s_temp;
    s_temp.clear();
}

int get_command_value(std::string l_c) {

    for (int i = 0; i < luc_command_size; i++)
        if (l_c == luc_command[i].str_command)
            return luc_command[i].value_command;
    return -1;
}




int main(int argc, char ** argv) {

    std::string feedback        = "";
    int command_value           = -1;

    std::string arg1, arg2, arg3, command_name;
    arg1 = arg2 = arg3 = command_name = "";

    if (argc >= 2) {

        command_name                = argv[1];
        command_value               = get_command_value(command_name);
    }
    if (argc >= 3)
        arg1 =      argv[2];
    if (argc >= 4)
        arg2 =      argv[3];
    if (argc == 5)
        arg3 =      argv[4];
    if (argc > 5) {

        std::cout << LUC_MESSAGE_ERROR + "To many arguments.\n";
        std::cout << "\t>> Type \'luc -h\' or \'luc --help\' for more informations." << std::endl;
        return EXIT_FAILURE;
    }


    if ( command_value == 0 ) {

        bool run_temperature    = false;

        ignore_quotation_mark_if_any(arg1);
        ignore_quotation_mark_if_any(arg2);

        // Check for verbose
        if (arg3 == "--verbose" || arg3 == "-v")
            verbose = true;

        // Check for temperature Sintax
        for (int i = 0; i < arg2.size(); i++)
            if ( (arg2[i] == '>') || (arg2[i] == '<') ) {

                run_temperature = true;
            }
                
        if (run_temperature) {
            
            if (! Luc::temperature_conversion(arg1, arg2, feedback) ) {
                std::cout << feedback;
                return EXIT_FAILURE;
            }
        }
        else {

            if (! Luc::convert_unit(arg1, arg2, feedback) ) {
                std::cout << feedback;
                return EXIT_FAILURE;
            }
        }
    }
    else if (command_value == 1) {

        Luc::print_kirarasproject_logo();
    }
    else if (command_value == 2) {

        Luc::luc_help();
    }
    else if (command_value == -1) {

        std::cout << "LUC does not recogise the command \'" + command_name + "\'." << std::endl;
        std::cout << "\t>> Type \'luc -h\' or \'luc --help\' for more informations." << std::endl;
    }
    else {

        std::cout << "Exit..." << std::endl;
    }


    return EXIT_SUCCESS;
}
