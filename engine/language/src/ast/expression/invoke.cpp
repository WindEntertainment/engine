#include "../../../include/wind/language/language.hpp"
#include "../../../include/wind/language/nodes/InvokeExpression.hpp"

namespace wind::wdlang {
  Node* AST::invoke(const bool& asStatement, Node* passedName) {
    Node* name = passedName;
    if (!name && get(0).type == Token::Word)
      name = identifier(true);

    if (name && isEqual(Token::Operator, "(")) {
      std::list<Node*> arguments = {};

      while (!isEqual(Token::Operator, ")")) {
        arguments.push_back(expression());

        if (get(0).value != ")")
          except(Token::Operator, ",");
      }

      auto* expression = new InvokeExpression();
      expression->name = name;
      expression->arguments = arguments;

      return expression;
    }

    if (!asStatement)
      return name ? name : identifier(false);

    shift();
    push("Syntax error: Unexpected symbol");
    return nullptr;
  }
} // namespace wind::wdlang