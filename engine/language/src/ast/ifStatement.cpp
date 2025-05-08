#include "wind/language/language.hpp"
#include "wind/language/nodes/Node.hpp"
#include "wind/language/nodes/IfStatement.hpp"

namespace wind::wdlang {
  Node* AST::ifStatement() {
    if (isEqual(Token::Word, "if")) {

      auto* condition = expression();
      std::list<Node*> body = {};
      std::list<Node*> else_body = {};

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

      if (isEqual(Token::Word, "else")) {
        except(Token::Operator, "{");
        while (!isEqual(Token::Operator, "}")) {
          if (get(0).type == Token::T_EOF) {
            push("Syntax Error: Unexpected end of file");
            return nullptr;
          }

          auto* part = statement();

          if (part == nullptr)
            continue;

          else_body.emplace_back(part);
        }
      }

      auto* statement = new IfStatement();
      statement->condition = condition;
      statement->body = body;
      statement->else_body = else_body;

      return statement;
    }

    return assign();
  }
}