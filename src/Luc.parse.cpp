#include "Luc.h"
#include <iostream>

// Const ============================
const char * UNIT_INPUT_LEGAL_SYMBOLS           = "-.*/^()";
const char * UNIT_SINTAX_LEGAL_SYMBOLS          = "/*^";
const char * UNIT_DONE_FLAG                     = "@";
const char * ARITHMETIC_LEGAL_OPERATOR_SYMBOLS  = "+-*/^";

// Operators for Shuting Yard Process...
Operator oprts[] = {
    {.symbol = '^', .precedence = 4, .associativity = 'r'},
    {.symbol = '*', .precedence = 3, .associativity = 'l'},
    {.symbol = '/', .precedence = 3, .associativity = 'l'},
    {.symbol = '+', .precedence = 2, .associativity = 'l'},
    {.symbol = '-', .precedence = 2, .associativity = 'l'}
};


/*
    Function to treat the parsing of the unit_argument and generating the tokens and shunting yard tokens to perform calculation later.
    @param <raw_unit_argument> The raw unit argument
    @param <generated_tokens> The tokens will be stored here
    @param <s_yard> The tokens in shunting yard order will be stored here
    @param <feedback>
*/
bool Luc::parse_unit_arg(std::string raw_unit_argument, std::vector<std::string> & generated_tokens, std::vector<std::string> & s_yard, std::string & feedback) {

    // Check for illegal symbols                                            [ 100% DONE ]
    if (! check_for_illegal_unit_arg_symbols(raw_unit_argument, feedback) )
        return false;

    // Generate Tokens                                                      [ 100% DONE ]
    if (! unit_argument_tokenization(raw_unit_argument, generated_tokens, feedback) )
        return false;

    // Check if decimal numbers are formated correctly                      [ 100% DONE ]
    if (! check_for_decimal_sintax(generated_tokens, feedback) )
        return false;
    
    // Check for inexistent units                                           [ 100% DONE ]
    if (! check_for_inexistent_units(generated_tokens, feedback) )
        return false;
    
    // If [ <decimal>, <string> ], then [ <decimal>, *, <string>]           [ 100% DONE ]
    if (! add_multiplication_operator_when_number_unit_found(generated_tokens, feedback) )
        return false;

    if (verbose) {

        std::cout << LUC_MESSAGE_SUCCESS + "Token generated: \n";
        print_vector(generated_tokens);
    }

    // Generate Posfix Sintax                                               [ 100% DONE ]
    if (! shunting_yard(generated_tokens, s_yard, feedback) )
        return false;
    
    if (verbose){

        std::cout << LUC_MESSAGE_SUCCESS + "Shunting Yard Token generated: \n";
        print_vector(s_yard);
    }

    // Check unit sintax                                                    [ ??? ]
    if (! check_sintax(s_yard, feedback) )
        return false;
    
    return true;
}

/*
    Function to check if there are illegal symbols for unit conversions
    Illegal symbols are those who are not in [ 'Latin Alphabet', 'integers', '/', '*', '^', '-', '(', ')' and '.' ]
    @param <raw_unit_argument>
*/
bool Luc::check_for_illegal_unit_arg_symbols(std::string raw_unit_argument, std::string & feedback) {

    for (int i = 0; i < raw_unit_argument.size(); i++) {

        // Is Alpha?
        if ( char_is_alpha(raw_unit_argument[i]) )
            continue;

        // Is Num?
        if ( char_is_num(raw_unit_argument[i]) )
            continue;

        // Is a Unit Conversion legal symbol?
        if ( char_in_string(raw_unit_argument[i], UNIT_INPUT_LEGAL_SYMBOLS) )
            continue;

        feedback = LUC_MESSAGE_ERROR + "The char \'" + raw_unit_argument[i] + "\' is illegal for unit conversion.\n";
        return false;
    }

    return true;
}

