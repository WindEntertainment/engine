#include "wind/language/language.hpp"
#include "wind/language/nodes/ForStatement.hpp"

namespace wind::wdlang {
  Node* AST::forStatement() {
    if (isEqual(Token::Word, "for")) {
      except(Token::Operator, "(");
      auto* prefix = variable(true);
      except(Token::Operator, ";");
      auto* midline = variable(true);
      except(Token::Operator, ";");
      auto* postfix = variable(true);
      except(Token::Operator, ")");

      std::list<Node*> body = {};

      except(Token::Operator, "{");
      while (!isEqual(Token::Operator, "}")) {
        if (get(0).type == Token::T_EOF) {
          push("Syntax Error: Unexpected end of file");
          return nullptr;
        }

        auto* part = statement();

        if (part == nullptr)
          continue;

        body.emplace_back(part);
      }

      auto* statement = new ForStatement();
      statement->prefix = prefix;
      statement->midline = midline;
      statement->postfix = postfix;
      statement->body = body;

      return statement;
    }

    return assign(false);
  }
} // namespace wind::wdlang