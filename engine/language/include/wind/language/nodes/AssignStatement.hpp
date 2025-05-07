#pragma once
#include "NodeCRTP.hpp"

#include <string>

namespace wind::wdlang {
  struct AssignStatement : public NodeCRTP<AssignStatement> {
    std::string name;
    Node* value;
  };
} // namespace wind::wdlang
