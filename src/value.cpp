#include "../include/value.hpp"

namespace cplox
{
	void writeValueArray(ValueArray & valArray, Value value)
	{
		valArray.emplace_back(value);
	}
	void printValue(Value value)
	{
		printf("%g", value);
	}
}
