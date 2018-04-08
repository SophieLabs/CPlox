#pragma once

#include "chunk.hpp"

namespace cplox
{
	enum class InterpretResult 
	{
		OK = 0,
		COMPILE_ERROR,
		RUNTIME_ERROR,
	};

	class VM {
	public:
		VM();
		~VM();
		InterpretResult interpret(Chunk& chunk);
	private:
		uint8_t * ip;
		InterpretResult run(Chunk& chunk);
	};
}