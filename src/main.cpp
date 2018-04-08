#include "../include/common.hpp"
#include "../include/chunk.hpp"
#include "../include/debug.hpp"

int main(int argc, const char* argv[])
{
	cplox::Chunk chunk;
	int constant = cplox::addConstant(chunk, 1.2);
	cplox::writeChunk(chunk, cplox::OpCode::OP_CONSTANT, 123);
	cplox::writeChunk(chunk, constant, 123);
	cplox::writeChunk(chunk, cplox::OpCode::OP_RETURN, 123);
	cplox::disassembleChunk(chunk, "test chunk");

	system("pause");
	return 0;
}