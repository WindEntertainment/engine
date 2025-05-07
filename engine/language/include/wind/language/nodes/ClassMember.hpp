#pragma once
#include "NodeCRTP.hpp"

namespace wind::wdlang {
  struct ClassMember : public NodeCRTP<ClassMember> {
    enum AccessModifier {
      Private,
      Public
    };

    AccessModifier access;
    Node* member;
  };
} // namespace wind::wdlang
