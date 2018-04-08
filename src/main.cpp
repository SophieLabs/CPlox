#include "../include/common.hpp"
#include "../include/chunk.hpp"
#include "../include/debug.hpp"
#include "../include/vm.hpp"

int main(int argc, const char* argv[])
{
	{
		cplox::VM vm;
		cplox::Chunk chunk;
		cplox::writeConstant(chunk, 1.2, 123);
		cplox::writeChunk(chunk, cplox::OpCode::OP_RETURN, 123);
		cplox::disassembleChunk(chunk, "test chunk");

		printf("Interpreting\n");
		vm.interpret(chunk);
	}
	system("pause");
	return 0;
}