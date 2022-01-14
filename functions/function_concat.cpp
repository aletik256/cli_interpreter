/*
 * cli_interpreter project
 *
 * Author: Aleksei Tikhomirov <aleksei.tikhomirov@mail.ru>
 *
 */

#include "../registrator.h"

#include <stdexcept>

namespace functions {

class FunctionConcat : public IFunction {
  private:
    std::string GetResult(const std::string *args, size_t args_size) const override;
};

std::string FunctionConcat::GetResult(const std::string *args, size_t args_size) const {
    if (!args || args_size < 2) {
        throw std::logic_error("Wrong parameters number");
    }
    std::string result;
    for (size_t i = 0; i < args_size; ++i) {
        result += args[i];
    }
    return result;
}

REGISTER_FUNCTION(FunctionConcat, "concat")

} // namespace functions
