#pragma once
#include "Array.h"

// ласс Stack, €вл€ющийс€ наследником класса Array
class Stack : public Array {
public:

	Stack();

	Stack(int size);

	Stack(const Stack& object);

	~Stack();

	void push(long long value);

	long long peek();

	void pop();

private:
};
