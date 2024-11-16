#include "wind/language/tokenizer.hpp"
#include <queue>

namespace wind {
  class LangImpl;

	namespace wdlang {
    
		//class WdExecutor;

		struct Expression {
      virtual void execute(LangImpl*) = 0;
    };

		/*class WdExecutor {
		public:
      WdExecutor(LangImpl* impl) : impl(impl) {}

      template <typename T>
        requires(std::derived_from<T, Expression>)
      void compile(T* t) {
        impl->compileImpl(t);
      }
		private:
			LangImpl* impl;
		};*/

		template <typename Derived> 
		struct ExpressionCRTP : public Expression {
			void execute(LangImpl* executor) override;
		};

		struct Value : public ExpressionCRTP<Value> {
			enum ValueType {
				Number,
				Char,
				String,
			};

			ValueType type;
      std::string value;
		};

    struct Identifier : public ExpressionCRTP<Identifier> {
      std::string name;

			Identifier(std::string&& name) : name(name) {}
		};
    
		struct BinaryOperation : public ExpressionCRTP<BinaryOperation> {
			enum OperationType {
				Add, 
				Sub, 
				Mul,
				Div,
				Equal,
				NotEqual,
				Greater,
				Less,
        GreaterOrEqual,
				LessOrEqual,
				And,
				Or
      };

			OperationType type;
      Expression* lhs;
      Expression* rhs;
		};

    struct UnaryOperation : public ExpressionCRTP<UnaryOperation> {
			enum OperationType {
				NEGATE
			};

			OperationType type;
      Expression* operand;
		};
	
		class AST {
			using Token = Tokenizer::Token;
    public:
			struct Error {
        int position;
        int line;
        std::string message;
				Tokenizer::Token token;
			};

			AST(Tokenizer::TokenStream& tokenStream): tokenStream(tokenStream) {
          parse();
			};

			std::queue<Error> getErrors() const {
        return errorStack;
			}

			std::vector<Expression*> getRoot() const {
				return ast;
			}

    private:
			std::queue<Error> errorStack;
			
			std::vector<Expression*> ast;
			std::vector<Token> tokens;
			Tokenizer::TokenStream& tokenStream;

			int cPos = 0;

			//===========================================//
			// Utils

			Token& get(unsigned int relativePosition = 0) {
        int pos = cPos + relativePosition;

				while (pos >= tokens.size()) {
          auto token = tokenStream.get();
          if (token.type == Token::Unknown)
						errorStack.push(Error{
						 	.position = tokenStream.position,
							.line = tokenStream.line, 
							.message = "Unknown symbol",
							.token = token
						});

					tokens.emplace_back(token);
				}

				return tokens[pos];
			}

			Token& shift(unsigned int step = 1) {
				cPos += step;
        return get(0);
			}

			Token& consume() { 
        shift();
				return get(-1);
			}

			bool isType(Token::TokenType type, int relativePosition = 0) { 
				auto res = get(relativePosition).type == type;
				
				if (res)
					shift();

				return res;
			}

			bool isEqual(Token::TokenType type, std::string&& value, int relativePosition = 0) {
				auto token = get(relativePosition);
				auto res = token.type == type && token.value == value;

				if (res)
					shift();

				return res;
			}

			void push(const std::string&& message) {
        errorStack.push(Error{
          .position = tokenStream.position,
          .line = tokenStream.line,
          .message = message,
          .token = get(-1)
        });
			}

			//===========================================//
			// Parsing

			void parse() {
				while (get(0).type != Token::T_EOF) {
          ast.emplace_back(expression());
				}
			}

			Expression* expression() {
				return binaryPriority0();
			}

			Expression* binaryPriority0() {
        auto result = binaryPriority1();

				if (!result)
					return nullptr;

				while (true) {
					auto token = get();
					if (token.type == Token::Operator && (
						token.value == "&&"  ||
						token.value == "||"
					)) {
            shift();

						auto binaryEx = new BinaryOperation();
						binaryEx->lhs = result;
						binaryEx->rhs = binaryPriority1();

						if			(token.value == "&&") binaryEx->type = BinaryOperation::And;
						else if (token.value == "||") binaryEx->type = BinaryOperation::Or;
				
						if (!binaryEx->rhs) {
							push("Syntax Error: Unexcepted symbol. Excepted expression to binary operation");
							return nullptr;
						}

						result = binaryEx;
					} else 
						break;
				}

				return result;
			}

