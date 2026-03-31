#include "Luc.h"
#include <iostream>

/*
    Function to check if char is in a list of chars
    Ex: 'm' in ['a', 'b', 'c'] ? FALSE
    @param <c> Char
    @param <list> Pointer to a const string
*/
bool Luc::char_in_string(char c, const char * list) {

    for (int i = 0; list[i] != '\0'; i++) {
        if (c == list[i])
            return true;
    }

    return false;
}

/*
    Function to check if a char is a Latin Alphabet symbol
    @param <c> Char
*/
bool Luc::char_is_alpha(char c) {

    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

/*
    Function to check if a char is a number
    @param <c> Char
*/
bool Luc::char_is_num(char c) {

    return (c >= '0' && c <= '9');
}

/*
    Function to check if a string is a integer
    @param <str> String
*/
bool Luc::string_is_int(std::string str) {


    if (str.empty()) return false;

    int str_size = str.size();

    for (int i = 0; i < str_size; i++) {

        if (str[i] == '-' && i == 0 && str_size > 1)
            continue;
        else if (str[i] == '-' && i != 0)
            return false;
        
        if (! char_is_num(str[i]) )
            return false;
    }

    return true;
}

/*
    Function to check if a string is a decimal value
    @param <str> String
*/
bool Luc::string_is_decimal(std::string str) {

    if (str.empty()) return false;

    int str_size = str.size();
    bool dot_found =            false;
    bool number_before_dot =    false;
    bool number_after_dot =     false;

    for (int i = 0; i < str_size; i++) {
        
        if (str[i] == '-' && i == 0 && str_size > 1)
            continue;
        else if (str[i] == '-' && i != 0)
            return false;

        if (str[i] == '.') {

            if (dot_found)
                return false;

            dot_found = true;
            continue;
        }
        
        if (! char_is_num(str[i]) )
            return false;
        else if (! dot_found )
            number_before_dot = true;
        else if (dot_found)
            number_after_dot = true;
    }

    if ( dot_found && ((! number_before_dot) || (! number_after_dot)) )
        return false;

    return true;
}
