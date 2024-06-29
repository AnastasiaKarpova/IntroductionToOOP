#include <iostream>
#include "String.h"
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define delimiter "\n--------------------------------------\n"




//#define CONSTRUCTORS_CHECK
#define OPERATOR_PLUS_CHECK
//#define CALLING_CONSTRUCTORS
void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK

	String str1; //Default Constructor
	str1.print();

	//String str2 = 8; //Conversion from 'int' to 'String'
	String str2(8); //Explicit int constructor (Single-argument 'int' constructor
	str2.print();

	String str3 = "Hello";
	str3 = str3;
	str3.print();

	String str4 = "World";
	str4.print();

	cout << str3 << endl;
	cout << str4 << endl;

	//String str5 = str3 + str4;
	String str5;
	str5 = str3 + str4; //Copy assignment
	str5.print();
	cout << str5 << endl;
#endif // DEBUG

#ifdef OPERATOR_PLUS_CHECK
	String str1 = "Hello"; 
	String str2 = "World";

	cout << delimiter << endl;
	String str3 = str1 + str2;
	cout << str3 << endl;
	cout << delimiter << endl;

	cout << str1 << endl;
	cout << str2 << endl;
#endif // OPERATOR_PLUS_CHECK

#ifdef CALLING_CONSTRUCTORS
	String str1; //Default Constructor
	str1.print();

	//String str2 = 8; //Single Argument constructor 'int'
	                 //explicit constructor так вызвать не возмодно
	String str2(8); //explicit constructor можно вызвать только так
	str2.print();

	String str3 = "Hello"; // Single Argument constructor 'char'
	str3.print();

	String str4(); //
	//здесь не вызываетс€ никакой конструктор и не создаетс объект
	//здесь объ€влетс€ функци€ str4(), котора€ не принимает никаких параметров
	// и возвращает значение типа 'String'
	//“.е. ткаким образом Defaul Constructor вызвать невозможно
	//str4.print();
	//”сли нужно €вно вызвать Defaul Constructor, это делаетс€ следующим образом:
	String str5{}; //явный вызов конструктора по умолчанию
	str5.print();
	
	//String str6 = str3; //CopyConstructor
	//String str6 (str3); //CopyConstructor
	String str6{ str3 }; //CopyConstructor
	str6.print();
	//—ледовательно, абсолютно любой конструктор можно вызвать при помощи круглых () или фигурных скобок {}

#endif // CALLING_CONSTRUCTORS


}