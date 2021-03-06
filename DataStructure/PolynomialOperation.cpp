// ConsoleApplication126.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
using namespace std;

void menu();
class Polynomial;
class Term { //which saves each term's exp and coef
	friend Polynomial;
private:
	int exp;
	float coef;
};
class Polynomial{
	friend Term;
private:
	Term *termarray; // Term array for Polynomial
	int capacity; // Max length for Polynomial
	int terms; // Num of the terms which has coef != 0
public:
	Polynomial(); // creater
	~Polynomial(); // Destructor
	void sort();  // Sorting function
	void printing(); // Printing function
	void newterm(int theExp, float theCoef);
	Polynomial add(Polynomial b); // Add function
	Polynomial sub(Polynomial b); // Minus function
	Polynomial mul(Polynomial b); // multiply function
};
Polynomial::Polynomial()
{
	termarray = new Term[4]; // Early length for Polynomial is 4
	capacity = 4; // Indicates the number of terms that can be entered in the future.
	terms = 0;  // Indicates the number of terms that entered in now.
	return;
}
Polynomial::~Polynomial()
{
	delete[] termarray;
	return;
}
void Polynomial::newterm(int theExp, float theCoef)
{
	if (terms == capacity) //if the polynomial is full, extend the size
	{
		Term *temparray;
		capacity *= 2;
		temparray = new Term[capacity];
		for (int i = 0 ; i < terms; i++)
		{
			temparray[i].coef = termarray[i].coef;
			temparray[i].exp = termarray[i].exp;
		}
		termarray = new Term[capacity];
		for (int i = 0; i < terms; i++)
		{
			termarray[i].coef = temparray[i].coef;
			termarray[i].exp = temparray[i].exp;
		} //moving data to new Polynomial
		delete[] temparray;
	}
	termarray[terms].coef = theCoef;
	termarray[terms++].exp = theExp; //make a new term
	return;
}
void Polynomial::sort() //Sort polynomial in exp descending order
{
	int max_exp;
	int max_index= 0;
	float temp_coef = 0;
	for(int i = 1 ; i < terms ; i++)
	{
		max_exp = termarray[i].exp;
		max_index = i;
		for (int j = i; j < terms; j++)
		{
			if (termarray[j].exp > max_exp)
			{
				max_exp = termarray[j].exp;
				max_index = j;
			}
		}
		if (i != max_index)
		{
			int temp_exp = termarray[i].exp;
			float temp_coef = termarray[i].coef;

			termarray[i].exp = termarray[max_index].exp;
			termarray[i].coef = termarray[max_index].coef;

			termarray[max_index].exp = temp_exp;
			termarray[max_index].coef = temp_coef;

		}
	}
}
void Polynomial::printing()
{
	cout << "다항식 : " << termarray[0].coef << " X^" << termarray[0].exp << "\t"; // 첫번째 항만 출력
	for (int i = 1; i < terms; i++)
	{
		if (termarray[i].coef > 0)
			cout << "  +" << termarray[i].coef << " X^" << termarray[i].exp << "\t"; // 항의 계수가 양수인 경우
		else
			cout << "  " << termarray[i].coef << " X^" << termarray[i].exp << "\t"; // 항의 계수가 음수인 경우
	}
	return;
}
Polynomial Polynomial::add(Polynomial b) // add polynomial b to polynomial a
{
	Polynomial c; // c is the result polynomial for add b to a
	sort();
	b.sort();
	int apos = 0 , bpos = 0;
	while ((apos < terms) && (bpos < b.terms)) //do while one of the polynomial's term is over
	{
		if (termarray[apos].exp == b.termarray[bpos].exp)
			c.newterm(termarray[apos].exp, termarray[apos++].coef + b.termarray[bpos++].coef);
		else if (termarray[apos].exp > b.termarray[bpos].exp)
			c.newterm(termarray[apos].exp, termarray[apos++].coef);
		else
			c.newterm(b.termarray[bpos].exp, b.termarray[bpos++].coef);
	}
	for (; apos < terms; apos++) //if the while loop break because of polynomial b
		c.newterm(termarray[apos].coef, termarray[apos].exp);

	for (; bpos < b.terms; bpos++) // or a
		c.newterm(b.termarray[bpos].coef, b.termarray[bpos].exp);

	return c;
}
Polynomial Polynomial::sub(Polynomial b)
{
	Polynomial c; // c is the result polynomial for subtraction b from a
	sort();
	b.sort();
	int apos = 0, bpos = 0;
	while ((apos < terms) && (bpos < b.terms))  //do while one of the polynomial's term is over
	{
		if (termarray[apos].exp == b.termarray[bpos].exp)
			c.newterm(termarray[apos].exp, termarray[apos++].coef - b.termarray[bpos++].coef);
		else if (termarray[apos].exp > b.termarray[bpos].exp)
			c, newterm(termarray[apos].exp, termarray[apos++].coef);
		else
			c.newterm(b.termarray[bpos].exp, b.termarray[bpos++].coef);
	}
	for (; apos < terms; apos++) //if the while loop break because of polynomial b
		c.newterm(termarray[apos].coef, termarray[apos].exp); 

	for (; bpos < b.terms; bpos++) // or a
		c.newterm(b.termarray[bpos].coef, b.termarray[bpos].exp);

	return c;
}
Polynomial Polynomial::mul(Polynomial b)
{
	Polynomial c, d;
	// make a polynomial c for each term of polynomial a and add c to d
	// d is the result polynomial for multiply polynomial a and b
	sort();
	b.sort();
	for (int apos = 0; apos < terms; apos++)
	{
		for (int bpos = 0; bpos < b.terms; bpos++)
			c.newterm(termarray[apos].exp + b.termarray[bpos].exp, termarray[apos].coef * b.termarray[bpos].coef);
		d = d.add(c);
	}
	return d;
}
int main(void)
{
	Polynomial A, B, C;

	int size = 0, EXP = 0;
	float COEF = 0;
	cout << "Number of terms in polynomial A : ";
	cin >> size;

	for (int i = 0; i < size; i++)
	{
		cout << "Coefficients and exponents of the " << i <<" term in polynomial A: ";
		cin >> COEF >> EXP;
		A.newterm(EXP, COEF);
	}
	cout << "Number of terms in polynomial B : ";
	cin >> size;

	for (int i = 0; i < size; i++)
	{
		cout << "Coefficients and exponents of the " << i << " term in polynomial B: ";
		cin >> COEF >> EXP;
		B.newterm(EXP, COEF);
	}
	cout << "============= Menu =============\n 1.add\n 2.subtraction\n 3.multiply\n";
	cin >> size;

	if (size == 1)
		C = A.add(B);
	else if (size == 2)
		C = A.sub(B);
	else if (size == 3)
		C = A.mul(B);
	else
		C = A.div(B);
	cout << "\nresult : ";
	C.printing();

	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
