#ifndef LUC_H
#define LUC_H

#include <iostream>
#include <vector>


// Structs ==========================================
typedef struct Str_operator {
    char symbol;
    char precedence;
    char associativity;
} Operator;

typedef struct Str_unit_dimension {
    int exp_base[7] =       {0,0,0,0,0,0,0};
    std::string name[7] =   {"time", "length", "mass", "electric current", "thermodynamic temperature", "amount of substance", "luminous intensity"};
} Unit_dimension;

typedef struct Str_unit_prefix {
    std::string name;
    std::string prefix;
    long double prefix_value;
} Unit_prefix;

typedef struct Str_unit {

    std::string     symbol;
    std::string     name;
    std::string     argument;
    Unit_dimension  dimension;
    long double     unit_value;
    bool            compost;
} Unit;


// Consts ==========================================
const std::string LUC_MESSAGE_ERROR =   "[LUC ERROR]: ";
const std::string LUC_MESSAGE_SUCCESS = "[LUC]: ";

extern const char * UNIT_INPUT_LEGAL_SYMBOLS;
extern const char * UNIT_SINTAX_LEGAL_SYMBOLS;
extern const char * ARITHMETIC_LEGAL_OPERATOR_SYMBOLS;
extern const char * UNIT_DONE_FLAG;
extern bool verbose;

const int unit_prefixes_len = 18; 
const Unit_prefix unit_prefixes[unit_prefixes_len] = {
    { .name="zetta",    .prefix="Z",        .prefix_value=1e21L},
    { .name="exa",      .prefix="E",        .prefix_value=1e18L},
    { .name="peta",     .prefix="P",        .prefix_value=1e15L},
    { .name="tera",     .prefix="T",        .prefix_value=1e12L},
    { .name="giga",     .prefix="G",        .prefix_value=1e9L},
    { .name="mega",     .prefix="M",        .prefix_value=1e6L},
    { .name="kilo",     .prefix="k",        .prefix_value=1e3L},
    { .name="hecto",    .prefix="h",        .prefix_value=1e2L},
    { .name="deca",     .prefix="da",       .prefix_value=1e1L},
    { .name="deci",     .prefix="d",        .prefix_value=1e-1L},
    { .name="centi",    .prefix="c",        .prefix_value=1e-2L},
    { .name="milli",    .prefix="m",        .prefix_value=1e-3L},
    { .name="micro",    .prefix="u",        .prefix_value=1e-6L},
    { .name="nano",     .prefix="n",        .prefix_value=1e-9L},
    { .name="pico",     .prefix="p",        .prefix_value=1e-12L},
    { .name="femto",    .prefix="f",        .prefix_value=1e-15L},
    { .name="atto",     .prefix="a",        .prefix_value=1e-18L},
    { .name="zepto",    .prefix="z",        .prefix_value=1e-21L}
};

