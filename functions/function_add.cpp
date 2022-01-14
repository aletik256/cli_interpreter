/*
 * cli_interpreter project
 *
 * Author: Aleksei Tikhomirov <aleksei.tikhomirov@mail.ru>
 *
 */

#include "../registrator.h"

#include <stdexcept>

namespace functions {

class FunctionAdd : public IFunction {
  private:
    std::string GetResult(const std::string *args, size_t args_size) const override;
};

std::string FunctionAdd::GetResult(const std::string *args, size_t args_size) const {
    if (!args || args_size < 2) {
        throw std::logic_error("Wrong parameters number");
    }
    int summ = 0;
    for (size_t i = 0; i < args_size; ++i) {
        summ += std::stoi(args[i]);
    }
    return std::to_string(summ);
}

REGISTER_FUNCTION(FunctionAdd, "add")

} // namespace functions
