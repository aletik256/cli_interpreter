/*
 * cli_interpreter project
 *
 * Author: Aleksei Tikhomirov <aleksei.tikhomirov@mail.ru>
 *
 */

#include "../registrator.h"

#include <stdexcept>

namespace functions {

class FunctionMult : public IFunction {
  private:
    std::string GetResult(const std::string *args, size_t args_size) const override;
};

std::string FunctionMult::GetResult(const std::string *args, size_t args_size) const {
    if (!args || args_size < 2) {
        throw std::logic_error("Wrong parameters number");
    }
    auto prod = std::stoi(args[0]);
    for (size_t i = 1; i < args_size; ++i) {
        prod *= std::stoi(args[i]);
    }
    return std::to_string(prod);
}

REGISTER_FUNCTION(FunctionMult, "mult")

} // namespace functions
