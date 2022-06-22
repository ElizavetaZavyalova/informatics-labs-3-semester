// laba3.1.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdarg.h>
#include <math.h>
#include <stdio.h>
#include <map>


struct point {
	float x = 0;
	float y = 0;
	bool operator==(const point& pos)const {
		if ((this->x == pos.x) && (this->y == pos.y))
			return 1;
		return 0;
	}
	 
};

struct vec {
	float x = 0;
	float y = 0;
	bool operator==(const point& pos)const {
		if ((this->x == pos.x) && (this->y == pos.y))
			return 1;
		return 0;
	}
	void create(const point&first, const point&last) {
		x = last.x - first.x;
		y= last.y- first.y;
	}
};

bool isitconvex(int count, ...);

int main()
{
	point pos[4];
	pos[0].x = 1;
	pos[0].y = 1;
	pos[1].x = 2;
	pos[1].y = 1;
	pos[2].x = 2;
	pos[2].y = 2;
	pos[3].x = 1;
	pos[3].y = 2;
	if (isitconvex(4, pos[2], pos[0], pos[1], pos[3]))
		std::cout << "corvex";
	else
	std::cout << "no corvex";
}


bool isitconvex(int count, ...) {

	va_list arg;
	bool flag = 1;
	va_start(arg, count);  
	point pos[3];
	point pos0[2];
	 
	for (int i = 0; i < 3; i++) {
		pos[i] = va_arg(arg, point);
	}
	 
	pos0[0] = pos[0];
	pos0[1] = pos[1];
	vec v[2];
	float lastresault = 0;
	float resault = 0;
	int i = 3, k=0;
	while (i < count+2) {
		v[0].create(pos[0], pos[1]);
		v[1].create(pos[1], pos[2]);
		resault = v[0].x * v[1].y- v[0].y * v[1].x;
		for (int j = 0; j < 2; j++) {
			pos[j] = pos[j + 1];
		}
		if(i<count)
		pos[2] = va_arg(arg, point);
		else {
			pos[2] = pos0[k]; k++;
		}
		if ((resault > 0 && lastresault < 0) || (lastresault > 0 && resault < 0))
			flag = 0;
		lastresault = resault;
		i++;
	} 
	 
	va_end(arg);
	if (flag)
		return 1;
	return 0;

	 
	 
	 
	 
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
