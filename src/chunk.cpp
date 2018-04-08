#include "../include/chunk.hpp"

namespace cplox
{
	void writeChunk(Chunk& chunk, uint8_t byte)
	{
		chunk.code.emplace_back(byte);
	}

	int addConstant(Chunk & chunk, Value value)
	{
		writeValueArray(chunk.constants, value);
		return static_cast<int>(chunk.constants.size() - 1);
	}

}