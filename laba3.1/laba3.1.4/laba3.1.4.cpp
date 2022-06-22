// laba3.1.4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cctype>
#include <string>
#include <fstream>

int fromsistem(std::string str, int base);

void writeinfile(std::string inname, std::string outname);


int main(int argc, char* argv[])
{
	std::string str1(argv[1]);
	std::string str2 = "C:\\jjj\\laba4out.txt";

	try {
		writeinfile(str1, str2);
		std::cout << "Ok";
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
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

 



int fromsistem(std::string str, int base) {
	int num = 0;
	int i = 0;
	int r = 0;
	int len = str.length();
	while (i < len) {

		r = (isdigit(str[i]) ? (str[i] - '0') : (str[i] - 'A' + 10));
		if (r >= base)
			throw(std::exception("not correct base"));

		num = num * base + r;
		i++;
	}
	return num;
}

void writeinfile(std::string inname, std::string outname) {

	std::ifstream in;
	std::ofstream out;
	int maxbase = 2;
	int base = 2;
	std::string num = "";
	in.open(inname);
	out.open(outname);
	char c = ' ';
	c = in.get();

	while (c != -1) {
		while ((isupper(c) || isdigit(c))&&c!=-1) {
			num = num + c;
			isdigit(c) ? (base = c - '0' + 1) : (base = c - 'A' + 11);
			if (base > maxbase)
				maxbase = base;
			c = in.get();

			 
		}
		while (isspace(c)&&c!=-1) {
			c = in.get();
			 
		}
		if (num != "") {
			out << maxbase << "->" << fromsistem(num, maxbase) << '\n';
			 
			base = 2;
			maxbase = 2;
			num = "";
		}
		if (!isdigit(c) && !isupper(c) && c != -1 && !isspace(c))
		{
			in.close();
			out.close();
			throw (std::exception("no correct simvol"));


		}

	}
	in.close();
	out.close();

}

