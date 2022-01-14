/*
 * cli_interpreter project
 *
 * Author: Aleksei Tikhomirov <aleksei.tikhomirov@mail.ru>
 *
 */

#include "../registrator.h"

#include <stdexcept>

namespace functions {

class FunctionSub : public IFunction {
  private:
    std::string GetResult(const std::string *args, size_t args_size) const override;
};

std::string FunctionSub::GetResult(const std::string *args, size_t args_size) const {
    if (!args || args_size < 2) {
        throw std::logic_error("Wrong parameters number");
    }
    auto diff = std::stoi(args[0]);
    for (size_t i = 1; i < args_size; ++i) {
        diff -= std::stoi(args[i]);
    }
    return std::to_string(diff);
}

REGISTER_FUNCTION(FunctionSub, "sub")

} // namespace functions
