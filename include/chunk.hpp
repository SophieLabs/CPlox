#pragma once

#include "common.hpp"
#include "value.hpp"

#include <vector>

namespace cplox
{
	enum OpCode : uint8_t {
		OP_CONSTANT,
		OP_RETURN,
	};

	struct Chunk {
		std::vector<uint8_t> code;
		std::vector<int> lines;
		ValueArray constants;
	};

	void writeChunk(Chunk& chunk, uint8_t byte, int line);
	int addConstant(Chunk& chunk, Value value);
}