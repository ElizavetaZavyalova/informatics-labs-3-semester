#pragma once
#include "laba4.h"
#include <map>
#include <cctype>
#include <iostream>
std::string tosistem(int num, const int &base);
void readbase(char& c, int& base, std::ifstream& in, char& key, std::ofstream& out, const bool& trass);
void stringsrav(const std::string& name, char& c, std::ifstream& in, std::ofstream& out, const bool& trass);
void interpritfile(const std::string& filename, const bool& trass, const std::string file = "");
void dotrass(const char& c, std::ofstream& out, const bool& trass);
int dooopiration(const int& first, const std::string& opiration, const int& second);