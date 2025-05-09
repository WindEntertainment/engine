#include "wind/language/language.hpp"
#include "wind/language/nodes/VariableStatement.hpp"

namespace wind::wdlang {
   Node* AST::variable(const bool& asExpression) {
    if (isEqual(Token::Word, "let")) {
      const auto isMutable = isEqual(Token::Word, "mut");

      except(Token::Word);
      const auto name = get(-1).value;

      except(Token::Operator, ":");

      except(Token::Word);
      const auto type = get(-1).value;

      except(Token::Operator, "=");
      auto* value = expression();

      auto* statement = new VariableStatement();
      statement->isMutable = isMutable;
      statement->type = type;
      statement->name = name;
      statement->value = value;

      return statement;
    }

    return asExpression ? expression() : function();
  }
} // namespace wind::wdlang