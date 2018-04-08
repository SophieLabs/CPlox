#pragma once

#include "common.hpp"
#include "value.hpp"

#include <vector>
#include <utility>

namespace cplox
{
	enum OpCode : uint8_t {
		OP_CONSTANT,
		OP_CONSTANT_LONG,	/** For accessing more than 256 constants. Uses 3 byte operand */
		OP_NEGATE,			/** Unary negation */
		OP_ADD,				/** Binary addition */
		OP_SUBTRACT,		/** Binary subtraction */
		OP_MULTIPLY,		/** Binary multiplication */
		OP_DIVIDE,			/** Binary division */
		OP_RETURN,
	};

	struct Chunk {
		/**
		 * Stores code and data in 8-bit bytes. For data types
		 * larger than 1 byte, uses little-endian format
		 */
		std::vector<uint8_t> code;
		// Run length encoding of line numbers
		std::vector<int> line_runs;
		// Might be able to eliminate this if line
		// numbers are always sequential
		std::vector<int> line_numbers;
		ValueArray constants;
	};

	/**
	 * Write data to chunk
	 * \param chunk - Byte chunk to access
	 * \param byte - Byte to append to chunk
	 * \param line - Source line number
	 */
	void writeChunk(Chunk& chunk, uint8_t byte, int line);
	
	/**
	 * Adds a constant to the register and writes the appropriate
	 * instruction to the chunk (depending on size of constants array)
	 * \param chunk - Byte chunk to access
	 * \param value - New constant value
	 * \param line - Source line number
	 */
	void writeConstant(Chunk& chunk, Value value, int line);

	/**
	 * Add a constant to the chunk's constant register
	 * \param chunk - Chunk to modify
	 * \param value - Value to add to register
	 * \return Index in register
	 */
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