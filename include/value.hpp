#pragma once

#include <vector>

namespace cplox
{
	using Value = double;

	using ValueArray = std::vector<Value>;
	
	void writeValueArray(ValueArray & valArray, Value value);

	void printValue(Value value);
}