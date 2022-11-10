#define _CRT_SECURE_NO_WARNINGS

#include "DataException.h"
#include <iostream>

#define DigitMaxSize 20

DataException::DataException(const char* arg, long long errorData)
	: std::exception(arg) {
	size = 1;
	data = new long long[size];
	data[0] = errorData;
}

DataException::DataException(const char* arg, int amount, long long errorData1, ...)
	:std::exception(arg) {
	size = amount;
	data = new long long[size];
	long long* p = &errorData1;
	for (size_t i=0; amount > 0; i++, p++, amount--) {
		data[i] = *p;
	}
}

DataException::DataException(const DataException& other)
	: std::exception(other) {
	size = other.size;
	data = new long long[size];
	memcpy(data, other.data, size*sizeof(long long));
}

DataException::~DataException() {
	delete[] data;
}

const char* DataException::whatData() const {
	int cStrSize = 41;
	char* cStr = new char[cStrSize];
	int digits;
	size_t i = 0, j = 0;
	for (; i < cStrSize && j < size; i++, j++) {
		if (i + DigitMaxSize >= cStrSize) {
			char* tmpCStr = new char[cStrSize * 2];
			memcpy(tmpCStr, cStr, cStrSize * sizeof(char));
			delete[] cStr;
			cStr = tmpCStr;
		}
		_i64toa(data[j], cStr + i, 10);
		digits = countDigits(data[j]);
		i += digits;
		if (j + 1 != size) cStr[i] = ',';
	}
	return cStr;
}

long long* DataException::getData() const {
	long long* dataCpy = new long long[size];
	memcpy(dataCpy, data, size * sizeof(long long));
	return dataCpy;
}

int DataException::countDigits(long long value) const {
	int digits = 0;
	if (value == 0 || value < 0) digits++;
	while (value != 0) {
		digits++;
		value /= 10;
	}
	return digits;
}