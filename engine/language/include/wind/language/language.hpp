#include "wind/utils/utils.hpp"

namespace wind {
	namespace wdlang {

    class Tokenizer {
      friend class TokenStream;
    public:

      struct Token {
        enum TokenType {
          T_EOF,

          Unknown,

          Number,
          Word,
          Operator,
          Char,
          String
        };

        TokenType type;
        std::string value;

        bool operator==(const Token& rhs) {
          return type == rhs.type && value == rhs.value;
        }

        bool operator!=(const Token& rhs) { 
          return type != rhs.type && value != rhs.value;
        }
      };

      class TokenStream {
        friend class Tokenizer;
      public:
        Token& end() {
          static Token eof = {
            .type = Token::T_EOF,
            .value = ""
          };

          return eof;
        }

        Token get() {
          return tokenizer.getNextToken();
        }

        int line;
        int position;

        TokenStream(const TokenStream&) = delete;
        TokenStream& operator=(const TokenStream&) = delete;
      private:
        Tokenizer& tokenizer;

        TokenStream(Tokenizer& tokenizer) : tokenizer(tokenizer) {
          line = position = 1;
        }
      };

      Tokenizer(const std::string& text): text(text), stream(*this) {
        cPos = 0;
      }

      TokenStream& getStream() {
        return stream;
      }

    private:
      TokenStream stream;
      std::string text;

      int cPos;

      const std::set<char> operators = {'=', '+', '-', '*', '/', '&', '|', ':', ',', '.'};
      const std::set<char> singleOperators = {'{', '}', '(', ')', ';'};

      //====================================================//
      // Utils

      char get(unsigned int relativePosition = 0) { 
        auto pos = cPos + relativePosition;
        if (pos >= text.size())
          return '\0';
        return text[pos];
      }

      char shift(unsigned int step=1) { 
        cPos += step;
        stream.position += step;

        return get();
      }

      bool isInSet(char ch, const std::set<char>& set) { 
        return set.find(ch) != set.end();
      }

      //====================================================//
      // Tokenization 

      Token getNextToken() { 
        auto ch = get();

        if (ch == '\0')
          return Token {
            .type = Token::T_EOF,
            .value = ""
          };

        if (ch == '\n') {
          stream.position = 0;
          stream.line += 1;
        }

        if (ch == ' ' || ch == '\n'  || ch == '\t') {
          shift();
          return getNextToken();
        }
        
        if (isInSet(ch, singleOperators)) {
          shift();
          return Token{
            .type = Token::Operator,
            .value = std::move(std::string(1, ch))
          };
        }

        if (ch == '\'') return getChar();
        if (ch == '"') return getString();
        if (SDL_isdigit(ch)) return getNumber();
        if (SDL_isalpha(ch)) return getWord();
        if (isInSet(ch, operators)) return getOperator();
         
        shift();
        return Token{ 
          .type = Token::Unknown,
          .value = std::string(1, ch)
        };
      }

      Token getString() { 
        std::string res = "";
        char ch = shift();

        while (ch != '"') {
          res.append(1, ch);

          ch = shift();
          if (ch == '\0')
            return Token{
              .type = Token::T_EOF,
              .value = std::move(res)
            };
        }

        shift();
        return Token{
          .type = Token::String,
          .value = std::move(res)
        };
      }

      Token getChar() {
        char value = shift();
        if (shift() != '\'')
          return Token{
            .type = Token::Unknown,
            .value = fmt::format("'{}", std::string(1, value))
          };

        shift();
        return Token{
          .type = Token::Char,
          .value = std::string(1, value)
        };
      }

      Token getNumber() {
        std::string res = "";
        auto ch = get();

        while (SDL_isdigit(ch)) {
          res.append(1, ch);
          ch = shift();
        }

        return Token{
          .type = Token::Number,
          .value = std::move(res)
        };
      }

      Token getWord() { 
        std::string res = "";
        auto ch = get();

        while (SDL_isalnum(ch)) {
          res.append(1, ch);
          ch = shift();
        }

        return Token{
          .type = Token::Word,
          .value = std::move(res)
        };
      }

      Token getOperator() {
        std::string res = "";
        auto ch = get();

        while (isInSet(ch, operators)) {
          res.append(1, ch);
          ch = shift();
        }

        return Token{
          .type = Token::Operator,
          .value = std::move(res)
        };
      }
    };

  }
}