#pragma once
#include<vector>
#include <iostream>
#include <string>
#include <stdarg.h>
#include <stdio.h>
#include<fstream>

bool SerfSubstring(const std::string& substr, std::string& str);

std::vector<std::string> poisk(bool (*Serfing)(const std::string& substr, std::string& str), const std::string&substr, int arg, ...);

