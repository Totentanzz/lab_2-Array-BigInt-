#define _CRT_SECURE_NO_WARNINGS

#include "BigDecimal.h"
#include <iostream>

//����������� �� ���������
BigDecimal::BigDecimal() : BigDecimal((long long)0) {
}

/*
* �����������, ����������� � �������� ��������� ������:
* 1) ��������� ��� ����� ����� �� '.' �� ����� �����, ��������� �� � ������ ��������� �������:
*	 ������� ������������ ���-�� ����, ������� ����� ������� �� ������� �� 9, ����� ������������
*	 ���������� ����� �������� �� 9
* 2) ����� '.' ��� ���������� ����� ������������ ����� ������� �����, ������� ������������
*	 ��������� �������: ������� �����, ��������� �� 9 ���� (���� ���� �������� ������ 9, ��
*    ������� ��� ����������), ������������� ���-�� ���� curDigits, ����� ���������� �� 10^N,
*    ��� N=9-curDigits, � ������������ � ������ (��������� �� 10^N ����������, ����� ���������
*    ����������� � ������, ���� ���� ��������� ������ ��� 9)
* 3) ����� ������ �����, � ������� ���������� ������ ��������
*    ������: "123456789123.00000040501" -> [123,456789123,405,10000000]
*    (123 � 456789123 - ����� �����, 405 � 10000000 - ������� �����)
*/
BigDecimal::BigDecimal(char* valStr) {
	intCells = 0;
	if (valStr[0] == '-') {
		sign = -1;
		valStr++;
	}
	else sign = 1;
	int strLen = getStrLen(valStr);
	int intDig = 0, flDig = 0;
	char* end = valStr + strLen + 1;
	char* isDot = std::find(valStr, end, '.');
	int dotPos = isDot - valStr;
	for (int i = 0; i <= strLen;) {
		char digStr[10] = { 0 };
		if (i < dotPos) {
			if (i == 0) intDig = dotPos;
			int subDig = (intDig % 9 != 0) ? intDig % 9 : 9;
			memcpy(digStr, valStr + i, subDig);
			array.addToEnd(_atoi64(digStr));
			intDig -= subDig;
			intCells++;
			i += subDig;
		}
		else {
			if (i == dotPos) i++;
			if (i == dotPos + 1) flDig = strLen - (dotPos + 1);
			int subDig = (flDig > 9) ? 9 : flDig;
			memcpy(digStr, valStr + i, subDig);
			long long curNum = _atoi64(digStr);
			int curDigits = getStrLen(digStr);
			curNum *= powOfTen(9 - curDigits);
			array.addToEnd(curNum);
			flDig -= subDig;
			i += (flDig > 0) ? subDig : subDig + 1;
		}
	}
	array.reduceCap(array.getSize() - array.getElmNum());
}

//�����������, ����������� � �������� ��������� ����������� ������
BigDecimal::BigDecimal(const char* valStr) : BigDecimal((char*)valStr) {
}

//�����������, ����������� � �������� ��������� ����� (�������� ����������� �� ������)
BigDecimal::BigDecimal(long double value) {
	char* valStr = new char[bufSize];
	memset(valStr, 0, bufSize);
	sprintf(valStr, "%f", value);
	BigDecimal tmp(valStr);
	swap(&tmp);
}

//����������� �����������
BigDecimal::BigDecimal(const BigDecimal& object) : array(object.array) {
	sign = object.sign;
	intCells = object.intCells;
}

//����������
BigDecimal::~BigDecimal() {
}

//��������� �������, � ������� �������� �����
Array BigDecimal::getArray() {
	return array;
}

//��������� ����� �����
short BigDecimal::getSign() {
	return sign;
}

//������������ ����� �����
void BigDecimal::setSign(short newSign) {
	if (newSign < -1 || newSign == 0 || newSign >> 1)
		throw("Exception: invalid sign");
	sign = newSign;
}

