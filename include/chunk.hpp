#pragma once

#include "common.hpp"
#include "value.hpp"

#include <vector>
#include <utility>

namespace cplox
{
	enum OpCode : uint8_t {
		OP_CONSTANT,
		OP_RETURN,
	};

	struct Chunk {
		std::vector<uint8_t> code;
		// Run length encoding of line numbers
		std::vector<int> line_runs;
		// Might be able to eliminate this if line
		// numbers are always sequential
		std::vector<int> line_numbers;
		ValueArray constants;
	};

	void writeChunk(Chunk& chunk, uint8_t byte, int line);
	int addConstant(Chunk& chunk, Value value);
	
	/**
	 * Finds the line number of the byte at offset and also tags if
	 * it is the first occurrence of that number
	 * \param chunk - Byte chunk to access
	 * \param offset - Byte offset into chunk
	 * \return Pair indicating line number (pair::first) and occurrence
	 * (pair::second == true if first occurrence)
	 */
	std::pair<int, bool> getLine(Chunk& chunk, int offset);
}