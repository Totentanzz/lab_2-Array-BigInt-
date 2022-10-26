#define _CRT_SECURE_NO_WARNINGS

#include "Number.h"
#include "BigInt.h"
#include "Stack.h"
#include "Queue.h"
#include "BigDecimal.h"
#include <iostream>

using namespace std;

void main() {
	long long one = 8446744073709551617;
	long long two = 8446744073709551618;
	BigInt first(one);
	BigInt second(two);
	char ab1[60] = "8446744073709551618.8446744073709551618";
	char ab2[50] = "999876535110876535110870144.0036931448099000"; 
	BigDecimal bd1(ab1);
	BigDecimal bd2(ab2);
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
		first.multiply(&second);
	}
	cout << first.cStr() << endl;
	for (int i = 0; i < 100; i++) {
		cout << first.cStr() << endl;
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