/*
    The most confusing function of human history
    Function that take a string of chars and tokenizate them.
    Also a function that calls itself because of compost units.
    Also a function that split prefixes from units.
    I hope it wont break, because I wont fix this shit later
    
    @param <unit_argument> A string of unit(s). Like "m", "km/h".
    @param <tokens> A list of strings.
    @param <feedback>
*/
bool Luc::unit_argument_tokenization(std::string unit_argument, std::vector<std::string> & tokens, std::string & feedback) {

    tokens.clear();
    const char * OPERATION_SYMBOLS = "+-*/^()";

    std::string new_string = "";
    std::string str_prefix, str_unit;
    str_prefix = str_unit = "";
    std::vector<std::string> temp_tokens;

    // Check if there are negative numbers
    enum negative_number {
        NO,
        POSSIBLE,
        YES 
    };

    negative_number neg_number = NO;

    // Control where char is in current string
    bool in_word, in_number, in_symbol, let_split, unit_format;
    in_word   = false;
    in_number = false;
    in_symbol = false;
    let_split = false;

    unit_format = false;

    // Start index to split string
    int start_index = 0;
    int return_index = 0;

    int unit_argument_size = unit_argument.size();

    // Check unit argument's length
    if (unit_argument_size <= 0) {
        feedback = LUC_MESSAGE_ERROR + "No unit argument especified.\n";
        return false;
    }

    if (char_is_num(unit_argument[0])) in_number = true;
    else if (char_is_alpha(unit_argument[0])) in_word = true;
    else if (char_in_string(unit_argument[0], OPERATION_SYMBOLS)) in_symbol = true; 

    for (int i = 0; i < unit_argument_size; i++) {
        
        if ( ( char_is_num(unit_argument[i]) || unit_argument[i] == '.' ) && (in_word || in_symbol)) {

            in_word     =   false;
            in_number   =   true;
            in_symbol   =   false;

            if (neg_number == POSSIBLE) {
                neg_number = YES;
                continue;
            }

            let_split   =   true;
        }
        else if ( char_is_alpha(unit_argument[i]) && (in_number || in_symbol) ) {

            if (neg_number == POSSIBLE)
                neg_number = NO;

            let_split   =   true;
            in_word     =   true;
            in_number   =   false;
            in_symbol   =   false;
        }
        else if ( char_in_string(unit_argument[i], OPERATION_SYMBOLS) ) {

            if (unit_argument[i] == '-') {
                neg_number = POSSIBLE;
                return_index = i;
            }

            // If first char is a symbol, do not split imediately
            if (i > 0)
                let_split   =   true;

            in_word     =   false;
            in_number   =   false;
            in_symbol   =   true;
        }

        // If conditions are satisfied, it will split the string
        // Isso daqui está uma bagunça que só por Deus.... Aaaaaaaaaaaaaah
        if (let_split) {

            if (neg_number == YES) {
                start_index = return_index;
                neg_number = NO;
            }

            new_string = unit_argument.substr(start_index, i - start_index);

            if ( split_prefix_from_unit(new_string, str_prefix, str_unit) )
                unit_format = true;
            else
                unit_format = false;

            if ( unit_format && is_compost_unit(str_unit) ) {

                if (! unit_argument_tokenization(extract_compost_unit(str_unit), temp_tokens, feedback))
                    return false;

                if (str_prefix != "") {
                    
                    tokens.push_back("(");
                    tokens.push_back(str_prefix + "_");
                    tokens.push_back("*");
                }

                tokens.push_back("(");
                for (int j = 0; j < temp_tokens.size(); j++)
                    tokens.push_back(temp_tokens[j]);
                tokens.push_back(")");

                if (str_prefix != "")
                    tokens.push_back(")");
                temp_tokens.clear();
            }
            else {

                if ( unit_format && (str_prefix != "") ) {

                    tokens.push_back("(");
                    tokens.push_back(str_prefix + "_");
                    tokens.push_back("*");
                    tokens.push_back(str_unit);
                    tokens.push_back(")");
                } 
                else
                    tokens.push_back(new_string);
            }

            new_string = "";
            start_index = i;
            let_split = false;      
        }
    }

    // Split the rest of the string.
    // Isso daqui está uma bagunça que só por Deus.... Aaaaaaaaaaaaaah
    new_string = unit_argument.substr(start_index, unit_argument_size - start_index);

    if ( split_prefix_from_unit(new_string, str_prefix, str_unit) )
        unit_format = true;
    else
        unit_format = false;

    if ( unit_format && is_compost_unit(str_unit) ) {

        split_prefix_from_unit(new_string, str_prefix, str_unit);
        
        if (! unit_argument_tokenization(extract_compost_unit(str_unit), temp_tokens, feedback))
            return false;
        
        if (str_prefix != "") {
            
            tokens.push_back("(");
            tokens.push_back(str_prefix + "_");
            tokens.push_back("*");
        }

        tokens.push_back("(");
        for (int j = 0; j < temp_tokens.size(); j++)
            tokens.push_back(temp_tokens[j]);
        tokens.push_back(")");

        if (str_prefix != "")
            tokens.push_back(")");
        temp_tokens.clear();
    }
    else {
        if ( unit_format && (str_prefix != "") ) {

            tokens.push_back("(");
            tokens.push_back(str_prefix + "_");
            tokens.push_back("*");
            tokens.push_back(str_unit);
            tokens.push_back(")");
        } 
        else
            tokens.push_back(new_string);
    }

    return true;
}

