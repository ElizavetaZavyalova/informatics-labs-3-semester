// laba3.1.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

 
#include<vector>
#include <iostream>
#include <string>
#include <stdarg.h>
#include <stdio.h>
#include<fstream>

bool SerfSubstring(const std::string& substr, std::string& str);

std::vector<std::string> poisk(bool (*Serfing)(const std::string& substr, std::string& str), const std::string& substr, int arg, ...);



int main()
{
	std::string str1 = "C:\\jjj\\repit.txt";
	std::string str2 = "C:\\jjj\\read.txt";
	std::string str3 = "C:\\jjj\\readme.txt";
	std::string substr = "HH \nHui";

	std::vector<std::string> colection;
	try {
		colection = poisk(SerfSubstring, substr, 3, str1, str2, str3);
		for (auto i = colection.cbegin(); i != colection.cend(); i++) {
			std::cout << (*i) << '\n';
		}
		std::cout << "Ok";
	}
	catch (const std::string exept) {
		std::cout << exept;
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.


bool SerfSubstring(const std::string& substr, std::string& str) {
	int i = 0; int j = 0;  
	if (substr == "")
		return 1;
	while (i <= str.length()) {
		if (str[i] != substr[0]) {
			i++;
		}
		 
		else {
			while (j < substr.length()&&i+j<str.length()) {
				if (str[i + j] == substr[j]) {
					j++;  
				}
				else {
					break;  
				}
			}
			 
			if (j == substr.length()) {
				return 1;
			}
			j = 0; i++;
		}
		 
	 }
	if (str.length() > substr.length())
		str.erase(0, str.length()-(substr.length() - 1));
	return 0;
		
}

std::vector<std::string> poisk(bool (*Serfing)(const std::string& substr, std::string& str), const  std::string& substr, int file, ...) {
	va_list arg;
	int j = 1;
	std::vector<std::string> colection;
	va_start(arg, file);
	int i = 0;
	int n = 3 * substr.length();
	char* buf = new char[n];
	buf[n - 1] = '\0';

	while (i < file) {

		std::string name = va_arg(arg, std::string);
		std::ifstream file;
		file.open(name);
		 
		std::string inter = "";
		 
		while (!file.eof()) {
			file.read(buf, n-1);
			std::string str(buf);
			inter = inter+str;
			  
				 
				if (Serfing(substr, inter)) {
					colection.resize(j);
					(colection)[j - 1] = name;
					j++;
					break;
				}
			
		}
		i++;
		file.close();	 

	}
	delete[] buf;
	va_end(arg);
	return colection;
}