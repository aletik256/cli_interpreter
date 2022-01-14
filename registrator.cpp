/*
 * cli_interpreter project
 *
 * Author: Aleksei Tikhomirov <aleksei.tikhomirov@mail.ru>
 *
 */

#include "registrator.h"

#include <map>

namespace registrator {

class FunctionRegistrator::PImpl {
  public:
    bool Register(const std::string &function_name, IFunctionPtr &&function) {
        return functions_map_.emplace(function_name, std::move(function)).second;
    }

    IFunctionPtr GetFunction(const std::string &function_name) const {
        const auto iter = functions_map_.find(function_name);
        return iter != functions_map_.cend() ? iter->second : nullptr;
    }

  private:
    std::map<const std::string, IFunctionPtr> functions_map_;
};

FunctionRegistrator::FunctionRegistrator() : impl_(std::make_unique<PImpl>()) {}

FunctionRegistrator &FunctionRegistrator::GetHandler() {
    static FunctionRegistrator registrator;
    return registrator;
}

bool FunctionRegistrator::Register(const std::string &function_name, IFunctionPtr &&function) {
    return impl_->Register(function_name, std::move(function));
}

FunctionRegistrator::IFunctionPtr FunctionRegistrator::GetFunction(const std::string &function_name) const {
    return impl_->GetFunction(function_name);
}

} // namespace registrator
