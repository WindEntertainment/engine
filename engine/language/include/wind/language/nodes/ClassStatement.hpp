#pragma once
#include "ClassMember.hpp"
#include "NodeCRTP.hpp"

#include <list>
#include <string>

namespace wind::wdlang {
  struct ClassStatement : public NodeCRTP<ClassStatement> {
    std::string name;
    std::string parent;
    std::list<std::string> interfaces;
    std::list<ClassMember*> members;
  };
} // namespace wind::wdlang
