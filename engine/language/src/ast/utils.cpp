#include "wind/language/language.hpp"

namespace wind::wdlang {

  AST::AST(Tokenizer::TokenStream& tokenStream) : tokenStream(tokenStream) {
    parse();
  }

  std::queue<AST::Error> AST::getErrors() const { return errorStack; }
  std::vector<Node*> AST::getRoot() const { return ast; }

  void AST::parse() {
    currentScope = Scope::Imports;
    while (get(0).type != Token::T_EOF) {
      ast.emplace_back(imports());
    }
  }

  AST::Token& AST::get(const unsigned int relativePosition) {
    const int pos = currentPosition + relativePosition;

    while (tokens.size() <= pos) {
      auto token = tokenStream.get();
      if (token.type == Token::Unknown)
        errorStack.push(
          Error{
            .position = tokenStream.position,
            .line = tokenStream.line,
            .message = "Unknown symbol",
            .token = token
          }
        );

      tokens.emplace_back(token);
    }

    return tokens[pos];
  }

  AST::Token& AST::shift(unsigned int step) {
    currentPosition += step;
    return get(0);
  }

  AST::Token& AST::consume() {
    shift();
    return get(-1);
  }

  bool AST::isType(Token::TokenType type, int relativePosition) {
    auto res = get(relativePosition).type == type;

    if (res)
      shift();

    return res;
  }

  bool AST::isEqual(
    Token::TokenType type,
    std::string&& value,
    int relativePosition
  ) {
    auto token = get(relativePosition);
    auto res = token.type == type && token.value == value;

    if (res)
      shift();

    return res;
  }

  void AST::except(Token::TokenType type, std::string&& value) {
    if (isEqual(type, std::move(value)))
      return;

    push(fmt::format("Syntax Error: Except '{}'. Unexpected symbol.", value));
  }

  void AST::except(Token::TokenType type) {
    if (isType(type))
      return;

    push("Syntax Error: Unexpected symbol");
  }

  void AST::push(const std::string&& message) {
    errorStack.push(
      Error{
        .position = tokenStream.position,
        .line = tokenStream.line,
        .message = message,
        .token = get(-1)
      }
    );
  }
} // namespace wind::wdlang