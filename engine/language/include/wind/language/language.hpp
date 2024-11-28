#include "wind/language/tokenizer.hpp"
#include <queue>

namespace wind {
  class LangImpl;

	namespace wdlang {
		struct Node {
      virtual void execute(LangImpl*) = 0;
    };

		template <typename Derived> 
		struct NodeCRTP : public Node {
			void execute(LangImpl* executor) override;
		};

		template <typename Derived>
    struct Expression : public NodeCRTP<Derived> {};

		struct Value : public Expression<Value> {
			enum ValueType {
				Number,
				Char,
				String,
			};

			ValueType type;
      std::string value;
		};

    struct Identifier : public Expression<Identifier> {
      std::string name;

			Identifier(std::string&& name) : name(name) {}
		};
    
		struct BinaryOperation : public Expression<BinaryOperation> {
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
      Node* lhs;
      Node* rhs;
		};

    struct UnaryOperation : public Expression<UnaryOperation> {
			enum OperationType {
				NEGATE
			};

			OperationType type;
      Node* operand;
		};

		struct AssignStatement : public NodeCRTP<AssignStatement> {
			std::string name;
			Node* value;
		};

		struct VariableStatement : public NodeCRTP<VariableStatement> {
			bool isMutable;
			std::string type;
			std::string name;
			Node* value;
		};

		struct ClassMember : public NodeCRTP<ClassMember> {
			enum AccessModifier {
				Private,
				Public
			};

			AccessModifier access;
			Node* member;
		};

		struct ClassStatement : public NodeCRTP<ClassStatement> {
			std::string name;
			std::string parent;
			std::list<std::string> interfaces;
			std::list<ClassMember*> members;
		};

		struct FunctionArgumentStatement : public NodeCRTP<FunctionArgumentStatement> {
			std::string name;
			std::string type;
			Node* defaultValue;
		};

		struct FunctionStatement : public NodeCRTP<FunctionStatement> {
			std::string type;
			std::string name;
			std::list<FunctionArgumentStatement*> args;
			std::list<Node*> body;
		};
	
		struct ReturnStatement : public NodeCRTP<ReturnStatement> {
			Node* value;
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

			std::vector<Node*> getRoot() const {
				return ast;
			}

    private:
			std::queue<Error> errorStack;
			
			std::vector<Node*> ast;
			std::vector<Token> tokens;
			Tokenizer::TokenStream& tokenStream;

			int currentPosition = 0;

			enum class Scope {
				Global,
				InNamespace,
				InClass,
				InFunction
			};

			Scope currentScope;

			//===========================================//
			// Utils

			Token& get(unsigned int relativePosition = 0) {
        int pos = currentPosition + relativePosition;

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
				currentPosition += step;
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

			void except(Token::TokenType type, std::string&& value) {
        if (isEqual(type, std::move(value)))
					return;

				push(fmt::format("Syntax Error: Except '{}'. Unexcepted sybmol.", value));
			}

			void except(Token::TokenType type) {
        if (isType(type))
					return;

				push("Syntax Error: Unexcepted sybmol");
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
					currentScope = Scope::Global;
					ast.emplace_back(statement());
				}
			}

			Node* statement() { 
				return classS();
			}

