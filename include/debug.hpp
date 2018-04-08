#pragma once

#include "chunk.hpp"
#include <string>

namespace cplox
{
	/**
	 * Print out disassembly for entire chunk with label
	 */
	void disassembleChunk(Chunk& chunk, std::string const& name);

	/**
	 * Print out disassembly for instruction located at offset
	 */
	int disassembleInstruction(Chunk& chunk, int offset);

}