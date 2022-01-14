/*
 * cli_interpreter project
 *
 * Author: Aleksei Tikhomirov <aleksei.tikhomirov@mail.ru>
 *
 */

#pragma once

#include "interfaces/function.h"

#include <memory>

namespace registrator {

class FunctionRegistrator {
  public:
    using IFunctionPtr = std::shared_ptr<const functions::IFunction>;

    static FunctionRegistrator &GetHandler();

    bool Register(const std::string &function_name, IFunctionPtr &&function);
    IFunctionPtr GetFunction(const std::string &function_name) const;

  private:
    FunctionRegistrator();

  private:
    class PImpl;
    std::unique_ptr<PImpl> impl_;
};

template <class Func> class FunctionFactory {
  public:
    FunctionFactory(const std::string &function_name) {
        const auto function = std::make_shared<const Func>();
        FunctionRegistrator::GetHandler().Register(function_name, std::move(function));
    }
};

} // namespace registrator

#define REGISTER_FUNCTION(function_class_name, function_name)                                                          \
    static registrator::FunctionFactory<function_class_name> function_class_name##_factory(function_name);
