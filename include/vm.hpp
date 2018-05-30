#pragma once

#include "chunk.hpp"
#include <memory>

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
		//VM();
		//~VM();

		/**
		* Runs the code located in chunk and gives result
		*/
		InterpretResult interpret(const char* source);

		void repl();

		void runFile(const char* path);

	private:
		/** Instruction pointer. Points to next instruction */
		uint8_t * ip = nullptr;

		/**
		 * Implementation for running the code in a chunk
		 */
		InterpretResult run(Chunk& chunk);

		/** Stack for VM. Actually a vector to allow random
		access for debugging */
		std::vector<Value> stack;

		/** Stack management functions */
		void push(Value value);
		Value pop();

		std::unique_ptr<char[]> readFile(const char* path);
	};
}