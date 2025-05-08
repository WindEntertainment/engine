#pragma once
#include "Node.hpp"

namespace wind::wdlang {
  template <typename Derived>
  struct NodeCRTP : public Node {
    void execute(LangImpl* executor) override;
  };
} // namespace wind::wdlang