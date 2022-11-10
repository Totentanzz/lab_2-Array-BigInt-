#define _CRT_SECURE_NO_WARNINGS

#include "Number.h"
#include "BigInt.h"
#include "Stack.h"
#include "Queue.h"
#include "BigDecimal.h"
#include "DataException.h"
#include <iostream>

using namespace std;

void test1() {
	Array a(-1);
}

void test2() {
	Array a(3);
	a.reduceCap(3);
}

void test3() {
	Array a(4);
	a.makeEqualSize(1, 2);
}

void test4() {
	Array a(5);
	a.insertByIndex(2, 6);
}

void test5() {
	Array a(6);
	a.deleteByIndex(-2);
}

void test6() {
	Array a(7);
	a.getByIndex(8);
}

void test7() {
	Array a(7);
	a.getSlice(5, 4);
}

void test8() {
	Array a(7);
	a.shiftSliceR(8);
}

void test9() {
	Array a(7);
	a.shiftSliceL(9);
}

void test10() {
	BigInt a("1324ab15.");
}

void test11() {
	BigInt a(1515);
	a.setSign(20);
}

void test12() {
	BigInt a(15213);
	BigInt b("0");
	a.divide(&b);
}

void test13() {
	BigDecimal a("1b32a.12c44");
}

void test14() {
	BigDecimal a("1321244");
}

void test15() {
	BigDecimal b("1234.1325");
	b.setSign(20);
}

void test16() {
	Queue a;
	a.peek();
}

void test17() {
	Queue a;
	a.pop();
}

void test18() {
	Stack a;
	a.peek();
}

void test19() {
	Stack a;
	a.pop();
}

void runTest(void(*func)(void)) {
	try
	{
		func();
	}
	catch (const DataException& ex)
	{
		cout << ex.what() << '\t' << ex.whatData() << endl;
	}
	catch (const exception& ex1)
	{
		cout << ex1.what() << endl;
	}
}

void main() {
	long long one = 8446744073709551617;
	long long two = 8446744073709551618;
	BigInt first("9998765351108765351108701440036931448099000");
	BigInt second("0");
	char ab1[] = "8446744073709551618.8446744073709551618";
	char ab2[] = "999876535110876535110870144.0036931448099000";
	BigDecimal bd1(ab1);
	BigDecimal bd2(ab2);
	first.divide(&second);
	runTest(test10);
	/*for (int i = 0; i < 1000; i++) {
		cout << bd1.cStr() << "    " << bd2.cStr()<< endl;
		bd1.add(&bd2);
	}
	cout << bd1.cStr() << "    " << bd2.cStr() << endl;
	for (int i = 0; i < 1000; i++) {
		cout << bd1.cStr() << "    " << bd2.cStr() << endl;
		bd1.subtract(&bd2);
	}
	cout << bd1.cStr() << "    " << bd2.cStr() << endl;*/
	/*for (int i = 0; i < 100; i++) {
		cout << first.cStr() << endl;
		BigInt ab(i);
		first.multiply(&second);
	}
	cout << first.cStr() << endl;;
	for (int i = 0; i < 100; i++) {
		cout << first.cStr() << endl;
		BigInt ab(i);
		first.divide(&second);
	}
	cout << first.cStr() << endl;*/
	/*cout << first.cStr() << endl;
	for (int i = 0; i < 1000; i++) {
		cout << first.cStr() << endl;
		first.add(&second);
	}
	cout << first.cStr() << endl;
	for (int i = 0; i < 1000; i++) {
		cout << first.cStr() << endl;
		first.subtract(&second);
	}
	cout << first.cStr() << endl;*/
}