/*
    Function to search for decimals numbers with bad sintax
    @param <tokens> A list of strings.
    @param <feedback>
*/
bool Luc::check_for_decimal_sintax(std::vector<std::string> & tokens, std::string & feedback) {

    int tokens_size = tokens.size();
    int token_size = 0;
    bool numeric = false;

    for (int i = 0; i < tokens_size; i++) {

        token_size = tokens[i].size();
        for (int j = 0; j < token_size; j++)
            if ( numeric = char_is_num(tokens[i][j]) ) break;

        // '.' without any numbers. The char '.' is considered as a number to the function that creates the tokens,
        //  so it will be apart from any char that is not betweem 0-9
        if (tokens[i][0] == '.') {

            feedback = LUC_MESSAGE_ERROR + "The char \'.\' should only be used between numerical chars.\n";
            return false;
        }


        if ( numeric && (! string_is_decimal(tokens[i])) ) {

            feedback = LUC_MESSAGE_ERROR + "The sintax for the decimal value \'" + tokens[i] + "\' is invalid.\n";
            return false;
        }
    }

    return true;
}

/*
    Function to search for inexistent unit symbols in token list
    @param <tokens> A list of strings.
    @param <feedback>
*/
bool Luc::check_for_inexistent_units(std::vector<std::string> & tokens, std::string & feedback) {

    int tokens_size = tokens.size();
    int tokens_content_size = 0;
    int ignore = -1;

    for (int i = 0; i < tokens_size; i++) {
        
        // Ignore not char units
        if (! char_is_alpha(tokens[i][0]) )
            continue;

        tokens_content_size = tokens[i].size();

        // Ignore prefixes [I am marking all prefixes with '_' at the end of the string]
        if ( (is_unit_prefix( tokens[i].substr(0, tokens_content_size - 1), ignore)) && (tokens[i][tokens_content_size - 1] == '_') ) {
            continue;
        }
        if (! unit_exist(tokens[i]) ) {
            feedback = LUC_MESSAGE_ERROR + "The unit symbol \'" + tokens[i] + "\' is unkown.\n";
            return false;
        }
    }

    return true;
}

