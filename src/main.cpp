#include "../include/common.hpp"
#include "../include/chunk.hpp"
#include "../include/debug.hpp"
#include "../include/vm.hpp"

#include <cstdio>
#include <cstdlib>
#include <string>



int main(int argc, const char* argv[])
{
	{
		cplox::VM vm;
		/*cplox::Chunk chunk;
		cplox::writeConstant(chunk, 1.2, 123);
		cplox::writeConstant(chunk, 3.4, 123);
		cplox::writeChunk(chunk, cplox::OpCode::OP_ADD, 123);
		cplox::writeConstant(chunk, 5.6, 123);
		cplox::writeChunk(chunk, cplox::OpCode::OP_DIVIDE, 123);
		cplox::writeChunk(chunk, cplox::OpCode::OP_NEGATE, 123);
		cplox::writeChunk(chunk, cplox::OpCode::OP_RETURN, 123);
		cplox::disassembleChunk(chunk, "test chunk");
		
		printf("Interpreting\n");
		vm.interpret(chunk);*/

		if(argc == 1) {
			vm.repl();
		}
		else if(argc == 2) {
			vm.runFile(argv[1]);
		}
		else {
			fprintf(stderr, "Usage: cplox [path]\n");
			exit(64);
		}		
	}
	system("pause");
	return 0;
}