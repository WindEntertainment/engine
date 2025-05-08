#include "wind/language/language.hpp"
#include "wind/language/nodes/AssignStatement.hpp"

namespace wind::wdlang {
  Node* AST::assign() {
    Node* name = nullptr;
    if (get(0).type == Token::Word)
      name = identifier(true);

    if (name && isEqual(Token::Operator, "=")) {
      auto* value = expression();

      auto* statement = new AssignStatement();
      statement->name = name;
      statement->value = value;

      return statement;
    }

    return invoke(true, name);
  }
} // namespace wind::wdlang