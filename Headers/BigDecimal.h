#pragma once
#include "BigInt.h"

// ласс BigDecimal, €вл€ющийс€ наследником класса Number
class BigDecimal : public Number
{
public:
	BigDecimal();

	BigDecimal(char* valStr);

	BigDecimal(const char* valStr);

	BigDecimal(long double value);

	BigDecimal(const BigDecimal& object);

	~BigDecimal();

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

private:
	Array array;
	short sign; //long long dotPos;
	int intCells;
	const static short bufSize = 317;
	const static int BASE = 1000000000;

	int getStrLen(char* str);

	int powOfTen(int deg);
};

