#include "laba1.h"
bool SerfSubstring(const std::string& substr, std::string& str) {
	
	return 1;
}

std::vector<std::string> poisk(bool (*Serfing)(const std::string& substr, std::string& str), const  std::string& substr, int file, ...) {
	va_list arg;
	int j = 1;
	std::vector<std::string> colection; 
	va_start(arg, file);
	int i = 0;
	while (i < file) {

		std::string name=va_arg(arg, std::string);
		std::ifstream file;
		file.open(name);
		int j = 0;
		char c = ' ';
		std::string inter = "";
		while (c != -1) {
			c = file.get();
			inter = inter + c;
			if (inter.length() == substr.length()) {
				 
				if (Serfing(substr, inter)) {
					colection.resize(j);
					(colection)[j - 1] = name;
					j++;

				}
				i++;
					 
				 
			}
		}
		file.close();
		 
		if (Serfing(substr, name)) {
			colection.resize(j);
			(colection)[j-1] = name;
			j++;
			 
		}
		i++;
	}
	va_end(arg);
	return colection;
}