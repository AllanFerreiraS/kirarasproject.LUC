
# LUC (LUC Unit Converter)

```
 /$$           /$$   /$$     /$$$$$$    
| $$          | $$  | $$    /$$__  $$   
| $$          | $$  | $$   | $$  \__/   
| $$          | $$  | $$   | $$         
| $$          | $$  | $$   | $$         
| $$          | $$  | $$   | $$    $$   
| $$$$$$$$ /$$|  $$$$$$//$$|  $$$$$$//$$
|________/|__/ \______/|__/ \______/|__/
```

LUC is a simple C++ application for unit conversion and others things that I am still thinking about LOL. It supports both physical unit conversions and (in the future) currency conversion.

I build this to learn a little bit C++, so the code is very trashy I'm sorry. Feedback and suggestions are very welcome!

Features
Unit Conversion – Convert between units with support for compound expressions
Currency Conversion – Coming soon
History – Coming soon

## How to run
- Clone the repository from Github
- `cd` to the directory.
- Using a terminal, type `make`.
- To run, type `./luc -h`.

## How LUC works

As one of my best teachers said, do thing by STEP-BY-STEP.

LUC processes unit expressions in several steps:

- Input validation
- Tokenization \[I hate this part\]
- Conversion to postfix notation (Shunting-Yard algorithm)
- Syntax validation
- Dimensional analysis
- Final conversion calculation

## Detailed Logic

#### Unit Argument Filtering

The input is first validated to ensure it contains only allowed characters:

- Letters (Latin alphabet)
- Digits (0–9)
- Symbols: *, /, ^, (, ), -, .

#### Tokenization

The input string is split into tokens representing:

- Unit symbols
- Operators (*, /, ^)
- Numbers (decimals)
- Parentheses

Example:
Input:
kg*m^2/(s^2*A)

Tokens:
["kg", "*", "m", "^", "2", "/", "(", "s", "^", "2", "*", "A", ")"]

#### Composite Unit Expansion

Some units are internally defined in terms of base units.

Example:

N = kg*m/s^2

So:

["N"]

becomes:

["kg", "*", "m", "/", "s", "^", "2"]

#### Unit and Number Validation

All unit symbols must exist in the internal database
Decimal values must be valid numbers

#### Shunting-Yard Algorithm

The expression is converted from infix to postfix notation.

Example:

Infix:

(4 + 18 / (9 - 3))

Postfix:

4 18 9 3 - / +

Unit example:

["kg", "m", "2", "^", "*", "s", "2", "^", "A", "*", "/"]

#### Syntax Validation

Rules include:

Exponents must be numeric (e.g., m^2 is valid, m^s is not)
Multiplication and division can combine units and numbers

#### Dimensional Analysis

LUC extracts the exponent of each base unit to build a dimension vector.

Operations on units are handled through:

Luc::dimension_operator

#### Conversion Calculation

Each unit is reduced to its base representation.

Example:

1 km = 1000 m

So converting:

1000 m to km

Becomes:

1000 / 1000 = 1

## Future Improvements
- Currency API integration
- Arithmetic function
- Number base conversor

## Feedback

If you have suggestions, ideas, or book recommendations, feel free to reach out!

## ©️ License

This work is licensed under [GNU GENERAL PUBLIC LICENSE](https://www.gnu.org/licenses/gpl-3.0.en.html?ref=itsfoss.com).
