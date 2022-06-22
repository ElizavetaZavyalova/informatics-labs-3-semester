#include "laba6.h"

std::ifstream& operator>> (std::ifstream& in, char&c) {
	c = in.get();
	while (isspace(c)||c=='#'||c=='{') {
		if (c == '#') {
			while (c != -1 && c != '\n') {
				c = in.get();
			}
		}
		if (c == '{') {
			int scobka = 1;
			while (c != -1 && c != '}') {
				c = in.get();
				(c == '{') ? (scobka++) : (c == '}') ? (scobka--) : (scobka);
				if (scobka < 0)
					throw(std::exception("no{"));
			}
			if (c == -1||scobka!=0) {
				throw("no}");
			}
			else
				c = in.get();
		}
		while (isspace(c)) {
			c = in.get();
		}
	}
	return in;
}

int dooopiration(const int&first, const std::string&opiration, const int&second) {
	if (opiration == "|")
		return ~first;
	else if(opiration == "+")
		return first|second;
	else if (opiration == "&")
		return  first & second;
	else if (opiration == "->")
		return ~first|second;
	else if (opiration == "<-")
		return ~second|first;
	else if (opiration == "~")
		return (~first|second)&(~second|first);
	else if (opiration == "<>")
		return ~((~first | second) & (~second | first));
	else if (opiration == "+>")
		return ~(~first | second);
	else if (opiration == "?")
		return ~(first&second);
	else if (opiration == "!")
		return ~(first | second);
	else
		throw("noopiration");

}

std::string tosistem(int num, const int& base) {
	std::string str = "";
	while (num != 0) {
		char remains = num % base;
		(remains < 10) ? (remains += '0') : (remains = remains - 10 + 'A');
		str = remains + str; num /= base;
	}
	return str;
}

void interpritfile(const std::string& filename, const bool& trass, const std::string file) {
	std::map<char, int > variables;
	std::ifstream in;
	std::ofstream out;
	if (trass) {
		out.open(file);
	}
	std::string read = "read(";
	std::string write = "write(";
	std::string num = "";
	char key;
	int base = 10;
	in.open(filename);
	int first = 0;
	int second = 0;
	std::string opiration = "";
	char c=' ';
	in >> c; dotrass(c, out, trass);
	while (c != -1) {
		if (c == 'r') {
			stringsrav(read, c, in, out, trass);
			readbase(c, base, in, key, out, trass);
				std::cin >> num;
				variables[key] = fromsistem(num, base);
				if (trass)
					out << variables[key];
				base = 10; num = "";
			
		 }
		if (c == 'w') {
			stringsrav(write, c, in, out, trass);
			readbase(c, base, in, key, out, trass);
			if (variables.find(key) == variables.cend()) {
				throw("noelem" + c);
			}
			else {
				num = tosistem(variables[key], base);
			}
			std::cout << num; 
			if (trass)
				out << num; 
			num = "";
			base = 10;
		}
		if (isupper(c)) {
			key = c;
			in >> c;  dotrass(c, out, trass);
			if(c!=':')
				throw("no=");
			else {
				if (c != '=') {
					throw("no=");
				}
				else {
					in >> c;
					dotrass(c, out, trass);
				}
				if (c == 92) {
					opiration = "|"; in >> c;  dotrass(c, out, trass);
					if (!isupper(c)) {
						throw("no[A,...,Z]");
					}
					else {

						if (variables.find(c) == variables.cend()) {
							throw("noelem" + c);
						}
						else {

							first = variables[c];
						} in >> c;
						dotrass(c, out, trass);
					}
					if (c != ';') {
						throw("no;");
					}
					else {
						in >> c;
						dotrass(c, out, trass);
					}
					variables[key] = dooopiration(first, opiration, second);
					if (trass) {
						out << key << "=" << variables[key] << '\n';
					}
					first = 0;
					opiration = "";
					//опирация
				}
				else {
					if (isupper(c)) {

						if (variables.find(c) == variables.cend()) {
							throw("noelem" + c);
						}
						else {
							first = variables[c];
						}in >> c;
						dotrass(c, out, trass);
						while (!isupper(c) && c != -1) {
							num = num + c;
						}
						if (isupper(c)) {
							if (variables.find(c) == variables.cend()) {
								throw("noelem" + c);
							}
							else {
								second = variables[c];
							} in >> c;
							dotrass(c, out, trass);
						}
						else {
							throw("no[A,...,Z]");
						}
						if (c != ';') {
							throw("no;");
						}
						else {
							in >> c;
							dotrass(c, out, trass);
						}
						variables[key] = dooopiration(first, opiration, second);
						if (trass) {
							out << key << "=" << variables[key] << '\n';
						}
						first = 0;
						second = 0;
						opiration = "";
						//опирация

					}
					else {
						throw("no[A,...,Z]");
					}

				}
			}

		}


	}
	in.close();
}

void dotrass(const char& c, std::ofstream& out, const bool&trass) {
	if (trass)
		out << c;
}

void stringsrav(const std::string& name,  char& c, std::ifstream&in, std::ofstream&out, const bool&trass) {
	for (int i = 0; i < name.length(); i++) {
		if (name[i] == c) {
			in >> c;  dotrass(c, out, trass);
		}
		else {
			throw("it is not " + name);
			 
		}
	}
}

void readbase(char& c, int& base, std::ifstream& in, char&key, std::ofstream& out, const bool& trass) {
	if (isupper(c)) {
		key = c;
		in >> c;  dotrass(c, out, trass);
		if (c == ',') {
			in >> c;  dotrass(c, out, trass);
			base = 0;
			while (isdigit(c) && c != -1) {
				base = base * 10 + c - '0'; in >> c;  dotrass(c, out, trass);
			}
			if (base < 2 || base>36) {
				throw("nobase");
				 
			}
		}
		if (c != ')')   {
			throw("no)");
			 
		}
		else {
			in >> c;  dotrass(c, out, trass);
			if (c != ';') {
				throw("no;");
				 
			}
			else {
				in >> c;  dotrass(c, out, trass);
			}
		}
	}
	else {
		throw("no[A,...,Z]");
	}
}
 


