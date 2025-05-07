#pragma once
#include "NodeCRTP.hpp"

#include <string>

namespace wind::wdlang {
  struct VariableStatement : public NodeCRTP<VariableStatement> {
    bool isMutable;
    std::string type;
    std::string name;
    Node* value;
  };
} // namespace wind::wdlang
