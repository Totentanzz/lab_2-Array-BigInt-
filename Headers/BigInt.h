#pragma once
#include "Array.h"
#include "Number.h"

// ласс BigInt, €вл€ющийс€ наследником класса Number
class BigInt : public Number {
public:

	BigInt();

	BigInt(long long value);

	BigInt(const BigInt& object);

	BigInt(char* valStr);

	BigInt(const char* valStr);

	virtual ~BigInt();

	Array getArray();

	short getSign();

	void setSign(short newSign);

	char* cStr() override;

	short compare(void* second) override;

	void equalize(void* second) override;

	void add(void* added) override;

	void subtract(void* subtracted) override;

	void multiply(void* factor) override;

	void divide(void* divider) override;

	void swap(void* second) override;

protected:

private:

	Array array;
	short sign;
	const static int BASE = 1000000000;

	int countDigits(long long value);

};