/*
* ����� ��������� ���������� ������������� ����� ���� BigDecimal:
* 1) �������� �������� ������������� �������, � ������� �������� �����
* 2) ���� ����� �������������, �� ������ '[' ������ '-', ����� ������� ������ '['
* 3) ����������� �� ���� ������, ������� ������� ',' ' ' ']'
* 4) � ������ ���� ����� ����� ����� �����������, ������ '.' ������ ����������� ','
*	 (�.�. ���� ���-�� ���������� ��������� ������� ����� ���-�� ����� ��������� intCells
      � �������)
* 5) � ������ ���� ����� ����� ����������� � '.' ��� ������������, �� ��� ������� ����������
     ��������, ��������������� ����� ������� �����, ������������ ���-�� ����� �����, �������
	 �������, ��������� ���� �����
	 ������:   [999876535,110876535,110870144,3693144,809900000] ->
	         -> 999876535110876535110870144.003693144809900000

*/
char* BigDecimal::cStr() {
	char* cArr = array.cStr();
	int cArrSize, cStrSize, tmpCells;
	for (cArrSize = 1; cArr[cArrSize] != '\0'; cArrSize++);
	cStrSize = (array.getSize() + 1) * 9 , tmpCells = 0;
	char* cStr = new char[cStrSize];
	memset(cStr, 0, cStrSize);
	memcpy(cStr, cArr, cArrSize);
	if (sign == 1) memmove(cStr, cStr + 1, cStrSize - 1);
	else cStr[0] = '-';
	for (size_t i = 0; i < cStrSize; i++) {
		if ((tmpCells + 1 == intCells) && (cStr[i]==',')) {
			cStr[i] = '.';
			tmpCells++;
		}
		else if (cStr[i] == ',' || cStr[i] == ' ' || cStr[i] == ']') {
			memmove(cStr + i, cStr + i + 1, cStrSize - (i + 1));
			tmpCells++;
			i--;
		}
		else if (tmpCells >= intCells && tmpCells < array.getSize()) {
			long long lstDig = i, flPartPos = i;
			char digStr[10] = { 0 };
			for (; cStr[lstDig] != ',' && cStr[lstDig] != ']'; lstDig++);
			memcpy(digStr, cStr + i, lstDig - i);
			flPartPos += 9 - getStrLen(digStr);
			memmove(cStr + flPartPos, cStr + i, cStrSize - flPartPos);
			memset(cStr + i, '0', flPartPos - i);
			i = flPartPos + (lstDig - i - 1);
			tmpCells++;
		}
	}
	return cStr;
}

/*
* ����� ��������� ���� ����� ���� BigInt:
* 1)����������  2, ���� ������ > �������
* 2)����������  1, ���� ����� ����� ������� > ����� ����� ������� (intCells_1>intCells_2)
* 3)����������  0, ���� �����
* 4)���������� -1, ���� ����� ����� ������� < ����� ����� ������� (intCells_1<intCells_2)
* 5)���������� -2, ���� ������ < �������
*/
short BigDecimal::compare(void* second) {
	short state = 0;
	BigDecimal* secondBd = (BigDecimal*)second;
	if (intCells > secondBd->intCells) state = 1;
	else if (intCells == secondBd->intCells) {
		state = 0;
		int size1 = array.getSize();
		int size2 = secondBd->array.getSize();
		int maxSize = size1 < size2 ? size2 : size1;
		for (int i = 0; i < maxSize && (state != 2 && state != -2); i++) {
			long long curElem = i < size1 ? array.getByIndex(i) : 0;
			long long secondElem = i < size2 ? secondBd->array.getByIndex(i) : 0;
			if (curElem > secondElem)
				state = 2;
			else if (curElem < secondElem)
				state = -2;
		}
	}
	else state = -1;
	return state;
}

//����� ��������� ����� �������� ���� ����� ���� BigDecimal
void BigDecimal::equalize(void* second) {
	short state = compare(second);
	BigDecimal* secondBd = (BigDecimal*)second;
	if (state == 1) {
		while (secondBd->intCells < intCells) {
			secondBd->array.shiftSliceR(0);
			secondBd->array.insertByIndex(0, 0);
			secondBd->intCells++;
		}
		secondBd->array.reduceCap(secondBd->array.getSize() - secondBd->array.getElmNum());
	}
	else if (state == -1) {
		while (intCells < secondBd->intCells) {
			array.shiftSliceR(0);
			array.insertByIndex(0, 0);
			intCells++;
		}
		array.reduceCap(array.getSize() - array.getElmNum());
	}
}