			Node* classS() { 
				if (isEqual(Token::Word, "class")) {
					
					except(Token::Word);
          auto name = get(-1).value;

          std::string parent = "";
					if (isEqual(Token::Word, "extends")) {
            except(Token::Word);
						parent = get(-1).value;
					}

					std::list<std::string> interfaces = {};
          if (isEqual(Token::Word, "implements")) {
						if (get().type != Token::Word) {
              push("Syntax Error: Excepted interface to implements. Unexcepted symbol. ");
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

						auto member = new ClassMember();
						member->access = currentAccess;
						member->member = statement();

						if (!member->member)
							continue;

						members.emplace_back(member);
					}

					currentScope = Scope::Global;

					auto statement = new ClassStatement();
					statement->name = name;
					statement->parent = parent;
					statement->interfaces = interfaces;
					statement->members = members;

					return statement;
				}

				if (
					currentScope == Scope::InClass ||
					currentScope == Scope::InFunction
				) {
          return variable();
				}

				shift();
				push("Syntax Error: In global scope may be only class defination statements");
				return nullptr;
			}

			Node* variable() { 
				if (isEqual(Token::Word, "let")) {
					auto isMutable = isEqual(Token::Word, "mut");
          
					except(Token::Word);
          auto name = get(-1).value;

					except(Token::Operator, ":");

          except(Token::Word);
          auto type = get(-1).value;

					except(Token::Operator, "=");
          auto value = expression();

					auto statement = new VariableStatement();
					statement->isMutable = isMutable;
					statement->type = type;
					statement->name = name;
					statement->value = value;

					return statement;
				}

				return function();
			}

			Node* function() { 
				if (
					get(0).type == Token::Word &&
					get(1).type == Token::Word &&
					get(2).type == Token::Operator &&
					get(2).value == "("
				) {
					auto type = consume().value;
					auto name = consume().value;

					std::list<FunctionArgumentStatement*> args = {};
					bool require = false;
					bool first = true;

          except(Token::Operator, "(");
					while (!isEqual(Token::Operator, ")")) {
						if (get(0).type == Token::T_EOF) {
							push("Syntax Error: Unexcepted end of file");
							return nullptr;	
						}

						if (!first)
							except(Token::Operator, ",");
						first = false;

						auto arg = functionArg(require);

						if (!arg)
							return nullptr;
						
						args.emplace_back(arg);
					}

					std::list<Node*> body = {};

					if (isEqual(Token::Operator, "->")) {
						auto returnS = new ReturnStatement();
						returnS->value = expression();
            body.emplace_back(returnS);
					}
					else {
						except(Token::Operator, "{");
						while (!isEqual(Token::Operator, "}")) {
							if (get(0).type == Token::T_EOF) {
								push("Syntax Error: Unexcepted end of file");
								return nullptr;	
							}

							currentScope = Scope::InFunction;
							auto part = statement();

							if (!part) 
								continue;

							body.emplace_back(part);
						}
						
						currentScope = Scope::InClass;
					}

					auto statement = new FunctionStatement();
					statement->name = name;
					statement->type = type;
					statement->args = args;
					statement->body = body;

					return statement;
				}

				if (currentScope == Scope::InFunction) {
					return returnS();
				}

				shift();
				push("Syntax Error: In class scope may be only member defination statements");
				return nullptr;
			}
	
			Node* returnS() {
				if (isEqual(Token::Word, "return")) {
					Node* result = nullptr;
					if (!isEqual(Token::Operator, ";")) 
						result = expression();

					auto statement = new ReturnStatement();
					statement->value = result;

					return statement;
				}

				return assign();
			}

			FunctionArgumentStatement* functionArg(bool& requireDefaultParam) {
        if (isType(Token::Word)) {
					auto name = get(-1).value;
          except(Token::Operator, ":");
					except(Token::Word);
          auto type = get(-1).value;
					Node* value = nullptr;

					if (requireDefaultParam) 
            except(Token::Operator, "=");
					else if (isEqual(Token::Operator, "="))
						requireDefaultParam = true;
					
					if (requireDefaultParam)
						value = expression();

					auto statement = new FunctionArgumentStatement();
					statement->defaultValue = value;
					statement->name = name;
					statement->type = type;

					return statement;
				}

				shift(1);
        push("Syntax Error: Excepted parameter name. Unexcepted symbol.");
				return nullptr;
			}

			Node* assign() { 
				if (isType(Token::Word) && isEqual(Token::Operator, "=")) {
					auto name = get(-2).value;
          auto value = expression();

					auto statement = new AssignStatement();
					statement->name = name;
					statement->value = value;

					return statement;
				}

				shift();
				push("Syntax error: Unexcepted symbol");
				return nullptr;
			}

			Node* expression() {
				return binaryPriority0();
			}

			Node* binaryPriority0() {
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

			Node* binaryPriority1() {
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

			Node* binaryPriority2() {
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

			Node* binaryPriority3() {
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

			Node* parentheses() { 
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

			Node* unary() { 
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

			Node* identifier() {
				if (isType(Token::Word))
          return new Identifier(std::move(get(-1).value));
				
				return value();
			}

			Node* value() { 
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

				shift(1);
				push("Syntax Error: Unknown value type");
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
    virtual void compile(wdlang::AssignStatement*) = 0;
    virtual void compile(wdlang::VariableStatement*) = 0;
    virtual void compile(wdlang::ClassMember*) = 0;
    virtual void compile(wdlang::ClassStatement*) = 0;
    virtual void compile(wdlang::FunctionArgumentStatement*) = 0;
    virtual void compile(wdlang::FunctionStatement*) = 0;
    virtual void compile(wdlang::ReturnStatement*) = 0;
	};

	namespace wdlang {
    template <typename Derived>
    void NodeCRTP<Derived>::execute(LangImpl* executor) {
			executor->compile(static_cast<Derived*>(this));
    }
	}
}