			Expression* binaryPriority1() {
        auto result = binaryPriority2();

				if (!result)
					return nullptr;

				while (true) {
					auto token = get();
					if (token.type == Token::Operator && (
						token.value == ">"  ||
						token.value == "<"  ||
						token.value == "==" ||
						token.value == "!=" ||
						token.value == ">=" ||
						token.value == "<="
					)) {
            shift();

						auto binaryEx = new BinaryOperation();
						binaryEx->lhs = result;
						binaryEx->rhs = binaryPriority2();

						if			(token.value == ">") binaryEx->type = BinaryOperation::Greater;
						else if (token.value == "<") binaryEx->type = BinaryOperation::Less;
						else if (token.value == "==") binaryEx->type = BinaryOperation::Equal;
						else if (token.value == "!=") binaryEx->type = BinaryOperation::NotEqual;
						else if (token.value == ">=") binaryEx->type = BinaryOperation::GreaterOrEqual;
						else if (token.value == "<=") binaryEx->type = BinaryOperation::LessOrEqual;
				
						if (!binaryEx->rhs) {
							push("Syntax Error: Unexcepted symbol. Excepted expression to binary operation");
							return nullptr;
						}

						result = binaryEx;
					} else 
						break;
				}

				return result;
			}

			Expression* binaryPriority2() {
        auto result = binaryPriority3();

				if (!result)
					return nullptr;

				while (true) {
					auto token = get();
					if (token.type == Token::Operator && (
						token.value == "+" ||
						token.value == "-"
					)) {
            shift();

						auto binaryEx = new BinaryOperation();
						binaryEx->lhs = result;
						binaryEx->rhs = binaryPriority3();

						if			(token.value == "+") binaryEx->type = BinaryOperation::Add;
						else if (token.value == "-") binaryEx->type = BinaryOperation::Sub;
				
						if (!binaryEx->rhs) {
							push("Syntax Error: Unexcepted symbol. Excepted expression to binary operation");
							return nullptr;
						}

						result = binaryEx;
					} else 
						break;
				}

				return result;
			}

			Expression* binaryPriority3() {
        auto result = parentheses();

				if (!result)
					return nullptr;

				while (true) {
					auto token = get();
					if (token.type == Token::Operator && (
						token.value == "*" ||
						token.value == "/"
					)) {
						shift();

						auto binaryEx = new BinaryOperation();
						binaryEx->lhs = result;
            binaryEx->rhs = parentheses();

						if			(token.value == "*") binaryEx->type = BinaryOperation::Mul;
						else if (token.value == "/") binaryEx->type = BinaryOperation::Div;

						if (!binaryEx->rhs) {
							push("Syntax Error: Unexcepted symbol. Excepted expression to binary operation");
							return nullptr;
						}

						result = binaryEx;
					} else
						break;
				}

				return result;
			}

			Expression* parentheses() { 
				if (isEqual(Token::Operator, "(")) {
          auto result = expression();
					if (!isEqual(Token::Operator, ")")) {
            shift();
            push("Syntax Error: Unmatched opening parenthesis '(' detected. Ensure every '(' has a corresponding ')' before the end of the expression.)");
						return nullptr;
					}

					return result;
				}

				return unary();
			}

			Expression* unary() { 
				if (isEqual(Token::Operator, "-")) {
          auto unaryEx = new UnaryOperation();
					unaryEx->type = UnaryOperation::NEGATE;
          unaryEx->operand = expression();

					if (unaryEx->operand)
						return unaryEx;
					
					push("Syntax Error: Unexcepted symbol. Excepted expression to negate");
					delete unaryEx;
					return nullptr;
				}

				return identifier();
			}

			Expression* identifier() {
				if (isType(Token::Word))
          return new Identifier(std::move(get(-1).value));
				
				return value();
			}

			Expression* value() { 
				auto value = new Value();
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

				shift();
				push("Syntax Error: Unknown value type");
				delete value;
				return nullptr;
			}
		}; 
	}

	class LangImpl {
	public:
    virtual void compile(wdlang::Value*) = 0;
    virtual void compile(wdlang::Identifier*) = 0;
    virtual void compile(wdlang::UnaryOperation*) = 0;
    virtual void compile(wdlang::BinaryOperation*) = 0;
	};

	namespace wdlang {
    template <typename Derived>
    void ExpressionCRTP<Derived>::execute(LangImpl* executor) {
			executor->compile(static_cast<Derived*>(this));
    }
	}
}