const int si_units_len = 7;
const Unit si_units[si_units_len] = {
    { .symbol="s",      .name="second",     .argument="s",      .dimension={.exp_base={1,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=false },
    { .symbol="m",      .name="meter",      .argument="m",      .dimension={.exp_base={0,1,0,0,0,0,0}}, .unit_value=1.0L,  .compost=false },
    { .symbol="g",      .name="gram",       .argument="g",      .dimension={.exp_base={0,0,1,0,0,0,0}}, .unit_value=1.0L,  .compost=false },
    { .symbol="A",      .name="ampere",     .argument="A",      .dimension={.exp_base={0,0,0,1,0,0,0}}, .unit_value=1.0L,  .compost=false },
    { .symbol="K",      .name="kelvin",     .argument="K",      .dimension={.exp_base={0,0,0,0,1,0,0}}, .unit_value=1.0L,  .compost=false },
    { .symbol="mol",    .name="mole",       .argument="mol",    .dimension={.exp_base={0,0,0,0,0,1,0}}, .unit_value=1.0L,  .compost=false },
    { .symbol="cd",     .name="candela",    .argument="cd",     .dimension={.exp_base={0,0,0,0,0,0,1}}, .unit_value=1.0L,  .compost=false }
};

const int units_len = 30;
const Unit units[units_len] = {
    // Time
    { .symbol="min",    .name="minute",     .argument="60*s",           .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="h",      .name="hour",       .argument="60*min",         .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="day",    .name="day",        .argument="24*h",           .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="week",   .name="week",       .argument="7*day",          .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="year",   .name="year",       .argument="365*day",        .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="Hz",     .name="hertz",      .argument="s^-1",           .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="N",      .name="newtown",    .argument="kg*m/s^2",       .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="Pa",     .name="pascal",     .argument="N/m^2",          .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="J",      .name="joule",      .argument="kg*m^2*s^-2",    .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="W",      .name="watt",       .argument="J/s",            .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="C",      .name="coulomb",    .argument="A*s",            .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="V",      .name="volt",       .argument="W/A",            .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="F",      .name="farad",      .argument="C/V",            .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="ohm",    .name="ohm",        .argument="V/A",            .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="S",      .name="siemens",    .argument="A/V",            .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="Wb",     .name="weber",      .argument="V*s",            .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="T",      .name="tesla",      .argument="Wb/m^2",         .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="H",      .name="henry",      .argument="Wb/A",           .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    //{ .symbol="lm",     .name="lumen",    .argument="cd*sr",          .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    //{ .symbol="lx",     .name="lux",      .argument="lm/m^2",         .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="Bq",      .name="becquerel",  .argument="s^-1",          .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="Gy",      .name="gray",       .argument="J/kg",          .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="Sv",      .name="sievert",    .argument="J/kg",          .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="kat",     .name="katal",      .argument="mol*s^-1",      .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="area",    .name="area",       .argument="m^2",           .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="volume",  .name="volume",     .argument="m^3",           .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="vlcty",   .name="velocity",   .argument="m*s^-1",        .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="accel",   .name="acceleration", .argument="m*s^-2",      .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
    { .symbol="lumin",   .name="luminance",   .argument="cd*m^-2",      .dimension={.exp_base={0,0,0,0,0,0,0}}, .unit_value=1.0L,  .compost=true },
};


class Luc {

    private:

        // Debug
        static void print_vector(std::vector<std::string> v);
        static void print_vector_dimension(std::vector<Unit_dimension> v);
        static void print_dimension(Unit_dimension v);
        static void print_vector_long_double(std::vector<long double> v);

        // Operators
        static char get_operator_precedence(char op);
        static char get_operator_associativity(char assoc);

        // Char data Type
        static bool char_in_string(char c, const char * list);
        static bool char_is_alpha(char c);
        static bool char_is_num(char c);
        static bool string_is_int(std::string str);
        static bool string_is_decimal(std::string str);

        // Unit
        static bool is_unit(std::string s, const Unit * units, int len, int & found);
        static bool unit_exist(std::string s);
        static int  si_unit_dimension_index(std::string s);
        static bool extract_si_unit_value(std::string unit, long double & value);
        static bool extract_si_unit_dimension(std::string unit, Unit_dimension & extracted_dimension);
        static bool is_compost_unit(std::string s);
        static std::string extract_compost_unit(std::string s);

        // Unit Prefix
        static bool is_unit_prefix(std::string prefix, int & found);
        static bool split_prefix_from_unit(std::string prefix_unit, std::string & prefix, std::string & unit);
        static bool extract_prefix(std::string prefix, Unit_prefix & extracted_prefix);

        // Parse
        static bool parse_unit_arg(std::string raw_unit_argument, std::vector<std::string> & generated_tokens, std::vector<std::string> & s_yard, std::string & feedback);
        static bool check_for_illegal_unit_arg_symbols(std::string raw_unit_argument, std::string & feedback);
        static bool unit_argument_tokenization(std::string unit_argument, std::vector<std::string> & tokens, std::string & feedback);
        static bool check_for_decimal_sintax(std::vector<std::string> & tokens, std::string & feedback);
        static bool check_for_inexistent_units(std::vector<std::string> & tokens, std::string & feedback);
        static bool add_multiplication_operator_when_number_unit_found(std::vector<std::string> & tokens, std::string & feedback);

        // Shunting Yard and Unit Sintax Check
        static bool shunting_yard(std::vector<std::string> & tokens, std::vector<std::string> & s_yard, std::string & feedback);
        static bool check_sintax(std::vector<std::string> s_yard, std::string & feedback);

        // Unit Dimension Creation
        static bool create_unit_dimention(std::vector<std::string> s_yard, Unit_dimension & dimension_created, std::string & feedback);
        static bool dimension_operator(Unit_dimension v1, Unit_dimension v2, std::string op, std::string exp_value, Unit_dimension & le_dimension);
        static bool dimensions_equal(Unit_dimension v1, Unit_dimension v2);
        static bool is_dimension_empty(Unit_dimension dim);

        // Convert argument to Value
        static bool argument_to_value(std::vector<std::string> s_yard, long double & value_result, std::string & feedback);
        static bool convert_number_and_unit_strings_to_decimal(std::string value, long double & decimal_value);
        static bool basic_arithmetics(long double v1, long double v2, std::string op, long double & result);



        // ---------------------------- TEMPERATURE ----------------------------
        // Parse and Sintax
        static bool check_temperature_sintax(std::string value_arg, std::string & temperature_arg, std::string & feedback);


    public:

        // Print kirarasproject logo
        static void print_kirarasproject_logo();

        // Help
        static void luc_help();

        // Unit and temperature conversions
        static bool convert_unit(std::string old_unit_argument, std::string new_unit_argument, std::string & feedback);
        static bool temperature_conversion(std::string value, std::string argument, std::string & feedback);
        static bool censius_fahrenheit_conversor(long double value, long double & result, char order);
        static bool kelvin_fahrenheit_conversor(long double value, long double & result, char order);
        static bool kelvin_celsius_conversor(long double value, long double & result, char order);
};




#endif
