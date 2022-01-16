/*
 * cli_interpreter project
 *
 * Author: Aleksei Tikhomirov <aleksei.tikhomirov@mail.ru>
 *
 */

#include "interpreter.h"
#include "registrator.h"

#include <regex>
#include <string>
#include <vector>

namespace interpreter {

constexpr char SYNTAX_ERROR_STR[] = "Syntax error!";
constexpr auto INVALID_INDEX = static_cast<size_t>(-1);

bool GetFunctionOrArgument(const char *input, std::string *func_arg_str) {
    static const std::regex func_arg_rx(R"((^-?[0-9a-zA-Z]+)|("[^"]+?"))");
    std::match_results<const char *> match;
    if (!std::regex_search(input, match, func_arg_rx) || match.position() != 0) {
        return false;
    }
    *func_arg_str = std::string(input, match.length());
    return true;
}

void RemoveMarks(std::string *str) {
    if ((*str)[0] == '"') {
        str->erase(0, 1);
    }
    const auto las_symbol = str->length() - 1;
    if ((*str)[las_symbol] == '"') {
        str->erase(las_symbol, 1);
    }
}

bool GetFunctionResult(const std::string *func_args, size_t func_args_size, std::string *result) {
    const auto function = registrator::FunctionRegistrator::GetHandler().GetFunction(func_args[0]);
    if (function) {
        try {
            *result = function->GetResult(func_args + 1, func_args_size - 1);
        } catch (const std::logic_error &) {
            return false;
        }
        return true;
    }
    return false;
}

size_t FindBufferIndex(const std::vector<std::string> &buffer, const std::string &value) {
    for (size_t i = buffer.size() - 1; i >= 0; i--) {
        if (buffer[i] == value) {
            return i;
        }
    }
    return INVALID_INDEX;
}

bool UpdateBufferTop(std::vector<std::string> &buffer) {
    const auto br_index = FindBufferIndex(buffer, "(");
    if (br_index == INVALID_INDEX) {
        return false;
    }
    const auto func_index = br_index + 1;
    std::string func_result;
    if (GetFunctionResult(buffer.data() + func_index, buffer.size() - func_index, &func_result)) {
        buffer[br_index] = std::move(func_result);
        buffer.erase(buffer.begin() + func_index, buffer.end());
        return true;
    }
    return false;
}

std::string InterpretExpression(const std::string &expression) {
    std::vector<std::string> buffer;
    size_t i = 0;
    while (i < expression.length()) {
        std::string func_arg_str;
        if (GetFunctionOrArgument(expression.c_str() + i, &func_arg_str)) {
            i += func_arg_str.length();
            RemoveMarks(&func_arg_str);
            buffer.push_back(std::move(func_arg_str));
        } else if (expression[i] == ' ') {
            i++;
        } else if (expression[i] == '(') {
            i++;
            buffer.push_back("(");
        } else if (expression[i] == ')') {
            i++;
            if (!UpdateBufferTop(buffer)) {
                return SYNTAX_ERROR_STR;
            }
        } else {
            return SYNTAX_ERROR_STR;
        }
    }
    if (buffer.size() > 1) {
        std::string func_result;
        if (GetFunctionResult(buffer.data(), buffer.size(), &func_result)) {
            return func_result;
        }
        return SYNTAX_ERROR_STR;
    }
    return buffer.size() == 1 ? buffer.back() : SYNTAX_ERROR_STR;
}

} // namespace interpreter
