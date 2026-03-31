#include "Luc.h"
#include <iostream>
#include <cmath>

/*
    Function that generates the Unit Dimension of a unit argument.
    @param <s_yard> String Array containing the arguments
    @param <feedback> Feedback
*/
bool Luc::create_unit_dimention(std::vector<std::string> s_yard, Unit_dimension & dimension_created, std::string & feedback) {

    if ( s_yard.empty() ) {
        feedback = LUC_MESSAGE_ERROR + "Shunting Yard List is empty.\n";
        return false;
    }

    int index, index_v1_content, index_v2_content, s_yard_size, s_yard_content_size, trash;
    index = 0;
    s_yard_size = s_yard.size();
    s_yard_content_size = 0;
    trash = -1;

    index_v1_content = index_v2_content = 0;

    std::string a,b, op;
    a = b = op = "";

    std::vector<Unit_dimension> dimensions;
    Unit_dimension dimension_buffer, dim1, dim2;
    
    // Using for empty Unit_dimension
    Unit_dimension dimension_empty;

    // Let's fill the vector dimensions with the units stored in s_yard.
    for (int i = 0; i < s_yard_size; i++) {
        
        s_yard_content_size = s_yard[i].size();
        
        // Ignore Operator Symbols and decimals
        if ( ( char_in_string(s_yard[i][0], UNIT_SINTAX_LEGAL_SYMBOLS) ) )
            continue;
        
        // Decimals and prefixes_
        if ( (string_is_decimal(s_yard[i])) || ((is_unit_prefix( s_yard[i].substr(0, s_yard_content_size - 1), trash)) && (s_yard[i][s_yard_content_size - 1] == '_')) )  {
            dimensions.push_back(dimension_empty);
            continue;
        }
                
        if (! extract_si_unit_dimension(s_yard[i], dimension_buffer) ) {

            feedback = LUC_MESSAGE_ERROR + "SI Unit \'" + s_yard[i] + "\' was not found while trying to generate the unit dimension.\n";
            return false;
        }

        dimensions.push_back(dimension_buffer);
    }

    if (verbose) {

        std::cout << LUC_MESSAGE_SUCCESS + "Dimensions extracted: " << std::endl;
        print_vector_dimension(dimensions);
    }

    while ( index < s_yard.size() ) {

        if ( ( char_in_string(s_yard[index][0], UNIT_SINTAX_LEGAL_SYMBOLS) ) ) {

            if ( (index - 2) < 0 ) {
                feedback = LUC_MESSAGE_ERROR + "Operand \'" + s_yard[index]+ "\' with incomplete arguments.\n";
                return false;
            }
            
            index_v1_content = index - 2;
            index_v2_content = index - 1;

            a = s_yard[index_v1_content];
            b = s_yard[index_v2_content];

            dim1 = dimensions[index_v1_content];
            dim2 = dimensions[index_v2_content];
            op = s_yard[index];

            // Operação com Dimensão
            if (! dimension_operator(dim1, dim2, op, b, dimension_buffer) ) {

                feedback = LUC_MESSAGE_ERROR + "Ocorreu um erro ao tentar fazer operações com dimensões da unidade.\n";
                return false;
            }


            dimensions[index_v1_content] = dimension_buffer;
            dimensions.erase(dimensions.begin() + index_v2_content);

            if (verbose) {

                std::cout << "\t " + std::to_string((index_v1_content + 1)) + "° Dimension (" + op + ") " + std::to_string((index_v2_content + 1)) + "° Dimension.\n";
                print_vector_dimension(dimensions);
            }

            s_yard.erase(s_yard.begin() + index);
            s_yard.erase(s_yard.begin() + index_v2_content);
            s_yard[index_v1_content] = UNIT_DONE_FLAG;
            index = 0;
            continue;
        }

        index++;
    }

    if (verbose)
        std::cout << std::endl;

    dimension_created = dimensions[0];

    return true;
}

