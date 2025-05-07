#pragma once
#include "FunctionArgumentStatement.hpp"
#include "NodeCRTP.hpp"

#include <list>
#include <string>

namespace wind::wdlang {
  struct FunctionStatement : public NodeCRTP<FunctionStatement> {
    std::string type;
    std::string name;
    std::list<FunctionArgumentStatement*> args;
    std::list<Node*> body;
  };
} // namespace wind::wdlang
