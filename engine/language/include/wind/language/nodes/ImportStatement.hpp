#pragma once
#include "NodeCRTP.hpp"

#include <string>

namespace wind::wdlang {
  struct ImportStatement : public NodeCRTP<ImportStatement> {
    Node* path;
  };
} // namespace wind::wdlang
