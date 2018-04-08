#include "../include/chunk.hpp"

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

	int addConstant(Chunk & chunk, Value value)
	{
		writeValueArray(chunk.constants, value);
		return static_cast<int>(chunk.constants.size() - 1);
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