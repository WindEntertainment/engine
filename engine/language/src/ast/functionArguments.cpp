#include "wind/language/language.hpp"

namespace wind::wdlang {
  inline FunctionArgumentStatement* AST::functionArguments(bool& requireDefaultParam) {
    if (isType(Token::Word)) {
      const auto name = get(-1).value;
      except(Token::Operator, ":");
      except(Token::Word);
      const auto type = get(-1).value;
      Node* value = nullptr;

      if (requireDefaultParam)
        except(Token::Operator, "=");
      else if (isEqual(Token::Operator, "="))
        requireDefaultParam = true;

      if (requireDefaultParam)
        value = expression();

      auto* statement = new FunctionArgumentStatement();
      statement->defaultValue = value;
      statement->name = name;
      statement->type = type;

      return statement;
    }

    shift(1);
    push("Syntax Error: Excepted parameter name. Unexcepted symbol.");
    return nullptr;
  }
} // namespace wind::wdlang