/*
* ����� �������� ���� ����� ���� BigDecimal:
* 1)� ����������� �� ������ ����� ������� ��������� ������ ��������;
* 2)�������� ����������� ����� �������� � �������, ��� ������ ������
	������������ � ����������� ���
*/
void BigDecimal::add(void* added) {
	BigDecimal* secondBd = (BigDecimal*)added;
	long long rest = 0, result = 0;
	if (sign == 1 && secondBd->sign == -1) {
		sign *= -1;
		subtract(added);
		sign *= -1;
	}
	else if (sign == -1 && secondBd->sign == 1) {
		sign *= -1;
		subtract(added);
		sign *= -1;
	}
	else {
		equalize(added);
		//array.makeEqualSize(array.getSize(), secondBd->array.getSize());
		int curSize = array.getSize();
		int addSize = secondBd->array.getSize();
		for (int i = curSize - 1; i >= 0; i--) {
			long long curElem = array.getByIndex(i);
			long long addElem = (i+1<=addSize) ? (secondBd->array.getByIndex(i)) : 0;
			result = curElem + addElem + rest;
			rest = result >= BASE ? 1 : 0;
			result -= rest > 0 ? BASE : 0;
			if (i + 1 <= array.getElmNum()) array.deleteByIndex(i);
			array.insertByIndex(result, i);
			if (rest && array.getElmNum() == array.getSize() && i == 0) {
				array.shiftSliceR(i);
				array.insertByIndex(rest, 0);
				intCells++;
			}
		}
		array.reduceCap(array.getSize() - array.getElmNum());
	}
}

/*
*    ����� ��������� ���� BigInt �����:
* 1) � ����������� �� ������ ����� ������� �������� ������ ���������
* 2) ��������� ����������� � �������, ��� ������ ������ ���������� �
*	����������� ���
*/
void BigDecimal::subtract(void* subtracted) {
	BigDecimal* secondBd = (BigDecimal*)subtracted;
	BigDecimal secondBdCpy(*secondBd);
	long long rest = 0, result = 0;
	if (sign == -1 && secondBd->sign == 1) {
		sign *= -1;
		add(subtracted);
		sign *= -1;
	}
	else if (sign == 1 && secondBd->sign == -1) {
		sign *= -1;
		add(subtracted);
		sign *= -1;
	}
	else {
		equalize(&secondBdCpy);
		//array.makeEqualSize(array.getSize(), secondBdCpy.array.getSize());
		int curSize = array.getSize();
		int subSize = secondBdCpy.array.getSize();
		if (compare(&secondBdCpy) == -2) {
			swap(&secondBdCpy);
			sign = -1;
		}
		for (int i = array.getSize() - 1; i >= 0; i--) {
			long long curElem = array.getByIndex(i);
			long long subElem = (i+1<=subSize) ? secondBdCpy.array.getByIndex(i) : 0;
			result = curElem - subElem - rest;
			rest = result < 0 ? 1 : 0;
			result += rest > 0 ? BASE : 0;
			if (i + 1 <= array.getElmNum()) array.deleteByIndex(i);
			array.insertByIndex(result, i);
		}
		array.reduceCap(array.getSize() - array.getElmNum());
		secondBdCpy.array.reduceCap(secondBdCpy.array.getSize() - secondBdCpy.array.getElmNum());
	}
}

void BigDecimal::multiply(void* factor) {
}

void BigDecimal::divide(void* divider) {
}

//����� ������ ������ ���� ����� ���� BigDecimal
void BigDecimal::swap(void* second) {
	BigDecimal* secondBi = (BigDecimal*)second;
	Array::swapArray(array, secondBi->array);
	long long tmpIntCells = intCells;
	short tmpSign = sign;
	intCells = secondBi->intCells;
	secondBi->intCells = tmpIntCells;
	sign = secondBi->sign;
	secondBi->sign = tmpSign;
}

//����� �������� ����� ������
int BigDecimal::getStrLen(char* str) {
	int i;
	for (i = 0; str[i] != '\0'; i++) {
		if ((str[i] < 48 && str[i] != 46) || str[i] > 57)
			throw("Exception: invalid string");
	}
	return i;
}

//����� ���������� 10 � ������� deg
int BigDecimal::powOfTen(int deg) {
	if (deg < 0)
		throw("Exception: invalid degree");
	int result = 1;
	while (deg) {
		result *= 10;
		deg--;
	}
	return result;
}