/*
    Function that is used as an operator for unit's exponents.
    @param <v1> The first Dimension
    @param <v2> The second dimension
    @param <op> The operator [*, / or ^].
    @param <exp_value> If the operator '^' is found, all the dimensions in v2 is 0 and the exponent intenger is stores here to calculate v1
    @param <le_dimension> El resultado de la operación entre v1 y v2 se almacenará aquí
*/
bool Luc::dimension_operator(Unit_dimension v1, Unit_dimension v2, std::string op, std::string exp_value, Unit_dimension & le_dimension) {

    try {

        if (op == "*") {
            for (int i = 0; i < 7; i++)
                v1.exp_base[i] += v2.exp_base[i];
                le_dimension = v1;
        }
        else if (op == "/") {

            for (int i = 0; i < 7; i++) {
                v2.exp_base[i] *= (-1);
                v1.exp_base[i] += v2.exp_base[i];
            }

            le_dimension = v1;
        }
        else if (op == "^") {

            for (int i = 0; i < 7; i++)
                v1.exp_base[i] *= stol(exp_value);
            
            le_dimension = v1;
        }
        else {

            le_dimension = v1;
        }
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

/*
    Function that compares two dimensions to check if both are equal
    @param <v1> Unit_dimension
    @param <v2> Unit_dimension
*/
bool Luc::dimensions_equal(Unit_dimension v1, Unit_dimension v2) {

    for (int i = 0; i < 7; i++) {

        if (v1.exp_base[i] != v2.exp_base[i])
            return false;
    }

    return true;
}

/*
    Function to check if a dimension is empty
    @param <dim> The dimension
*/
bool Luc::is_dimension_empty(Unit_dimension dim) {

    bool is_empty = true;

    for (int i = 0; i < 7; i++)
        if (dim.exp_base[i] != 0) is_empty = false;
    
    return is_empty;
}


























// Tacar em outro arquivo depois

bool Luc::argument_to_value(std::vector<std::string> s_yard, long double & value_result, std::string & feedback) {

    
    if ( s_yard.empty() ) {
        feedback = LUC_MESSAGE_ERROR + "Shunting Yard List is empty.\n";
        return false;
    }

    int index, index_v1_content, index_v2_content, s_yard_size;
    index = 0;
    s_yard_size = s_yard.size();

    index_v1_content = index_v2_content = 0;

    // I'll store the values here
    std::vector<long double> unit_values;

    std::string a, b, op, temp_string;
    a = b = op = temp_string = "";

    long double v1,v2, result, temp_double;
    v1 = v2 = result = temp_double = 0;

    for (int i = 0; i < s_yard_size; i++) {

        temp_string = s_yard[i];

        // Se achar o '-', é bom verificar se é um char ou uma string para decimal.
        if ( char_in_string(temp_string[0], ARITHMETIC_LEGAL_OPERATOR_SYMBOLS) && ( temp_string.size() == 1 ) )
            continue;

        if (! convert_number_and_unit_strings_to_decimal(temp_string, temp_double) ) {

            feedback = LUC_MESSAGE_ERROR + "Occurred an error while trying to convert the string \'" + temp_string + "\' to double format.\n";
            return false;
        }

        unit_values.push_back(temp_double);
    }

    if (verbose) {

        std::cout << LUC_MESSAGE_SUCCESS + "Values extracted: [@] Represents the working done.\n";
        print_vector_long_double(unit_values);
    }

    while ( index < s_yard.size() ) {

        // Se achar o '-', é bom verificar se é um char ou uma string para decimal.
        if ( char_in_string(s_yard[index][0], ARITHMETIC_LEGAL_OPERATOR_SYMBOLS) && ( s_yard[index].size() == 1 ) ){

            if ( (index - 2) < 0 ) {

                feedback = LUC_MESSAGE_ERROR + "Operand \'" + s_yard[index]+ "\' with incomplete arguments.\n";
                return false;
            }

            index_v1_content = index - 2;
            index_v2_content = index - 1;
        
            a = s_yard[index_v1_content];
            b = s_yard[index_v2_content];

            v1 = unit_values[index_v1_content];
            v2 = unit_values[index_v2_content];
            op = s_yard[index];
            

            if (! basic_arithmetics(v1, v2, op, result) ) {

                feedback = LUC_MESSAGE_ERROR + "Occurred an error while trying to perform the following operation:\n\t>> \'" + std::to_string(v1) + " " + op + " "+ std::to_string(v2) + "\'\n";
                return false;
            }

            if (verbose)
                std::cout << "\t[" + a + " " + op + " " + b + "] converted is [" + std::to_string(v1) + " " + op + " " + std::to_string(v2) + " = " + std::to_string(result) + "]\n";

            unit_values[index_v1_content] = result;
            unit_values.erase(unit_values.begin() + index_v2_content);

            if (verbose)
                print_vector_long_double(unit_values);
            
            s_yard.erase(s_yard.begin() + index);
            s_yard.erase(s_yard.begin() + index_v2_content);
            s_yard[index_v1_content] = UNIT_DONE_FLAG;
            index = 0;
            continue;
        }
        index++;
    }

    if (verbose)
        std::cout << std::endl;

    value_result = unit_values[0];

    return true;
}

/*
    Function that will take a string value or a unit to convert into a actuall double value
    @param <value> The string argument
    @param <decimal_value> The actuall value in double
*/
bool Luc::convert_number_and_unit_strings_to_decimal(std::string value, long double & decimal_value) {

    try {

        int ignore = -1;
        int value_size = value.size();
        Unit_prefix prefix;
        
        //FOR DECIMALS
        if ( string_is_decimal(value) ) {

            decimal_value = std::stold(value);
            return true;
        }
        // For Prefixes
        else if ( (is_unit_prefix( value.substr(0, value_size - 1), ignore)) && (value[value_size - 1] == '_') ) {
        
            extract_prefix(value.substr(0, value_size - 1), prefix);
            decimal_value = prefix.prefix_value;
            return true;
        }
        // FOR SI UNITS
        else if ( unit_exist(value) && ( extract_si_unit_value(value, decimal_value) ) )
            return true;
        // error
        else {
            
            decimal_value = 0;
            return false;
        }
    }
    catch(const std::exception& e) {}
    
    decimal_value = 0;
    return false;
}


bool Luc::basic_arithmetics(long double v1, long double v2, std::string op, long double & result) {

    try {

        if (op == "+")
            result = v1 + v2;
        else if (op == "-")
            result = v1 - v2;
        else if (op == "*")
            result = v1 * v2;
        else if (op == "/") {
            if (v2 == 0)
                return false;
            result = v1 / v2;
        }
        else if (op == "^")
            result =  pow(v1, v2);
        else
            return false;
        }
    catch(const std::exception& e) {
        return false;
    }

    return true;
}