/*
    Function that adds the multiplication operator '*', when [<decimal>, <unit string>] found.
    Example: 20km will become 20 * km. And 2(N) will become 2 * (N).
    @param <tokens> A list of strings.
    @param <feedback>
*/
bool Luc::add_multiplication_operator_when_number_unit_found(std::vector<std::string> & tokens, std::string & feedback) {


    int token_size = tokens.size();
    std::vector<std::string> temp_tokens;
    int index = 0;
    bool start_process = false;


    if (token_size <= 0) {
        feedback = LUC_MESSAGE_ERROR + "Unable to add multiplication unit operator when number unit found. Token is empty.\n";
        return false;
    }

    while (index < token_size) {

        if ( string_is_decimal(tokens[index]) && start_process == false) {
            start_process = true;
        }
        else if ( (char_is_alpha(tokens[index][0]) || tokens[index] == "(") && start_process) {
            temp_tokens.push_back("*");
            start_process = false;
        }
        else
            start_process = false;

        temp_tokens.push_back(tokens[index]);
        index++;
    }

    tokens.clear();
    tokens = temp_tokens;
    temp_tokens.clear();

    return true;
}


// Shuting Yard Part...


/*
    Function that returns the precedence value of an operator
    @param <op>
*/
char Luc::get_operator_precedence(char op) {

    for (int i = 0; i < (sizeof(oprts) / sizeof(oprts[0])); i++)
        if (op == oprts[i].symbol)
            return oprts[i].precedence;

    return 0;
}

/*
    Function that returns the associativity value of an operator
    @param <assoc>
*/
char Luc::get_operator_associativity(char assoc) {

    for (int i = 0; i < (sizeof(oprts) / sizeof(oprts[0])); i++)
        if (assoc == oprts[i].symbol)
            return oprts[i].associativity;

    return 0;
}

/*
    Funtion that put in practice the Shunting-Yard Algorithm
    @param <tokens> A list of strings.
    @param <s_yard> An empty string list
    @param <feedback> Feedback
*/
bool Luc::shunting_yard(std::vector<std::string> & tokens, std::vector<std::string> & s_yard, std::string & feedback) {

    s_yard.clear();

    std::vector<std::string> stk;
    int tokens_size = tokens.size();
    char first_index = 0;

    try {

        for (int i = 0; i < tokens_size; i++) {

            if ( string_is_decimal(tokens[i]) ) {

                s_yard.push_back(tokens[i]);
            }
            else if ( char_is_alpha(tokens[i][first_index]) ) {
                
                s_yard.push_back(tokens[i]);
            }
            else if ( char_in_string(tokens[i][first_index], ARITHMETIC_LEGAL_OPERATOR_SYMBOLS) ){

                while (
                    ( (!stk.empty()) && (stk[stk.size() - 1] != "(") ) &&
                    ( (get_operator_precedence(stk[stk.size()-1][first_index]) > get_operator_precedence(tokens[i][first_index]) || 
                    (get_operator_precedence(stk[stk.size()-1][first_index]) == get_operator_precedence(tokens[i][first_index]) && get_operator_associativity(tokens[i][first_index]) == 'l')) )
                ) {

                    s_yard.push_back( stk[stk.size() - 1] );
                    stk.pop_back();
                }

                stk.push_back(tokens[i]);
            }
            else if (tokens[i] == "(") {

                stk.push_back("(");
            }
            else if (tokens[i] == ")") {

                while ((! stk.empty()) && stk[stk.size() - 1] != "(") {
                    s_yard.push_back( stk[stk.size() - 1] );
                    stk.pop_back();
                }

                if (stk.empty()) {
                    feedback = LUC_MESSAGE_ERROR + "Parenthesis match error in Unit Argument.\n";
                    return false;
                }
                if ( stk[stk.size() - 1] == "(" ) stk.pop_back();
            }

        }
    }
    catch(const std::exception & e)
    {
        feedback = LUC_MESSAGE_ERROR + "Some unexpected error happened while transforming token in Posfix notation.\n"; 
        return false;
    }

    while (! stk.empty()) {

        if (stk[ stk.size() - 1 ] == "(") {
            feedback = LUC_MESSAGE_ERROR + "Parenthesis match error in Unit Argument.\n"; 
            return false;
        }

        s_yard.push_back(stk[ stk.size() - 1 ]);
        stk.pop_back();
    }

    return true;

}

