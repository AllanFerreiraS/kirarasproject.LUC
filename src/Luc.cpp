#include "Luc.h"
#include <iostream>
#include <sstream>
bool verbose = false;


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//                                  VARIABLES
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// ...


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//                              PUBLIC FUNCTIONS
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

/* 
    Function that converts a unit to another unit. Like meters to kilometers, kilometers/hour to centimeters/minutes.
    @param <value> A double value.
    @param <old_unit_argument> A string of unit(s). Like "m", "km/h".
    @param <new_unit_argument> A string of unit(s). Like "m", "km/h".
*/
bool Luc::convert_unit(std::string old_unit_argument, std::string new_unit_argument, std::string & feedback) {


    Unit old_unit, new_unit;
    long double result = 0;

    old_unit.symbol     = "luc_argument_1";
    old_unit.name       = old_unit_argument;
    old_unit.argument   = old_unit_argument;
    old_unit.unit_value = 1.0L;
    old_unit.compost    = true;

    new_unit.symbol     = "luc_argument_2";
    new_unit.name       = new_unit_argument;
    new_unit.argument   = new_unit_argument;
    new_unit.unit_value = 1.0L;
    new_unit.compost    = true;

    std::vector<std::string> old_unit_argument_token;
    std::vector<std::string> new_unit_argument_token;

    std::vector<std::string> old_unit_argument_s_yard_token;
    std::vector<std::string> new_unit_argument_s_yard_token;
    
    if (! parse_unit_arg(old_unit_argument, old_unit_argument_token, old_unit_argument_s_yard_token, feedback) )
        return false;
    
    if (! parse_unit_arg(new_unit_argument, new_unit_argument_token, new_unit_argument_s_yard_token, feedback) )
        return false;

    if (! create_unit_dimention(old_unit_argument_s_yard_token, old_unit.dimension, feedback) )
        return false;

    if ( is_dimension_empty(old_unit.dimension) ) {
        std::cout << LUC_MESSAGE_ERROR + "The argument \'"+ old_unit.argument + "\' is not a unit argument, or it cancells itself.\n";
        return false;
    }
    
    if (! create_unit_dimention(new_unit_argument_s_yard_token, new_unit.dimension, feedback) )
        return false;

    if ( is_dimension_empty(new_unit.dimension) ) {
        std::cout << LUC_MESSAGE_ERROR + "The argument \'"+ new_unit.argument + "\' is not a unit argument, or it cancells itself.\n";
        return false;
    }

    
    // Compare both dimensions
    if (! dimensions_equal(old_unit.dimension, new_unit.dimension) ) {

        std::cout << LUC_MESSAGE_ERROR + "It's not possible to convert \'"+ old_unit.argument + "\' to \'" + new_unit.argument + "\'.\n";
        std::cout << "Dimension of \'" + old_unit.argument + "\':\n";
        for (int i = 0; i < 7; i++) {

            std::cout << "\t\'" + old_unit.dimension.name[i] + "\': " + std::to_string(old_unit.dimension.exp_base[i]);
            if (i < 6)
                std::cout << ",";
        }

        std::cout << "\n\nDimension of \'" + new_unit.argument + "\':\n";
        for (int i = 0; i < 7; i++) {

            std::cout << "\t\'" + new_unit.dimension.name[i] + "\': " + std::to_string(new_unit.dimension.exp_base[i]);
            if (i < 6)
                std::cout << ",";
        }
        std::cout << "\n";
        
        return false;
    }

    if (! argument_to_value(old_unit_argument_s_yard_token, old_unit.unit_value, feedback) )
        return false;

    if (! argument_to_value(new_unit_argument_s_yard_token, new_unit.unit_value, feedback) )
        return false;

    result = old_unit.unit_value/ new_unit.unit_value;

    std::ostringstream sstream;
    sstream << result;
    std::string result_string = sstream.str();
    std::cout << result_string + "\n";
    
    return true;
}

/*
    Function converts two temperature units taking a value as parameter
    @param <value> A decimal value
    @param <argument> The argument, like K>F (Kelving to Fahrenheit) or C<K (Kelving to Celsius)
    @param <feedback>
*/
bool Luc::temperature_conversion(std::string value, std::string argument, std::string & feedback) {

    if (! check_temperature_sintax(value, argument, feedback) )
        return false;

    const char * c_f_units = "CF";
    const char * k_f_units = "KF";
    const char * k_c_units = "KC";


    char unit1, unit2, order;
    order = argument[1];
    unit1 = argument[0];
    unit2 = argument[2];

    long double result, double_value;
    double_value = std::stold(value);
    result = 0;

    if (unit1 == unit2)
        result = double_value;
    else if (char_in_string(unit1, c_f_units) && char_in_string(unit2, c_f_units)) {

        if ( (unit1 == 'F' && unit2 == 'C') )
            if (order == '>')
                order = '<';
            else
                order = '>';

        if (verbose)
            std::cout << LUC_MESSAGE_SUCCESS + "Converting Celsius(C) " + order + " Fahrenheit(F).\n";

        censius_fahrenheit_conversor(double_value, result, order);
    }
    else if (char_in_string(unit1, k_f_units) && char_in_string(unit2, k_f_units)) {

        if ( (unit1 == 'F' && unit2 == 'K') )
            if (order == '>')
                order = '<';
            else
                order = '>';

        if (verbose)
            std::cout << LUC_MESSAGE_SUCCESS + "Converting Kelvin(K) " + order + " Fahrenheit(F).\n";

        kelvin_fahrenheit_conversor(double_value, result, order);
    }
    else if (char_in_string(unit1, k_c_units) && char_in_string(unit2, k_c_units)) {

        if ( (unit1 == 'C' && unit2 == 'K') )
            if (order == '>')
                order = '<';
            else
                order = '>';

        if (verbose)
            std::cout << LUC_MESSAGE_SUCCESS + "Converting Kelvin(K) " + order + " Celsius(C).\n";

        kelvin_celsius_conversor(double_value, result, order);
    }
    else {
        feedback = LUC_MESSAGE_ERROR + "It was not possible to make the temperature conversion. Please, check your argument.\n";
        feedback += "\t>> Type \'luc -h\' or \'luc --help\' for more informations.\n";
    }

    std::ostringstream sstream;
    sstream << result;
    std::string result_string = sstream.str();
    std::cout << result_string + "\n";

    return true;
    
}