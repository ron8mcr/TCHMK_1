#pragma once
#include <iostream>
typedef unsigned int digit;
typedef long long int longDigit;
typedef unsigned long long int unsLongDigit;
#define BASE 4294967296 // 2^32
//#define forVS // если компилируется в Visual Studio
#define forGCC

#define DIVISION_BY_ZERO 1

class bigInt
{
public:
	bigInt();
	bigInt(const char* string);
	bigInt(const bigInt &rhv);
	bigInt(long long int value);
	~bigInt();

	char* getString();
	bool getFromTextFile(const char* filename);
	bool saveToTextFile(const char* filename);
	bool saveToBinFile(const char* filename);
	bool getFromBinFile(const char* filename);


	bigInt& operator=(const bigInt& rhv);
	bigInt& operator=(const longDigit value);

	bigInt operator+(const bigInt& right);
	bigInt operator-() const;
	bigInt operator-(const bigInt& right);
	bigInt operator*(const bigInt& right);
	bigInt operator/(const bigInt& right);
	bigInt operator%(const bigInt& right);
	bigInt operator^(const bigInt& right);

	bigInt operator+=(const bigInt& right);
	bigInt operator-=(const bigInt& right);
	bigInt operator*=(const bigInt& right);
	bigInt operator/=(const bigInt& right);
	bigInt operator%=(const bigInt& right);

	bigInt operator++();
	bigInt operator++(int);
	bigInt operator--();
	bigInt operator--(int);

	int operator>(const bigInt& B);
	int operator>=(const bigInt& B);
	int operator<(const bigInt& B);
	int operator<=(const bigInt& B);
	int operator==(const bigInt& B);
	int operator!=(const bigInt& B);

	friend std::ostream& operator<<(std::ostream &out, bigInt A);
	friend std::istream& operator>>(std::istream &is, bigInt &A);
private:
	int _size; // можно было бы взять unsigned long long int, но у оператора new есть ограничение на максимальный размер массива 0x7fffffff байт. Так что это, по сути, и ограничивает максимальную длинну числа
	digit* _digits;
	int _sign;

	char* _viewNumber();
	void _setSize(int size);
	digit & operator[](int i);
	digit operator[](int i) const;
	digit _normalize(longDigit d, digit &norm);
	void _copy(const bigInt &rhv);
	void _delLeadZeros();
	longDigit _cmp(const bigInt& B);
	void _shiftLeft(int s);

	friend const bigInt _simpleSum(const bigInt& left, const bigInt& right);
	friend const bigInt _simpleMul(const bigInt& A, const bigInt& B);
	friend const bigInt _divividing(const bigInt& A, const bigInt& B, bigInt &remainder);
	friend const bigInt _divColumn(const bigInt& A, const bigInt& B, bigInt &remainder);
	friend const bigInt _divBinSearch(const bigInt& A, const bigInt& B, bigInt &remainder);
};
const bigInt _simpleSum(const bigInt& left, const bigInt& right);
const bigInt _simpleMul(const bigInt& A, const bigInt& B);
const bigInt _divividing(const bigInt& A, const bigInt& B, bigInt &remainder);
const bigInt _divColumn(const bigInt& A, const bigInt& B, bigInt &remainder);
const bigInt _divBinSearch(const bigInt& A, const bigInt& B, bigInt &remainder);
