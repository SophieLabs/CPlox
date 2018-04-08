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
		/** Instruction pointer. Points to next instruction */
		uint8_t * ip;
		InterpretResult run(Chunk& chunk);

		/** Stack for VM. Actually a vector to allow random
		access for debugging */
		std::vector<Value> stack;

		void push(Value value);
		Value pop();
	};
}