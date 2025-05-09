#include "wind/language/language.hpp"
#include "wind/language/nodes/ClassStatement.hpp"

namespace wind::wdlang {
  Node* AST::classes() {
    if (isEqual(Token::Word, "class")) {
      except(Token::Word);
      auto name = get(-1).value;

      std::string parent;
      if (isEqual(Token::Word, "extends")) {
        except(Token::Word);
        parent = get(-1).value;
      }

      std::list<std::string> interfaces = {};
      if (isEqual(Token::Word, "implements")) {
        if (get().type != Token::Word) {
          push(
            "Syntax Error: Excepted interface to implements. Unexpected symbol. "
          );
          return nullptr;
        }

        do {
          interfaces.emplace_back(get().value);

          shift();
          if (!isEqual(Token::Operator, ","))
            break;
        } while (get().type == Token::Word);
      }

      currentScope = Scope::InClass;

      std::list<ClassMember*> members = {};
      ClassMember::AccessModifier currentAccess = ClassMember::Private;

      except(Token::Operator, "{");
      while (!isEqual(Token::Operator, "}")) {
        if (isEqual(Token::Word, "public")) {
          except(Token::Operator, ":");
          currentAccess = ClassMember::Public;
          continue;
        }

        if (isEqual(Token::Word, "private")) {
          except(Token::Operator, ":");
          currentAccess = ClassMember::Private;
          continue;
        }

        auto* member = new ClassMember();
        member->access = currentAccess;
        member->member = statement();

        if (member->member == nullptr)
          continue;

        members.emplace_back(member);
      }

      currentScope = Scope::Global;

      auto* statement = new ClassStatement();
      statement->name = name;
      statement->parent = parent;
      statement->interfaces = interfaces;
      statement->members = members;

      return statement;
    }

    if (currentScope == Scope::InClass || currentScope == Scope::InFunction) {
      return variable(false);
    }

    shift();
    push(
      "Syntax Error: In global scope may be only class definition statements"
    );
    return nullptr;
  }
} // namespace wind::wdlang