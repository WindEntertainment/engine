#pragma once
#include "NodeCRTP.hpp"
#include <list>

namespace wind::wdlang {
  struct IfStatement : public NodeCRTP<IfStatement> {
    Node* condition;
    std::list<Node*> body;
    std::list<Node*> else_body;
  };
} // namespace wind::wdlang
