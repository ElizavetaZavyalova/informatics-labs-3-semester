// laba3.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "laba4.h"
#include "laba6.h"
#include "laba1.h"
#include "laba3.h"
#include <string>
#include <exception>

/*int main(int argc, char*argv[])
{
	std::string str1 = "C:\\jjj\\repit.txt";
	std::string str2 = "C:\\jjj\\read.txt";
	std::string str3= "C:\\jjj\\readme.txt";
	std::string substr = "HHHui";

	std::vector<std::string> colection;
	try {
		colection=poisk(SerfSubstring, substr, 3, str1, str2, str3);
		std::cout << "Ok";
	 }
	catch (const std::string exept) {
	      std::cout<<exept;
	}
 
}*/

int main(int argc, char* argv[])
{   
	std::string str1(argv[1]);
	std::string str2 = "C:\\jjj\\laba4out.txt";
	 
	try {
		writeinfile(str1, str2);
		std::cout << "Ok";
	}
	catch (std::exception &ex) {
		std::cout << ex.what();
	}

}

/*int main(int argc, char* argv[]) {
	std::cout<<mnogochlen(10, 0, 5);


}*/

/*int main(int argc, char* argv[])
{
	std::string str1 = "C:\\jjj\\laba6.txt";
	std::string str2 = "C:\\jjj\\laba6trass.txt";

	try {
		interpritfile(str1, 1, str2);
		std::cout << "Ok";
	}
	catch (const std::string exept) {
		std::cout << exept;
	}

}*/

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
