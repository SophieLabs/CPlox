#include "../include/vm.hpp"
#include "../include/common.hpp"
#include "../include/compiler.hpp"
#include "../include/debug.hpp"

#include <gsl/gsl>

namespace cplox
{
	/*VM::VM() : ip(nullptr)
	{
	}

	VM::~VM()
	{
	}*/

	InterpretResult VM::interpret(const char* source)
	{
		compile(source);
		return InterpretResult::OK;
		/*ip = &(chunk.code[0]);

		InterpretResult const result = run(chunk);
		return result;*/
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
				Value const constant = read_constant();
				push(constant);
				break;
			}
			case OpCode::OP_CONSTANT_LONG:
			{
				Value const constant = read_long_constant();
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
			default:
				return InterpretResult::RUNTIME_ERROR;
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
		Value const ret = stack.back();
		stack.pop_back();
		return ret;
	}

	void VM::repl() {
		char line[1024];
		for(;;) {
			printf("> ");

			if(!fgets(line, sizeof(line), stdin)) {
				printf("\n");
				break;
			}

			interpret(line);
		}
	}

	void VM::runFile(const char* path) {
		auto source = readFile(path);
		cplox::InterpretResult result = interpret(source.get());

		if(result == cplox::InterpretResult::COMPILE_ERROR) exit(65);
		if(result == cplox::InterpretResult::RUNTIME_ERROR) exit(70);
	}

	std::unique_ptr<char[]> VM::readFile(const char* path) {
		FILE* file = fopen(path, "rb");

		if(file == NULL) {
			fprintf(stderr, "Could not open file \"%s\".\n", path);
			exit(74);
		}
		fseek(file, 0L, SEEK_END);
		size_t fileSize = ftell(file);
		rewind(file);

		std::unique_ptr<char[]> buffer(new char[fileSize + 1]);
		if(!buffer) {
			fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
			exit(74);
		}

		size_t bytesRead = fread(buffer.get(), sizeof(char), fileSize, file);
		if(bytesRead < fileSize) {
			fprintf(stderr, "Could not read file \"%s\".\n", path);
			exit(74);
		}
		buffer[bytesRead] = '\0';

		fclose(file);
		return buffer;
	}
}