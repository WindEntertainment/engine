#pragma once
#include "NodeCRTP.hpp"

#include <string>

namespace wind::wdlang {
  struct FunctionArgumentStatement : public NodeCRTP<FunctionArgumentStatement> {
    std::string name;
    std::string type;
    Node* defaultValue;
  };
} // namespace wind::wdlang
