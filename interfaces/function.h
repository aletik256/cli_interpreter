/*
 * cli_interpreter project
 *
 * Author: Aleksei Tikhomirov <aleksei.tikhomirov@mail.ru>
 *
 */

#pragma once

#include <string>

namespace functions {

/**
 * @brief The Function object
 */
class IFunction {
  public:
    virtual ~IFunction() = default;

    /**
     * @brief Calculate the result of the function
     *
     * @param args       A pointer to the array of arguments
     * @param args_size  The number of arguments
     *
     * @return The result
     *
     * @throw std::logic_error if `args` is empty or invalid `args_size`
     * @throw std::invalid_argument or std::out_of_range if one of the parameters is not suitable
     */
    virtual std::string GetResult(const std::string *args, size_t args_size) const = 0;
};

} // namespace functions
