#define _CRT_SECURE_NO_WARNINGS

#include "BigInt.h"
#include "Array.h"
#include <cstdlib>
#include <iostream>

	//����������� �� ���������
	BigInt::BigInt() {
		sign = 1;
	}

	/*
	* �����������, ��������� BigInt �� ����� value:
	* 1)�������������� ���-�� �������� ����� value;
	* 2)�������������� ����������� ���-�� ����� ��� ������ � ������ Array,
	    ��� ������ ������ �������� � ���� 9 ����
	  3)����� ������������ � ������ ��������
	*/
	BigInt::BigInt(long long value) {
		sign = 1;
		if (value < 0) {
			sign = -1;
			value *= sign;
		}
		if (value == 0) {
			array.addToEnd(0);
		}
		else {
			long long digits = countDigits(value);
			long long cells = (digits % 9) == 0 ? (digits / 9) : (digits / 9 + 1);
			array.makeEqualSize(array.getSize(), cells);
			for (int i = cells - 1; i >= 0; i--) {
				array.insertByIndex(value % BASE, i);
				value /= BASE;
			}
		}
	}

	//�����������, ��������� BigInt �� ������
	BigInt::BigInt(char* valStr) {
		long long len, cells, totalDig;
		for (len = 0; valStr[len] != '\0'; len++) {
			if (valStr[len] < 48 || valStr[len]>57)
				throw std::invalid_argument("BigInt constuctor: invalid string");
		}
		if (valStr[0] == '-') {
			sign = -1;
			valStr++;
		}
		else sign = 1;
		cells = ((len % 9) == 0) ? (len / 9) : (len / 9 + 1);
		totalDig = len;
		array.makeEqualSize(array.getSize(), cells);
		for (int i = 0,j = 0; i < len; j++) {
			char digStr[10] = { 0 };
			int digAmount = ((totalDig % 9) == 0) ? 9 : (totalDig % 9);
			memcpy(digStr, valStr + i, digAmount);
			array.insertByIndex(_atoi64(digStr), j);
			i += digAmount;
			totalDig -= digAmount;
		}
	}

	//�����������, ����������� � �������� ��������� ����������� ������
	BigInt::BigInt(const char* valStr) : BigInt((char*)valStr) {
	}

	//����������� �����������
	BigInt::BigInt(const BigInt& object) : array(object.array) {
		sign = object.sign;
	}


	//����������
	BigInt::~BigInt() {
	}

	//��������� �����, ����������������� �������� Array
	Array BigInt::getArray() {
		return array;
	}
	//��������� ����� �����
	short BigInt::getSign() {
		return sign;
	}

	//������������ ����� �����
	void BigInt::setSign(short newSign) {
		if (newSign < -1 || newSign == 0 || newSign > 1)
			throw std::invalid_argument("Exception: invalid sign");
		sign = newSign;
	}

	//�������� ���������� ������������� ������ BigInt � ���� �������� �����
	char* BigInt::cStr() {
		int arrSize = array.getSize();
		int cStrSize = arrSize*9+(arrSize-1)+1;
		char* cStr = new char[cStrSize];
		int digits;
		size_t i = 0, j = 0;
		for (; i < cStrSize && j < arrSize; i++, j++) {
			long long curNum = array.getByIndex(j);
			digits = countDigits(curNum);
			memset(cStr + i, '0', 9);
			_i64toa(curNum, cStr + i + (9 - digits), 10);
			i += 8;
			if (j + 1 != arrSize) cStr[++i] = ' ';
		}
		return cStr;
	}

	//����� ��������� ���� ����� ���� BigInt:
	//���������� 2, ���� ������ > �������
	//���������� 1, ���� ���-�� ����� ������� > ���-�� ����� �������
	//���������� 0, ���� �����
	//���������� -1, ���� ���-�� ����� ������� < ���-�� ����� �������
	//���������� -2, ���� ������ < �������
	short BigInt::compare(void* second) {
		short state;
		BigInt* secondBI = (BigInt*) second;
		if (array.getElmNum() > secondBI->array.getElmNum())
			state = 1;
		else if (array.getElmNum() == secondBI->array.getElmNum()) {
			state = 0;
			int size1 = array.getSize();
			int size2 = secondBI->array.getSize();
			for (int i = 0; i < size1 && (state != 2 && state != -2); i++) {
				long long curElem = array.getByIndex(i);
				long long secondElem = i < size2 ? secondBI->array.getByIndex(i) : 0;
				if (curElem > secondElem)
					state = 2;
				else if (curElem < secondElem)
					state = -2;
			}
		}
		else state = -1;
		return state;
	}

	//����� ��������� �������� ���� BigInt �����
	void BigInt::equalize(void* second) {
		short state = compare(second);
		BigInt* secondBI = (BigInt*)second;
		int elemNum1 = array.getElmNum();
		int elemNum2 = secondBI->array.getElmNum();
		if (state == 1) {
			while (elemNum2 < elemNum1) {
				secondBI->array.shiftSliceR(0);
				secondBI->array.insertByIndex(0, 0);
				elemNum2++;
			}
		}
		else if (state == -1) {
			while (elemNum1 < elemNum2) {
				array.shiftSliceR(0);
				array.insertByIndex(0, 0);
				elemNum1++;
			}
		}
	}

	/*
	* ����� �������� ���� BigInt �����:
	* 1)� ����������� �� ������ ����� ������� ��������� ������ ��������;
	* 2)�������� ����������� ����� �������� � �������, ��� ������ ������
	    ������������ � ����������� ���
	*/
	void BigInt::add(void* added) {
		BigInt* secondBi = (BigInt*)added;
		long long rest = 0, result = 0;
		if (sign == 1 && secondBi->sign == -1) {
			sign *= -1;
			subtract(added);
			sign *= -1;
		}
		else if (sign == -1 && secondBi->sign == 1) {
			sign *= -1;
			subtract(added);
			sign *= -1;
		}
		else  {
			equalize(added);
			for (int i = array.getSize() - 1, j = i; i >= 0; i--, j--) {
				long long curElem = array.getByIndex(i);
				long long addedElem = j >= 0 ? secondBi->array.getByIndex(i) : 0;
				result = curElem + addedElem + rest;
				rest = result >= BASE ? 1 : 0;
				result -= rest > 0 ? BASE : 0;
				array.deleteByIndex(i);
				array.insertByIndex(result, i);
				if (rest && array.getElmNum() == array.getSize() && i == 0) {
					array.shiftSliceR(i++);
					array.insertByIndex(0, 0);
				}
			}
		}
	}

	/*
	* ����� ��������� ���� BigInt �����:
	* 1)� ����������� �� ������ ����� ������� �������� ������ ���������
	* 2)��������� ����������� � �������, ��� ������ ������ ���������� � 
	    ����������� ���
	*/
	void BigInt::subtract(void* subtracted) {
		BigInt* secondBi = (BigInt*)subtracted;
		long long rest = 0, result = 0;
		if (sign == -1 && secondBi->sign == 1) {
			sign *= -1;
			add(subtracted);
			sign *= -1;
		}
		else if (sign == 1 && secondBi->sign == -1) {
			sign *= -1;
			add(subtracted);
			sign *= -1;
		}
		else {
			equalize(subtracted);
			if (compare(subtracted) == -2) {
				swap(subtracted);
				sign = -1;
			}
			for (int i = array.getElmNum() - 1; i >= 0; i--) {
				long long curElem = array.getByIndex(i);
				long long subElem = secondBi->array.getByIndex(i);
				result = curElem - subElem - rest;
				rest = result < 0 ? 1 : 0;
				result += rest > 0 ? BASE : 0;
				array.deleteByIndex(i);
				array.insertByIndex(result, i);
			}
		}
	}

	/*
	* ����� ��������� ���� BigInt �����:
	* 1)� ������ ���� ���� �� ���������� ����� 0, �� �� ���������� ���������,
		����� ��������� ����� 0;
	  2)��������� ����������� � �������, ��� ������ ������ ����� ����������
		������������� �� ����� ������� ��������� ������� �����, ����� ����
		��������� �����������;
	  3)����� ��������� � ������ ����� ���������� �������� ����, ���� �������
		�������
	*/
	void BigInt::multiply(void* factor) {
		BigInt* secondBi = (BigInt*)factor;
		BigInt bigMult;
		if (secondBi->array.isEmpty() || array.isEmpty()) {
			bigMult.array.addToEnd(0);
			swap(&bigMult);
		}
		else {
			int thisLen = array.getSize();
			int factorLen = secondBi->array.getSize();
			long long resLen = thisLen + factorLen + 1, resMult = 0, rest = 0;
			bigMult.array.makeEqualSize(resLen, bigMult.array.getSize());
			for (int i = thisLen - 1; i >= 0; i--) {
				long long curElem = array.getByIndex(i);
				for (int j = factorLen - 1; j >= 0 || rest > 0; j--) {
					long long factorElem = (j >= 0) ? secondBi->array.getByIndex(j) : 0;
					long long resElem = bigMult.array.getByIndex(i + j + 2);
					resMult = resElem + (curElem * factorElem) + rest;
					if (resElem == 0 && resMult != 0) 
						bigMult.array.insertByIndex(resMult % BASE, i + j + 2);
					else if (resElem !=0) {
						bigMult.array.deleteByIndex(i + j + 2);
						bigMult.array.insertByIndex(resMult % BASE, i + j + 2);
					}
					rest = resMult >= BASE ? resMult /= BASE : 0;
				}
			}
			while (bigMult.array.getByIndex(0) == 0) {
				bigMult.array.shiftSliceL(0);
				bigMult.array.reduceCap(1);
			}
			bigMult.sign = (sign == secondBi->sign) ? 1 : -1;
			swap(&bigMult);
		}
	}

	/*
	* ����� ������� ���� BigInt �����:
	* 1)���� �������� ����� 0, �� ����������� ����������;
	* 2)���� �������� > ��������, �� �� ���������� �������, � ����� ���������� �
	    ��������� 0;
	  3)������� ����������� � �������: 
	    3.1)�������� ������ ��������;
	    3.2)����� ��������� ������ ����������� ����������� ������ ��������;
		3.3)�� �������� ������� �������� ���������� ��������� ������ ��������,
		    ����������� �� ��������;
		3.4)� ������������ �������� �������� ����.������ ��������
	  4)����� ������� ���������� ���������� ����� � ������, ���� ������� �������
	*/
	void BigInt::divide(void* divider) {
		BigInt* secondBi = (BigInt*)divider;
		BigInt result, curDivr(*secondBi);
		curDivr.sign = 1;
		if (curDivr.array.isEmpty())
			throw std::invalid_argument("divide: division by zero");
		if (compare(&curDivr) < 0) {
			result.array.addToEnd(0);
			swap(&result);
			return;
		}
		result.array.makeEqualSize(result.array.getSize(), array.getSize());
		BigInt curDividend(result);
		for (int i = 0, j = 0; i < array.getSize(); i++, j++) {
			long long curElem = array.getByIndex(i);
			curDividend.array.insertByIndex(curElem, j);
			long long curFactor = 0, left = 0, right = BASE;
			while (left <= right) {
				long long mid = (left + right) / 2;
				BigInt tmp(mid);
				tmp.multiply(&curDivr);
				if (tmp.compare(&curDividend) <= 0) { 
					curFactor = mid;
					left = mid + 1;
				}
				else right = mid - 1;
			}
			result.array.insertByIndex(curFactor, i);
			BigInt tmpFactor(curFactor);
			tmpFactor.multiply(&curDivr);
			curDividend.subtract(&tmpFactor);
			while (curDividend.array.getByIndex(0) == 0) {
				if (curDividend.array.getElmNum() == 0) break;
				curDividend.array.deleteByIndex(0);
				curDividend.array.shiftSliceL(0);
				j--;
			}
		}
		while (result.array.getByIndex(0) == 0) {
			result.array.shiftSliceL(0);
			result.array.reduceCap(1);
		}
		result.sign = (sign == secondBi->sign) ? 1 : -1;
		swap(&result);
	}

	//����� ������ ������ ��� ���� BigInt �����
	void BigInt::swap(void* second) {
		BigInt* secondBi = (BigInt*)second;
		Array::swapArray(array, secondBi->array);
		short tmpSign = sign;
		sign = secondBi->sign;
		secondBi->sign = tmpSign;
	}

	
	//����� �������� ���-�� �������� ������������� ����� value
	int BigInt::countDigits(long long value) {
		int digits = 0;
		if (value == 0 || value < 0) digits++;
		while (value != 0) {
			digits++;
			value /= 10;
		}
		return digits;
	}