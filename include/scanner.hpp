#pragma once

namespace cplox
{
	enum class TokenType {
		// Single-character tokens
		LEFT_PAREN, RIGHT_PAREN,
		LEFT_BRACE, RIGHT_BRACE,
		COMMA, DOT, MINUS, PLUS,
		SEMICOLON, SLASH, STAR,

		// One or two character tokens
		BANG, BANG_EQUAL,
		EQUAL, EQUAL_EQUAL,
		GREATER, GREATER_EQUAL,
		LESS, LESS_EQUAL,

		// Literals
		IDENTIFIER, STRING, NUMBER,

		// Keywords
		AND, CLASS, ELSE, FALSE,
		FUN, FOR, IF, NIL, OR,
		PRINT, RETURN, SUPER, THIS,
		TRUE, VAR, WHILE,

		ERROR,
		//Can't use EOF as it is #define'd in cstdio
		END_OF_FILE
	};

	struct Token {
		TokenType type;
		const char* start;
		int length;
		int line;
	};


	class Scanner{
	public:
		Scanner(const char* source);
		Token scanToken();

	private:
		const char * start;
		const char * current;
		int line = { 1 };

		bool isAtEnd() const { return *current == '\0';	}
		char advance() {
			++current;
			return current[-1];
		}
		char peek() const { return *current; }
		char peekNext() const {
			if(isAtEnd()) return '\0';
			return current[1];
		}
		bool match(char expected);
		void skipWhitespace();
		
		TokenType checkKeyword(int start, int length, const char* rest, TokenType type) const;
		TokenType identifierType() const;

		Token identifier();
		Token number();
		Token string();
		Token makeToken(TokenType type);
		Token errorToken(const char* message);

	};
}