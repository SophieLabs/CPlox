#include "../include/compiler.hpp"
#include "../include/common.hpp"
#include "../include/scanner.hpp"

#include <cstdio>

namespace cplox
{
	void compile(const char * source)
	{
		initScanner(source);

		int line = -1;
		for(;;) {
			Token token = scanToken();
			if(token.line != line) {
				printf("%4d ", token.line);
				line = token.line;
			}
			else {
				printf("   | ");
			}
			printf("%2d '%.*s'\n", token.type, token.length, token.start);

			if(token.type == TokenType::END_OF_FILE) break;
		}
	}
}