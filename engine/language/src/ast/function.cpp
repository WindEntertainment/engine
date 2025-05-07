#include "wind/language/language.hpp"

namespace wind::wdlang {
  inline Node* AST::function() {
    if (get(0).type == Token::Word && get(1).type == Token::Word &&
        get(2).type == Token::Operator && get(2).value == "(") {

      const auto type = consume().value;
      const auto name = consume().value;

      std::list<FunctionArgumentStatement*> args = {};
      bool require = false;
      bool first = true;

      except(Token::Operator, "(");
      while (!isEqual(Token::Operator, ")")) {
        if (get(0).type == Token::T_EOF) {
          push("Syntax Error: Unexpected end of file");
          return nullptr;
        }

        if (!first)
          except(Token::Operator, ",");
        first = false;

        auto* arg = functionArguments(require);

        if (!arg)
          return nullptr;

        args.emplace_back(arg);
      }

      std::list<Node*> body = {};

      if (isEqual(Token::Operator, "->")) {
        auto* returnStatement = new ReturnStatement();
        returnStatement->value = expression();
        body.emplace_back(returnStatement);
      } else {
        except(Token::Operator, "{");
        while (!isEqual(Token::Operator, "}")) {
          if (get(0).type == Token::T_EOF) {
            push("Syntax Error: Unexcepted end of file");
            return nullptr;
          }

          currentScope = Scope::InFunction;
          auto* part = statement();

          if (part == nullptr)
            continue;

          body.emplace_back(part);
        }

        currentScope = Scope::InClass;
      }

      auto* statement = new FunctionStatement();
      statement->name = name;
      statement->type = type;
      statement->args = args;
      statement->body = body;

      return statement;
        }

    if (currentScope == Scope::InFunction) {
      return returnStatements();
    }

    shift();
    push(
      "Syntax Error: In class scope may be only member definition "
      "statements"
    );
    return nullptr;
  }

} // namespace wind::wdlang