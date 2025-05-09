#pragma once
#include "NodeCRTP.hpp"
#include <list>

namespace wind::wdlang {
  struct ForStatement final : public NodeCRTP<ForStatement> {
    Node* prefix;
    Node* midline;
    Node* postfix;
    std::list<Node*> body;
  };
} // namespace wind::wdlang
