// laba3.1.6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <map>
#include <functional>

typedef unsigned int uint;

std::string tosistem(uint num, const int& base) {
    std::string str = "";
    do   {
        char remains = num % base;
        (remains < 10) ? (remains += '0') : (remains = remains - 10 + 'A');
        str = remains + str; num /= base;
    } while (num != 0);
    
    return str;
}

uint fromsistem(std::string str, const int&base) {
    uint num = 0;
    int i = 0;
    int r = 0;
    int len = str.length();
    while (i < len) {
        r = (isdigit(str[i]) ? (str[i] - '0') : (str[i] - 'A' + 10));
        if (r >= base||r<0)
            throw(std::exception("not correct base"));

        num = num * base + r;
        i++;
    }
    return num;
}

class wwod {
    std::ifstream in;
    std::ofstream out;
    bool trass = 0;
    int num = 0;
public:
    wwod(std::string name1, const bool trass=0, std::string name2="") {
        in.open(name1);
        this->trass = trass;
        if (trass)
            out.open(name2);
    }
    friend wwod& operator>> (wwod& potok, char& c);
    friend wwod& operator<< (wwod& potok, const char& c);
    friend wwod& operator>> (wwod& potok, std::string& ection);
    friend wwod& operator<< (wwod& potok, std::string& ection);
    ~wwod() {
        in.close();
        if (trass)
            out.close();
    }
};

wwod& operator<< (wwod& potok, const char& c) {
    if(potok.trass)
    potok.out << c;
    return potok;
}

wwod& operator>> (wwod& potok, char& c) {
    c = potok.in.get();
    int scobka = 0;
    while (c == '{' || c == '%' || isspace(c)) {
        if (c == '%') {
            while (c != '\n' && c != -1) {
                c = potok.in.get();
            }
            c = potok.in.get();
        }
        if (c == '{') {
            scobka++;
            while (scobka != 0) {
                c = potok.in.get();
                if (c == '}')
                    scobka--;
                if (c == '{')
                    scobka++;
                if (c == -1 || scobka < 0)
                    throw(std::exception("no korect{}"));
            }
            c = potok.in.get();
        }
        if (c == '}') {
            throw(std::exception("no korect{}"));
        }
        while (isspace(c))
            c = potok.in.get();
    }
    return potok;
}

wwod& operator>> (wwod& potok, std::string& ection) {
    ection = "";
    char c = ' ';
    while (c!=-1&&c != ';' && ection.length() != 13) {
        potok >> c;
        if (c != -1)
        ection = ection + c;
    }
    return potok;
}

wwod& operator<< (wwod& potok, std::string& ection) {
    if (potok.trass) {
        potok.out << potok.num <<": " << ection << '\n'; potok.num++;
    }
    return potok;
}

bool iscorrect(const std::string& str1, const std::string str2, char* key, std::string& opiration, int& base) {
    int j = 0; int i = 0; int k = 0;
    while (i< str1.length() && j < str2.length()) {
        if (str2[j] == '.') {
            opiration = opiration + str1[i]; j++; i++;
            if (!isupper(str1[i])) {
                opiration = opiration + str1[i]; i++;
            }
        }
        else if (str2[j] == '_' && isupper(str1[i])) {
            key[k] = str1[i]; k++; j++; i++;
        }
        else if (str2[j] == ',') {
            j++;
            if (str1[i] == ',') {
                i++;
                if (str2[j] == '#') {
                    j++;
                    if (isdigit(str1[i])) {
                        base = base * 10 + str1[i] - '0'; i++;
                        if (isdigit(str1[i])) {
                            base = base * 10 + str1[i] - '0'; i++;
                        }
                    }
                }
            }
            else {
                j++; base = 10;
            }
        }
        else if (str1[i] == str2[j]) {
            i++; j++;
        }
        else
            return 0;
    }
    if (i == str1.length() && j == str2.length())
        return 1;
    else
        return 0;
}

void parser(std::string str1, bool trass = 0, std::string str2 = "") {
     
    std::string action = "";
    std::string numstr = "";
    std::map<char,  uint> variable;
    std::map<std::string, std::function<uint (const  uint&, const uint&)>> function{
    {"+", [](const uint& first, const uint& second) {return first | second; } },
    {"&", [](const uint& first, const uint& second) {return first & second; } },
    {"->", [](const uint& first, const uint& second) {return ~first | second; } },
    {"\\", [](const uint& first, const uint& second) {return ~first; } },
    {"<-", [](const uint& first, const uint& second) {return ~second | first; } },
    {"~", [](const uint& first, const uint& second) {return (~first | second) & (~second | first); } },
    {"<>", [](const uint& first, const uint& second) {return~((~first | second) & (~second | first)); } },
    {"+>", [](const uint& first, const uint& second) {return ~(~first | second); } },
    {"?", [](const uint& first, const uint& second) {return ~(first & second); } },
    {"!", [](const uint& first, const uint& second) {return ~(first | second); } },
    };
    char key[3] = { ' ',' ',' ' };
    std::string opiration = "";
    int base = 0;
    wwod potok(str1, trass, str2);
    try {
       
        potok >> action;
        while (action != "") {
            if (iscorrect(action, "read(_,#);", key, opiration, base)) {
                if (base < 2 || base>36)
                    throw(std::exception("no correct base"));
                std::cin >> numstr;
                variable[key[0]] = fromsistem(numstr, base);
                potok << action;
                numstr = '=' + numstr;
                numstr = key[0] + numstr;
                potok << numstr;
                numstr = ""; base = 0;
            }
            else if (iscorrect(action, "write(_,#);", key, opiration, base)) {
                if (base < 2 || base>36)
                    throw(std::exception("no correct base"));
                numstr = tosistem(variable[key[0]], base);
                potok << action;
                std::cout << numstr <<'\n';
                numstr = '=' + numstr;
                numstr = key[0] + numstr;
                potok << numstr;
                base = 0;
                 numstr = "";

            }
            else if (iscorrect(action, "_:=_._;", key, opiration, base)) {
                if (variable.find(key[1]) == variable.cend() || variable.find(key[2]) == variable.cend()\
                    || function.find(opiration) == function.cend() || opiration == "\\")
                    throw(std::exception("not found elem or opiration"));
                variable[key[0]] = function[opiration](variable[key[1]], variable[key[2]]);
                potok << action;
                numstr = std::to_string(variable[key[0]]);
                numstr = '=' + numstr;
                numstr = key[0] + numstr;
                
                potok << numstr; opiration = "";

            }
            else if (iscorrect(action, "_:=._;", key, opiration, base)) {
                if (variable.find(key[1]) == variable.cend() || opiration != "\\")
                    throw(std::exception("not found elem or opiration"));
               variable[key[0]] = function[opiration](variable[key[1]], variable[key[2]]);
                potok << action;
                numstr = std::to_string(variable[key[0]]);
                numstr = '=' + numstr;
                numstr = key[0] + numstr;
                
                potok << numstr; opiration = "";
            }
            else
                throw(std::exception("not correct action"));
            potok >> action;
        }
    }
    catch (std::exception& ex) {
        std::cout << ex.what();
        numstr = (ex.what());
        potok << numstr;
    }
}

int main(int argc, char** argv)
{
     
    if (argc == 2) {
        std::string name1(argv[1]);
        parser(name1);
    }
    else if (argc == 4) {
        std::string trass(argv[2]);
        if (trass== "\\trass") {
            std::string name1(argv[1]);
            std::string name2(argv[3]);
            parser(name1, 1, name2);
        }
        else
            std::cout << "no orguments trass";
    }
    else
        std::cout << "no orguments";
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


 
 