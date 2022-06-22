// laba3.1.7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <forward_list>
#include <string>
#include <fstream>

const int HASHSIZE = 128;

typedef unsigned long long int uint;
void hashtubl(std::string name1, std::string name2);

uint fromsistem(std::string str, const int& base) {
    uint num = 0;
    int i = 0;
    int numb = 0;
    int len = str.length();
    while (i < len) {
        
        
        numb= (isdigit(str[i]) ? (str[i] - '0') : isupper(str[i]) ?\
             (str[i] - 'A' + 10) : (str[i] - 'a' + 36));
        
        num = num * base + numb;
        i++;
    }
    return num;
}
int main()
{
    hashtubl("C:\\jjj\\laba7in.txt", "C:\\jjj\\laba7out.txt");
    std::cout << "Hello World!\n";
}

bool makedefine(const std::string&str, std::pair<std::string, std::string>&pair) {
    pair.first = "";
    pair.second = "";
    std::string shablon = "#define F S"; int i = 0; int j = 0;
    while (i != str.length() && j != shablon.length()) {
        if (shablon[j] == 'F') {
            j++;
            while ((isdigit(str[i]) || isalpha(str[i])) && i != str.length()) {
                pair.first += str[i]; i++;
            }

        }
        else if (shablon[j] == 'S') {
            j++;
            while ((isdigit(str[i]) || isalpha(str[i])) && i != str.length()) {
                pair.second += str[i]; i++;
            }

        }
        else if (str[i] == shablon[j]) {
            i++; j++;
        }
        else
            return 0;
    }
    if (i == str.length() && j == shablon.length())
        return 1;
    return 0;
}

class read {
    std::ifstream in;
    std::ofstream out;
    char c = '\0';
    bool flag = 1;
public:
    read(const std::string name1, const std::string name2) {
        in.open(name1);
        out.open(name2);
    }
    ~read() {
        in.close();
        out.close();
    }
    friend read& operator>>(read& potok, std::string& str);
    friend read& operator<<(read& potok, const std::string& str);
};

read& operator<<(read& potok, const std::string& str) {
    potok.out << str<< potok.c;
    return potok;
}
read& operator>>(read& potok, std::string& str) {
    char c = potok.in.get();
    str = "";
    bool def = 0;
    if (c == '#'&&potok.flag) {
         do {
            str += c;
            c = potok.in.get();
         }         while (isalpha(c)||isdigit(c));
        if (str == "#define") {
            while ((c != '\n' && c != -1)) {
                if (c == ' ') {
                    str += c;
                    while (c == ' ') {
                        c = potok.in.get();
                    }
                }
                str += c;
                c = potok.in.get();
                 
            }
        }
        else {
            potok.flag = 0;
            potok.out << '#';
            str.erase(0, 1);
        }

    }     
    else {
        potok.flag = 0;
        while (!isdigit(c) && !isalpha(c)&&c != -1) {
            potok.out << c;
            c = potok.in.get();
        }
        while (c != -1 && (isdigit(c) ||isalpha(c))) {
            str += c;
            c = potok.in.get();
        }
    }
    if (c == -1)
        c = '\0';
   potok.c=c;
    
    return potok;
}
struct Hash {
    std::forward_list<std::pair<std::string, std::string>> hash[HASHSIZE];
    void to_hash(const std::pair<std::string, std::string>&pair) {
        uint num = 0;
        num = fromsistem(pair.first, 62);
        hash[num % HASHSIZE].insert_after(hash[num % HASHSIZE].before_begin(), pair);
    }
    void remake(std::string& word) {
       uint num = fromsistem(word, 62);
        for (auto i = hash[num % HASHSIZE].cbegin(); i != hash[num % HASHSIZE].cend(); i++) {
            if (i->first == word) {
                word = i->second;
                break;
            }
        }
    }
 };
void hashtubl(std::string name1, std::string name2) {
     
    std::string word = "";
    std::pair<std::string, std::string> pair;
    Hash table;
    read potok(name1, name2); 
    potok >> word;
    while (word!=""){
        if (makedefine(word, pair)) {
            table.to_hash(pair);
            potok << word;
        }
        else {
           table.remake(word);
            potok << word;
        }
        potok >> word;
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
