#pragma once
#define p 1
#define m 0
#include <string>
#include <iostream>

class Big_int
{
protected:
	bool sign = p;
	std::string num="0";
	int sistem=10;
private:
	Big_int&addition(const Big_int &big1, const Big_int& big2);
	Big_int& multiplication(const Big_int& big1, const Big_int& big2);
	Big_int&subtraction(const Big_int& big1, const Big_int& big2);
	Big_int& add_or_sub(const Big_int& big1, const Big_int& big2);
	Big_int& multiplication_one(const Big_int& big1, const int& num);
	bool is_max(const Big_int& big)const;
	int return_num(const int i)const {
		if (isdigit(num[i])) {
			return num[i]-'0';
		}
		else{
			return num[i] - 'A'+10;
		}
	}
	char return_char(const int i)const {
		if (0<=i&&i<=9) {
			return i + '0';
		}
		else {
			return i -10+ 'A';
		}
	}
	int fromsistem(std::string str, int base);  
	Big_int tosistem(int num, const int& base);  
	Big_int re_base(int sistem) {
		return tosistem(this->sistem, sistem);
	}
	Big_int re_num(int sistem, std::string str) {
		int num = fromsistem(str, this->sistem);
		return tosistem(num, sistem);
	}
	 
public:
	Big_int& tosistem(const int base);
	Big_int() {};
	Big_int(const std::string& str, const int sist = 10) {
		 
		this->sistem = sist;
		this->num = str;
		if (str[0] == '-') {
			sign = m;
			this->num.erase(0, 1);
		}
		else if (str[0] == '+') {
			sign = p;
			this->num.erase(0, 1);
		}
		 
	}
	Big_int& operator+=(const Big_int& number){
		this->add_or_sub(*this, number);
		return *this;
	}
	Big_int operator+(const Big_int& number)const {
		Big_int resault;
		 resault.add_or_sub(*this, number);
		return resault;

	}
	Big_int& operator-=(const Big_int& number) {
		this->add_or_sub(*this, -number);
		return *this;
		 
	}
	Big_int operator-(const Big_int& number)const {
		Big_int resault;
		 
		resault.add_or_sub(*this, -number);
		 
		return resault;
	}
	Big_int& operator*(const int number)const {
		Big_int resault = *this;
		bool s;
		(number < 0) ? (s = m) : (s = p);
		resault.multiplication_one(*this, number);
		resault.sign = (sign || !s) && (!sign || s);
		return resault;
	}
	Big_int& operator*=(const int number) {
		bool s;
		(number < 0) ? (s = m) : (s = p);
		this->multiplication_one(*this, number);
		sign = (sign || !s) && (!sign || s);
		return*this;
	}
	Big_int& operator*=(const Big_int& number) {
		if (is_max(number)) {
			this->multiplication(*this, number);
		}
		else {
			this->multiplication(number, *this);
		}
		sign = (sign || !number.sign) && (!sign || number.sign);
		return *this;
	}
	Big_int operator*(const Big_int& number)const {
		Big_int resault;
		if (is_max(number)) {

			resault.multiplication(*this, number);
		}
		else {
			resault.multiplication(number, *this);
		}
		resault.sign = (sign || !number.sign) && (!sign || number.sign);
		return resault;
	}
	 

	Big_int operator -() const {
		Big_int copy = *this;
		copy.sign = !copy.sign;
		return copy;
	}
	Big_int&operator -(){
		this->sign = !this->sign;
		return *this;
	}
	Big_int operator +() const {
		Big_int copy = *this;
		return copy;
	}
	Big_int& operator +() {
		return *this;
	}
	friend std::ostream& operator<< (std::ostream& out, const Big_int& big) {
		out << big.sistem << ":";
		if (big.sign == m) {
			out << "-";
		}
		out << big.num;
		return out;
	}
	friend std::istream& operator>> (std::istream& in, Big_int& big) {
		std::string my_num = "";
		in >> my_num; int base = 10;
		if (my_num.find(":") != -1) {
			std::string my_base = my_num;
			base = atoi(my_base.erase(my_base.find(":"), my_base.size() - my_base.find(":")).c_str());
			my_num.erase(0, 1 + my_base.find(":"));
		}
		Big_int my_big(my_num, base);
		big = my_big;
		return in;
	}
	Big_int& rand_generation(const int bit, const int base = 2) {
		std::string my_num = "";
		this->sign = rand() % 2;
		for (int i = 0; i < bit; i++) {
			bool b = rand() % 2;
			my_num += (b + '0');	
		}
		this->sistem = 2;
		this->num = my_num;
		if (base != 2) {
			this->tosistem(base);
		}
		this->sistem = base;
		return *this;
	}
	Big_int Karacube(const Big_int& big1, const Big_int& big2);
	Big_int Fourier(const Big_int& big1, const Big_int& big2);
	Big_int& Reverse() {
		for (int i = 0; i < num.size() / 2; i++) {
			char c = num[i];
			num[i] = num[num.size() - 1 - i];
			num[num.size() - 1 - i] = c;
		}
		return*this;
	}
};

