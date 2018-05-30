#include "../include/chunk.hpp"

#include <gsl/gsl>

namespace cplox
{
	void writeChunk(Chunk& chunk, uint8_t byte, int line)
	{
		chunk.code.emplace_back(byte);

		if(!chunk.line_numbers.empty() && chunk.line_numbers.back() == line)
		{
			++(chunk.line_runs.back());
		}
		else
		{
			chunk.line_numbers.emplace_back(line);
			chunk.line_runs.emplace_back(1);
		}
	}

	void writeConstant(Chunk & chunk, Value const& value, int line)
	{
		int const index = addConstant(chunk, value);
		if(index < 256) {
			writeChunk(chunk, OpCode::OP_CONSTANT, line);
			writeChunk(chunk, index, line);
		}
		else {
			writeChunk(chunk, OpCode::OP_CONSTANT_LONG, line);
			writeChunk(chunk, index, line);
			writeChunk(chunk, index >> 8, line);
			writeChunk(chunk, index >> 16, line);
		}
	}

	int addConstant(Chunk & chunk, Value const& value)
	{
		writeValueArray(chunk.constants, value);
		return gsl::narrow_cast<int>(chunk.constants.size() - 1);
	}

	std::pair<int, bool> getLine(Chunk& chunk, int offset)
	{
		for(auto n = chunk.line_runs.size(), i = decltype(n){0}; i < n; ++i)
		{
			if(offset < chunk.line_runs[i])
			{
				return std::make_pair(chunk.line_numbers[i], offset == 0);
			}
			offset -= chunk.line_runs[i];
		}
		return std::make_pair(-1, true);
	}

}