#include "wind/language/language.hpp"
#include "wind/language/nodes/Identifier.hpp"

namespace wind::wdlang {
  Node* AST::identifier(const bool& asIdentifier) {
    std::list<std::string> namePath = {};
    do {
      if (!isType(Token::Word))
        break;

      auto name = get(-1).value;
      namePath.emplace_back(name);

    } while (isEqual(Token::Operator, "."));

    if (!namePath.empty()) {
      auto* name = new Identifier();
      name->path = namePath;
      return name;
    }

    if (asIdentifier)
      return nullptr;

    return value();
  }
} // namespace wind::wdlang