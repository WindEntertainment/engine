#pragma once
#include "wind/language/lang_impl.hpp"
#include "wind/language/tokenizer.hpp"

#include <queue>

namespace wind::wdlang {
  class AST {
    using Token = Tokenizer::Token;
  public:
    struct Error {
      int position;
      int line;
      std::string message;
      Tokenizer::Token token;
    };

    AST(Tokenizer::TokenStream& tokenStream);

    [[nodiscard]] std::queue<Error> getErrors() const;
    [[nodiscard]] std::vector<Node*> getRoot() const;

  private:
    std::queue<Error> errorStack;

    std::vector<Node*> ast;
    std::vector<Token> tokens;
    Tokenizer::TokenStream& tokenStream;

    int currentPosition = 0;

    enum class Scope { Global, InNamespace, InClass, InFunction };

    Scope currentScope;

    //===========================================//
    // Utils

    Token& get(unsigned int relativePosition = 0);
    Token& shift(unsigned int step = 1);
    Token& consume();
    bool isType(Token::TokenType type, int relativePosition = 0);
    bool isEqual(
      Token::TokenType type,
      std::string&& value,
      int relativePosition = 0
    );
    void except(Token::TokenType type, std::string&& value);
    void except(Token::TokenType type);
    void push(const std::string&& message);

    //===========================================//
    // Parsing

    void parse();
    Node* statement();
    Node* classes();
    Node* variable();
    Node* function();
    Node* returnStatements();
    FunctionArgumentStatement* functionArguments(bool& requireDefaultParam);
    Node* assign();
    Node* expression();
    Node* binaryPriority0();
    Node* binaryPriority1();
    Node* binaryPriority2();
    Node* binaryPriority3();
    Node* parentheses();
    Node* unary();
    Node* identifier();
    Node* value();
  };
} // namespace wind::wdlang