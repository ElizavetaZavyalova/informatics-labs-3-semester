#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <functional>

void parser(std::string interpritatorname, std::string set = "C:\\jjj\\laba8saves.txt");
class interpreter;
class settings;
class reading;
class reading{
    std::ifstream in;
public:
    reading(std::string inter) {
        in.open(inter);
    }
    ~reading() {
        in.close();
    }
    friend reading& operator>> (reading& potok, char& c);
    friend reading& operator>> (reading& potok, interpreter& str);
};

 

class settings {

    std::ifstream in;
    std::ofstream out;

public:
    settings(std::string name1 = "C:\\jjj\\laba8saves.txt") {
        in.open(name1);

    }
    ~settings() {
        if (in.is_open())
            in.close();
    }
    friend settings& operator>> (settings& potok, char& c);
    friend settings& operator<< (settings& potok, const char& c);
    friend settings& operator>> (settings& potok, std::map<std::string, std::string>& settings);
    friend settings& operator<< (settings& potok, const std::map<std::string, std::string>& settings);

};

class interpreter {
    std::map<std::string, std::string> syntax{
    {"write",""}, {"read", ""}, {"doopvn",""}, {"doop2v", ""},{"doopnv",""}, {"doop2n", ""},\
    {"doopw", ""}, {"doopr", ""}
    };
    int maxlen = 32 * 3 + 10;
    std::string ection = "";
    std::string key[3] = { "", "", "" };
    std::string opiration = "";
    int base = 0;
    int num[2] = { 0, 0 };
    bool unarnobinar = 0;
    std::string ruvn = "=";
    std::string write = "in";
    std::string read = "output";
    std::map<std::string, int> variable;
   
    std::map<std::string, std::function<int( int&, int&)>> functionbinar;
    
public:
    interpreter(std::string set = "C:\\jjj\\laba8saves.txt");
    void parser(const std::string interpritatorname);
    bool iscorrect(const std::string comand);
    void remake();
    void variablecreate(const int count = 3);
    friend reading& operator>> (reading& potok, interpreter& str);
    void repoisk();

};

std::string tosistem(int num, const int& base);

int fromsistem(std::string str, const int& base);
