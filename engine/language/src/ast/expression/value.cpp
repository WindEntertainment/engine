#include "wind/language/language.hpp"
#include "wind/language/nodes/Value.hpp"

namespace wind::wdlang {
  Node* AST::value() {
    auto* value = new Value();
    value->value = get(0).value;

    if (isType(Token::Number)) {
      value->type = Value::Number;
      return value;
    }

    if (isType(Token::Char)) {
      value->type = Value::Char;
      return value;
    }

    if (isType(Token::String)) {
      value->type = Value::String;
      return value;
    }

    shift(1);
    push("Syntax Error: Unknown value type");
    return nullptr;
  }
} // namespace wind::wdlang