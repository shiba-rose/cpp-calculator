#include "utility.h"

// discards input until the next print token.

void clean_up_mess(Token_stream& token_stream)
{
	token_stream.ignore(TokenKind::semicolon);
}


// reports an error by throwing a runtime_error.

[[noreturn]]  void error (const std::string& s)
{
  throw std::runtime_error(s);
}

[[noreturn]] void error (const std::string& s, const std::string& s2)
{
  error (s + s2);
}

[[noreturn]] void error (const std::string& s, int i)
{
  std::ostringstream os;
  os << s << ": " << i;
  error (os.str());
}

std::string help()
{
    return
        "================ CALCULATOR HELP ================\n"
        "\n"
        "GENERAL INFORMATION\n"
        "This calculator supports arithmetic expressions,\n"
        "variables and variable modifiers.\n"
        "\n"
        "COMMANDS\n"
        "help\n"
        "    Displays this help information.\n"
        "\n"
        "quit\n"
        "    Exits the calculator.\n"
        "\n"
        "VARIABLES\n"
        "let name = expression\n"
        "    Creates a new variable or changes its value.\n"
        "\n"
        "let name\n"
        "    Displays the current value of a variable.\n"
        "\n"
        "CONSTANTS\n"
        "let const name = expression\n"
        "    Creates a constant variable.\n"
        "\n"
        "let const name\n"
        "    Makes an existing variable constant.\n"
        "\n"
        "let unconst name\n"
        "    Removes the constant restriction.\n"
        "\n"
        "ARITHMETIC OPERATORS\n"
        "+    Addition\n"
        "-    Subtraction\n"
        "*    Multiplication\n"
        "/    Division\n"
        "\n"
        "EXPRESSIONS\n"
        "Parentheses can change the order of calculations.\n"
        "\n"
        "Examples:\n"
        "    2 + 3 * 4\n"
        "    (2 + 3) * 4\n"
        "    10 / 2 - 3\n"
        "\n"
        "MULTIPLE EXPRESSIONS\n"
        "Use semicolons (;) to separate expressions.\n"
        "\n"
        "Example:\n"
        "    2 + 2; 5 * 3; 10 / 2\n"
        "\n"
        "VARIABLE EXAMPLES\n"
        "    let x = 10\n"
        "    let y = 5\n"
        "    x + y\n"
        "    let x = 20\n"
        "    x * 2\n"
        "\n"
        "CONSTANT EXAMPLES\n"
        "    let const pi = 3.14\n"
        "    pi * 2\n"
        "\n"
        "=================================================\n"
        "\nTRIGONOMETRIC FUNCTIONS:\n"
        "  sin(x)  - sine of x\n"
        "  cos(x)  - cosine of x\n"
        "  tg(x)   - tangent of x\n"
        "\n"
        "ANGLE UNITS:\n"
        "  rad     - radians (default unit)\n"
        "  deg     - degrees (converted to radians)\n"
        "\n"
        "EXAMPLES:\n"
        "  sin(1)       - sine of 1 radian\n"
        "  sin(90deg)   - sine of 90 degrees\n"
        "  cos(180deg)  - cosine of 180 degrees\n"
        "  tg(45deg)    - tangent of 45 degrees\n";
}