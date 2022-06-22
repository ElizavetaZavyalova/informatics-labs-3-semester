#include "laba4.h"
 

 

int fromsistem(std::string str, int base) {
	int num=0;
	int i = 0;
	int r = 0;
	int len = str.length();
	while (i<len) {
		 
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
			while (isupper(c)||isdigit(c)) {
				num = num + c;
				isdigit(c) ? (base = c - '0'+1) : (base = c - 'A' + 11);
				if (base > maxbase)
					maxbase = base;
				c = in.get();
				 
				if (c == -1)
					break;
			}
			while (isspace(c)) {
				c = in.get();
				if (c == -1)
					break;
			}
			if (num != "") {
				out << maxbase << ' ' << fromsistem(num, maxbase) << '\n';
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
