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
		/** Replace this macro later once I have a better idea of how the dynamic typing will work */
#define BINARY_OP(op) \
	do { \
		double b = pop(); \
		double a = pop(); \
		push(a op b); \
	} while(false)

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
			case OpCode::OP_NEGATE:
				push(-pop());
				break;
			case OpCode::OP_ADD:		BINARY_OP(+); break;
			case OpCode::OP_SUBTRACT:	BINARY_OP(-); break;
			case OpCode::OP_MULTIPLY:	BINARY_OP(*); break;
			case OpCode::OP_DIVIDE:		BINARY_OP(/); break;
			case OpCode::OP_RETURN:
				printValue(pop());
				printf("\n");
				return InterpretResult::OK;
			}
		}
#undef BINARY_OP
	}

	void VM::push(Value value)
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