/*
    Function that checks if unit sintax is correct.
    Rule 1: Only allow numeric exponentiation bases
    Rule 2: With exception of exponentiation, if 'a*b' or 'a/b', then 'a' and 'b' should be units or decimals.
    @param <s_yard> string list (shunting yard)
    @param <feedback> feedback
*/
bool Luc::check_sintax(std::vector<std::string> s_yard, std::string & feedback) {

    if ( s_yard.empty() ) {
        feedback = LUC_MESSAGE_ERROR + "Shunting Yard List is empty.\n";
        return false;
    }

    std::string PROCCESS_DONE_FLAG = "X";

    int index, index_return;
    index = index_return = 0;

    std::string a,b, op;
    a = b = op = "";

    if (verbose)
        std::cout << LUC_MESSAGE_SUCCESS + "Checking Sintax: [X] Represents the working done.\n";

    while ( index < s_yard.size() ) {

        if (verbose) {

            std::cout << "\t>> ";
            for (int i = 0; i < s_yard.size(); i++)
                std::cout << s_yard[i] + " ";
            std::cout << std::endl;
        }

        if (s_yard[index] == "-") {
            feedback = LUC_MESSAGE_ERROR + "The minus sign \'-\' is only allowed to use with numbers. Example: \'-1\' is ALLOWED, but \'-m\' is NOT ALLOWED.\n";
            return false;
        }

        // Se achar o '-', é bom verificar se é um char ou uma string para decimal.
        if ( char_in_string(s_yard[index][0], UNIT_SINTAX_LEGAL_SYMBOLS)  ) {

            if ( (index - 2) < 0 ) {
                feedback = LUC_MESSAGE_ERROR + "Operand \'" + s_yard[index]+ "\' with incomplete arguments.\n";
                return false;
            }

            index_return = index - 2;

            a = s_yard[index - 2];
            b = s_yard[index - 1];
            op = s_yard[index];

            // If 'op' is exponent, then 'a' should be an unit and b should be an integer.
            if ( ((! char_is_alpha(a[0])) || (! string_is_int(b))) && op == "^" ) {
                feedback = LUC_MESSAGE_ERROR + "Sintax not allowed. If \'a^b\', then \'a\' should be an unit, and \'b\' an integer.\n";
                return false;
            }
            
            // If 'op' is not an exponent, then 'a' should be an unit OR decimal and 'b' should be an unit.
            // std::cout << "a = " + a + ",\tb = " + b + ",\t" + op;
            if ( ( (! ((char_is_alpha(a[0])) || (string_is_decimal(a))) ) || (! ((char_is_alpha(b[0])) || (string_is_decimal(b))) ) ) && op != "^" ) {
                feedback = LUC_MESSAGE_ERROR + "Sintax not allowed. If \'a*b\' or \'a/b\', then \'a\' and \'b\' should be an unit or a decimal value.\n";
                return false;
            }

            s_yard.erase(s_yard.begin() + index);
            s_yard.erase(s_yard.begin() + index - 1);
            index = index_return;
            s_yard[index] = PROCCESS_DONE_FLAG;
        }

        index++;
    }

    if (verbose) {
        std::cout << "\t>> ";
        for (int i = 0; i < s_yard.size(); i++)
            std::cout << s_yard[i] + " ";
        std::cout << "\n\n";
    }

    if ( (s_yard.size() > 1) || (s_yard.size() == 1 && string_is_decimal(s_yard[0])) ) {
        feedback = LUC_MESSAGE_ERROR + "Sintax argument is incorrect. Please review your string.\n";
        return false;
    }

    return true;
}