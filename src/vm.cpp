#include "../include/vm.hpp"
#include "../include/common.hpp"
#include "../include/debug.hpp"

namespace cplox
{
	VM::VM()
	{
	}

	VM::~VM()
	{
	}

	InterpretResult VM::interpret(Chunk & chunk)
	{
		ip = &(chunk.code[0]);

		InterpretResult result = run(chunk);
		return result;
	}

	InterpretResult VM::run(Chunk & chunk)
	{
		auto read_byte = [this]() { return *ip++; };
		auto read_constant = [this, &chunk, &read_byte]() { return chunk.constants[read_byte()]; };
		auto read_long_constant = [this, &chunk, &read_byte]() { return chunk.constants[read_byte() | (read_byte() << 8) | (read_byte() << 16)]; };

		for(;;) {
#ifdef DEBUG_TRACE_EXECUTION
			printf("          ");
			for(Value const& value : stack)
			{
				printf("[ ");
				printValue(value);
				printf(" ]");
			}
			printf("\n");
			disassembleInstruction(chunk, ip - &(chunk.code[0]));
#endif
			uint8_t instruction;
			switch(instruction = read_byte())
			{
			case OpCode::OP_CONSTANT:
			{
				Value constant = read_constant();
				push(constant);
				break;
			}
			case OpCode::OP_CONSTANT_LONG:
			{
				Value constant = read_long_constant();
				push(constant);
				break;
			}
			case OpCode::OP_RETURN:
				printValue(pop());
				printf("\n");
				return InterpretResult::OK;
			}
		}
		return InterpretResult();
	}

	void VM::push(Value & value)
	{
		stack.emplace_back(value);
	}

	Value VM::pop()
	{
		// This will need runtime error checking
		Value ret = stack.back();
		stack.pop_back();
		return ret;
	}
}