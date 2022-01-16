#include "interpreter.h"

#include <iostream>

int main() {
    std::string input_str;
    do {
        std::cout << "$ ";
        std::getline(std::cin, input_str);
        std::cout << "> " << interpreter::InterpretExpression(input_str) << "\n";
    } while (input_str != "quit");
    return 0;
}
