#include "Luc.h"
#include <iostream>



/*
    Function that checks the sintax for temperature unit conversion
    @param <value_arg> A string to represent a decimal value
    @param <temperature_argument> The argument, like K>F (Kelving to Fahrenheit) or C<K (Kelving to Celsius)
    @param <feedback>
*/
bool Luc::check_temperature_sintax(std::string value_arg, std::string & temperature_arg, std::string & feedback) {
    
    std::string temperature_arg_ignore_spaces = "";

    for (int i = 0; i < temperature_arg.size(); i++)
        if (temperature_arg[i] != ' ')
            temperature_arg_ignore_spaces += toupper(temperature_arg[i]);

    temperature_arg = temperature_arg_ignore_spaces;

    if (temperature_arg.size() != 3) {

        feedback = LUC_MESSAGE_ERROR + "Format for temperature conversion not allowed. Please use the following format:\n";
        feedback += "\t>> luc -uc \"double\" \"\'Unit1\' \'<\' or \'>\' \'Unit2\'\"\n";
        return false;
    }

    char unit1, unit2, order;
    unit1 = temperature_arg[0];
    order = temperature_arg[1];
    unit2 = temperature_arg[2];

    const char * temperature_units = "CFK";

    if (! string_is_decimal(value_arg) ) {
        
        feedback = LUC_MESSAGE_ERROR + "The argument \'" + value_arg + "\' should be a decimal value.\n";
        return false;
    }

    if (order != '>' && order != '<') {

        feedback = LUC_MESSAGE_ERROR + "Format for temperature conversion not allowed. Please use the following format:\n";
        feedback += "\t>> luc -uc \"double\" \"\'Unit1\' \'<\' or \'>\' \'Unit2\'\"\n";
        return false;
    }

    if ( (! char_in_string(unit1, temperature_units)) || (! char_in_string(unit2, temperature_units)) ) {

        feedback = LUC_MESSAGE_ERROR + "The units allowed for temperature conversion are:\n";
        feedback += "\t>> C: Celsius\n\t>> F: Fahrenheit\n\t>> K: Kelvin\n";
        feedback += "\t>> Type \'luc -h\' or \'luc --help\' for more informations.\n";
        return false;
    }

    return true;
}

/*
    Funtion to change between celsius and fahrenheit
    @param <value> Decimal value
    @param <result> The result value after conversion
    @param <order> The order (from) > (to) or (to) < (from)
*/
bool Luc::censius_fahrenheit_conversor(long double value, long double & result, char order) {

    if (order != '>' && order != '<')
        return false;

    if (order == '>')
        result = (value * 9.0/5.0) + 32.0;
    else
        result = (value - 32.0) / (9.0/5.0);

    return true;
}

/*
    Funtion to change between kelvin and fahrenheit
    @param <value> Decimal value
    @param <result> The result value after conversion
    @param <order> The order (from) > (to) or (to) < (from)
*/
bool Luc::kelvin_fahrenheit_conversor(long double value, long double & result, char order) {

    if (order != '>' && order != '<')
        return false;

    if (order == '>')
        result = (9.0/5.0) * (value - 273.15) + 32;
    else
        result = (value + 459.67) * (5.0/9.0);

    return true;
}

/*
    Funtion to change between kelvin and celsius
    @param <value> Decimal value
    @param <result> The result value after conversion
    @param <order> The order (from) > (to) or (to) < (from)
*/
bool Luc::kelvin_celsius_conversor(long double value, long double & result, char order) {

    if (order != '>' && order != '<')
        return false;

    if (order == '>')
        result = value - 273.15;
    else
        result = value + 273.15;

    return true;
}