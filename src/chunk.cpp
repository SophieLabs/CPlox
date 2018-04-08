#include "../include/chunk.hpp"

namespace cplox
{
	void writeChunk(Chunk& chunk, uint8_t byte, int line)
	{
		chunk.code.emplace_back(byte);
		chunk.lines.emplace_back(line);
	}

	int addConstant(Chunk & chunk, Value value)
	{
		writeValueArray(chunk.constants, value);
		return static_cast<int>(chunk.constants.size() - 1);
	}

}