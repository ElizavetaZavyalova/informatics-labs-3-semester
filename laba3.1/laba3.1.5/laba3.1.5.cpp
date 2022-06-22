// laba3.1.5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdarg.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

std::string summa(int base, int count, ...);
int main()
{
    std::string s1 = "001";
    std::string s2 = "00000000000000000000000000000000000000000034";
    std::string s3 = "345";
    std::cout << summa(10, 3,  s1, s2, s3);
}


std::string sum(const std::string& num1, const int& base, const std::string& num2) {
    std::string resault = "";
    std::string max = "";
    std::string min = "";
    int num = 0;
    char cifra = ' ';
    if (num1.length() > num2.length()) {
        max = num1;
        min = num2;
    }
    else {
        max = num2;
        min = num1;
    }
    max = '0' + max;
    int j = max.length() - 1;
    for (int i = min.length() - 1; i >= 0; i--) {
        isdigit(max[j]) ? (cifra= max[j] - '0') : (cifra= max[j] - 'A' + 10);
        num += cifra;
        isdigit(min[i]) ? (cifra= min[i] - '0') : (cifra= min[i] - 'A' + 10);
        num += cifra;
        cifra = num % base;
        (cifra < 10) ? (cifra += '0') : (cifra = cifra + 'A' - 10);
        resault = cifra + resault;
        num /= base;
        j--;
    }
    isdigit(max[j]) ? (cifra = max[j] - '0') : (cifra = max[j] - 'A' + 10);
    cifra += num;
    (cifra < 10) ? (cifra += '0') : (cifra = cifra + 'A' - 10);
    max.erase(j, max.length()-j );
    max += cifra;
    resault = max + resault;
    
    while(resault[0] == '0'&&resault.length()!=1){
        resault.erase(0, 1); 
    }
    
    return resault;
}

std::string summa(int base, int count, ...) {

    va_list arg;
     
    va_start(arg, count);
    int i = 1;
    std::string resault = "";
    resault=va_arg(arg, std::string);
     
    while (i < count) {

        resault = sum(resault, base, va_arg(arg, std::string));

        i++;
    }
    va_end(arg);
    return resault;
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
