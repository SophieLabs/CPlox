#pragma once

#include "chunk.hpp"
#include <string>

namespace cplox
{
	void disassembleChunk(Chunk& chunk, std::string const& name);
	int disassembleInstruction(Chunk& chunk, int offset);

}