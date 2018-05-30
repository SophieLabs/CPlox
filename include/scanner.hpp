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

	void initScanner(const char* source);
	Token scanToken();
}