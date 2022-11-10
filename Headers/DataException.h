#pragma once

#include <exception>
class DataException : public std::exception
{
public:

	DataException(const char* arg, long long errorData);

	DataException(const char* arg, int amount, long long errorData1, ...);

	DataException(const DataException& other);

	~DataException();

	const char* whatData() const;

private:

	long long* getData() const;

	int countDigits(long long value) const;

	int size;
	long long* data;
};

