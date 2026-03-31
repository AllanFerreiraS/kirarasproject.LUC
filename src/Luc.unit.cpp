#include "Luc.h"
#include <iostream>

/*
    Function to check if string is a unit
    @param <s> Unit symbol
    @param <units> List of units to check
    @param <len> Length of the list
    @param <found> Index of the Unit found
*/
bool Luc::is_unit(std::string s, const Unit * units, int len, int & found) {

    for (int i = 0; i < len; i++) {
        if (s == units[i].symbol) {
            found = i;
            return true;
        }
    }
    found = -1;
    return false;
}

/*
    Function to check if Unit symbol with prefix refers to an existing unit
    @param <s> Unit symbol
*/
bool Luc::unit_exist(std::string s) {

    // I dont know...
    // int trash = 0;
    
    std::string ignore_prefix, ignore_unit;
    ignore_prefix = ignore_unit = "";

    if (! split_prefix_from_unit(s, ignore_prefix, ignore_unit) )
        return false;

    return true;
    
    /*
    if ( is_unit(s, si_units, si_units_len, trash) )
        return true;
    if ( is_unit(s, units, units_len, trash) )
        return true;
    return false;
    */
}

/*
    Function that will return the index of si unit dimension in the Unit_dimension array
    @param <s> Unit Symbol
    PS: Am I even using this function throughout my project???????????????????????????
*/
int Luc::si_unit_dimension_index(std::string s) {

    int si_unit_index = 0;

    if ( is_unit(s, si_units, si_units_len, si_unit_index) ) {

        for (int i = 0; i < 7; i++) {
            if (si_units[si_unit_index].dimension.exp_base[i] > 0)
                return i;
        }
    }

    return -1;
}

/*
    Function that extracts the double value of a unit
    @param <unit> The symbol of the unit
    @param <value> The value returned
*/
bool Luc::extract_si_unit_value(std::string unit, long double & value) {

    int unit_index = -1;

    if ( is_unit(unit, si_units, si_units_len, unit_index) ) {
        value = si_units[unit_index].unit_value;
        return true;
    }

    return false;
}

/*
    Function to extract the dimension of a si unit
    @param <unit> A unit symbol
    @param <extracted_dimension> It will store the dimension in this variable if the si unit is found
*/
bool Luc::extract_si_unit_dimension(std::string unit, Unit_dimension & extracted_dimension) {

    int unit_index = -1;
    std::string ignore_prefix, extracted_unit;
    ignore_prefix = extracted_unit = "";

    if (! split_prefix_from_unit(unit, ignore_prefix, extracted_unit) )
        return false;

    if ( is_unit(extracted_unit, si_units, si_units_len, unit_index) ) {
        extracted_dimension = si_units[unit_index].dimension;
        return true;
    }

    return false;
}

/*
    Function to check if Unit is a compost Unit.
    @param <s> Unit symbol
*/
bool Luc::is_compost_unit(std::string s) {

    for (int i = 0; i < units_len; i++) {
        if ( (s == units[i].symbol) && (units[i].compost) )
            return true;
    }

    return false;
}

/*
    Function to extract a compost Unit
    @param <s> Unit symbol
*/
std::string Luc::extract_compost_unit(std::string s) {

    int index = 0;
    if (! is_unit(s, units, units_len, index) )
        return "";
    
    return units[index].argument;
}

/*
    Function to check is a string represents a unit prefix
    @param <prefix> The prefix itself...
*/
bool Luc::is_unit_prefix(std::string prefix, int & found) {

    if (prefix.size() <= 0)
        return false;

    for (int i = 0; i < unit_prefixes_len; i++) {

        if (prefix == unit_prefixes[i].prefix) {
            found = i;
            return true;
        }
    }

    found = -1;
    return false;
}

/*
    Function to extract the prefix
    @param <prefix> The prefix itself...
    @param <extracted_prefix> The prefix the you extracted with the function...
*/
bool Luc::extract_prefix(std::string prefix, Unit_prefix & extracted_prefix) {

    int prefix_index = -1;
    if ( is_unit_prefix(prefix, prefix_index ) ) {

        extracted_prefix = unit_prefixes[prefix_index];
        return true;
    }

    return false;
}

/*
    Function that separates the prefix (if exists) from unit.
    @param <prefix_unit> The unit with possible prefix in it.
    @param <prefix> The prefix extracted
    @param <unit> The unit extracted
*/
bool Luc::split_prefix_from_unit(std::string prefix_unit, std::string & prefix, std::string & unit) {


    int prefix_unit_size, ignore;
    ignore = -1;
    prefix_unit_size = prefix_unit.size();
    
    prefix = unit = "";

    if (prefix_unit_size <= 0)
        return false;

    if ( is_unit(prefix_unit, si_units, si_units_len, ignore) || is_unit(prefix_unit, units, units_len, ignore) ) {

        unit = prefix_unit;
        return true;
    }

    if (prefix_unit_size >= 2) {

        prefix = prefix_unit.substr(0, 2);
        unit = prefix_unit.substr(2, prefix_unit_size - 2);

        if ( is_unit_prefix(prefix, ignore) && ( is_unit(unit, si_units, si_units_len, ignore) || is_unit(unit, units, units_len, ignore) ) )
            return true;
        
        prefix = prefix_unit.substr(0, 1);
        unit = prefix_unit.substr(1, prefix_unit_size - 1);

        if ( is_unit_prefix(prefix, ignore) && ( is_unit(unit, si_units, si_units_len, ignore) || is_unit(unit, units, units_len, ignore) ) )
            return true;
    }
    return false;
}
