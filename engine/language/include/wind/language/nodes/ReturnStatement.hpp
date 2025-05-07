#pragma once
#include "NodeCRTP.hpp"

namespace wind::wdlang {
  struct ReturnStatement : public NodeCRTP<ReturnStatement> {
    Node* value;
  };
} // namespace wind::wdlang
