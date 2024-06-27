#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\t----------------------------------------\t"

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right);

class Fraction
{
	int integer; //целая часть
	int numenator; //числитель
	int denominator;//знаменатель
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numenator()const
	{
		return numenator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numenator(int numenator)
	{
		this->numenator = numenator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0) denominator = 1;
		this->denominator = denominator;
	}

	//constractors
	Fraction()
	{
		integer = 0;
		numenator = 0;
		set_denominator(1);
		cout << "DefaultConstractor:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numenator = 0;
		set_denominator(1);
		cout << "SingleArgumentConstructor:\t\t" << this << endl;
	}
	Fraction(double decimal)
	{
		//decimal - десятичный
		//decimal += 1e-10;
		integer = decimal; //сохраняем целую часть;
		decimal -= integer; //убираем целую часть из десятичной дроби
		denominator = 1e+9; //записываем максимально возможный знаменатель
		numenator = decimal * denominator + .5;
		reduce();
		cout << "DoubleConstructor:\t" << this << endl;

	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numenator = numenator;
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(int integer = 0, int numenator = 0, int denominator = 1)
	{
		set_integer(integer);
		set_numenator(numenator);
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numenator = other.numenator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}

	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numenator = other.numenator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t\t" << this << endl;
		return *this;
	}
	
	Fraction& operator*=(Fraction& other)
	{
		return *this = *this * other;
	}
	Fraction& operator/=(Fraction& other)
	{
		return *this = *this / other;
	}
	// type-cast operators:
	operator int()
	{
		return integer;
	}
	// Methods
	Fraction& to_improper()
	{
		numenator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()
	{
		integer += numenator / denominator;
		numenator %= denominator;
		return *this;
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		swap(inverted.numenator, inverted.denominator);
		return inverted;
	}
	Fraction& reduce()
	{
		int more, less, rest;
		if (numenator > denominator) more = numenator, less = denominator;
		else less = numenator, more = denominator;
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; //GCD - Greatest Common Divisor
		numenator /= GCD;
		denominator /= GCD;
		return *this;
	}
	void print()const
	{
		if (integer) cout << integer;
		if (numenator != 0)
		{
			if (integer) cout << "(";
			cout << numenator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0) cout << 0;
		cout << endl;
	}
};

Fraction operator*(Fraction left, Fraction right)
{
	/*left.to_improper();
	right.to_improper();

	Fraction result;
	result.set_numenator(left.get_numenator() * right.get_numenator());
	result.set_denominator(left.get_denominator() * right.get_denominator());
	return result;*/

	/*Fraction result
	(
		left.get_numenator() * right.get_numenator(),
		left.get_denominator() * right.get_denominator()
	);
	result.to_proper();
	return result;*/

	return Fraction
	(
		left.get_numenator() * right.get_numenator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
Fraction operator/(const Fraction& left, const Fraction& right)
{
	return left * right.inverted();
}

// Comparison operators:
bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numenator() * right.get_denominator() == right.get_numenator() * left.get_denominator();
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numenator() * right.get_denominator() >
		right.get_numenator() * left.get_denominator();
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numenator() * right.get_denominator() <
		right.get_numenator() * left.get_denominator();
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	return !(left < right);
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return !(left > right);
}

std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	return os << "Numerator" << obj.get_numenator() << "\tDenominator" << obj.get_denominator();
}

std::istream& operator>>(std::istream& is, Fraction& obj)
{
	const int SIZE = 256;
	char buffer[SIZE] = {};
	is >> buffer;

	int numbers[3] = {};
	int n = 0;
	const char delimiters[] = " \()";
	for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
		numbers[n++] = atoi(pch); // Функция atoi() принимает строку, и возвращает целочисленный аналог этой строки,
	//т.е., строку преобразует в число.
	for (int i = 0; i < n; i++) cout << numbers[i] << "\t"; cout << endl;

}
//#define CONSTRUCTORS_CHECK;
//#define ARITHMETICAL_OPERATORS_CHECK;
//#define IOSTREAM_CHECK;
//#define CONVERSIONS_FROM_OTHER_TO_CLASS
//#define CONVERSIONS_HOME_WORK

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK 
	Fraction A;  //Default constraction
	A.print();

	Fraction B = 5; //Single-argument constructor
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();
#endif

#ifdef ARITHMETICAL_OPERATORS_CHECK
	Fraction A(2, 3, 4);
	A.print();
	Fraction B(3, 4, 5);
	B.print();
	//A.to_improper().print();
	//A.to_proper().print();

	/*Fraction C = A / B;
	C.print();*/

	A *= B;
	A.print();

	A /= B;
	A.print();
#endif

#ifdef IOSTREAM_CHECK
	//cout << (Fraction(1, 2) == Fraction(5, 10)) << endl;
	Fraction A(3, 5);
	cout << A << endl;

	Fraction B;
	cout << "Введите простую дробь: "; cin >> B;
	cout << B << endl;
#endif

#ifdef CONVERSIONS_FROM_OTHER_TO_CLASS
	Fraction A = (Fraction)5; //Conversion from less to more
	                //Sindle-argument constructor
	cout << A << endl;

	cout << delimiter << endl; 

	Fraction B;     //Default constructor
	cout << delimiter << endl; 
	B = Fraction (8);          //Conversion from less to more (from 'int' to 'Fraction')
	cout << B << endl;

	cout << delimiter << endl;
#endif

#ifdef CONVERSIONS_HOME_WORK
	Fraction A = 3.333; //Conversion from
	cout << A << endl;
#endif

	Fraction A(2, 3, 4);
	cout << A << endl;

	int a = A;
	cout << a << endl;
}