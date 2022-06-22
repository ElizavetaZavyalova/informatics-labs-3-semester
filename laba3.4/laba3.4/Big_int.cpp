#include "Big_int.h"

Big_int&Big_int::addition(const Big_int&big1,const Big_int&big2){
    int l = big2.num.size() - 1; int b = big1.num.size() - 1;
	std::string new_num = big1.num; int remains = 0;
	while (l >= 0) {
		  
		char n = this->return_char(((big1.return_num(b) + big2.return_num(l))+remains)%big1.sistem);
		remains = (big1.return_num(b) + big2.return_num(l)) / big1.sistem;
		new_num[b] = n; l--; b--;

	}
	if (remains != 0) {
		if (b < 0) {
			new_num = "1" + new_num;
		}
		else {
			new_num[b] = this->return_char((big1.return_num(b) + remains));
		}
	}
	while (new_num[0] == '0' && new_num.size() > 1) {
		new_num.erase(0, 1);
	}
	this->num = new_num;
	this->sistem = big1.sistem;
	return *this;
	 
}
Big_int& Big_int::multiplication_one(const Big_int& big1, const int&num) {
	int l = big1.num.size() - 1;
	int remains = 0; std::string new_num = "";
	while (l >= 0) {
		char n = big1.return_char((big1.return_num(l) * num + remains) % big1.sistem);
		remains = (big1.return_num(l) * num + remains) / big1.sistem;
		new_num = n + new_num; l--;
	}
	if (remains != 0) {
		new_num = this->return_char(remains) + new_num;
	}
	this->num = new_num;
	this->sistem = big1.sistem;
	this->sign = big1.sign;
	return *this;
}
Big_int&Big_int::multiplication(const Big_int& big1, const Big_int& big2){
	 int l = big2.num.size() - 1; int b = big1.num.size() - 1;
	  std::string zero= "";
	 this->multiplication_one(big1, big2.return_num(l)); l--;
	 Big_int help("+", big1.sistem);
	 while(l >= 0) {
		 help.multiplication_one(big1, big2.return_num(l)); l--;
		 zero += "0";
		 help.num += zero;
		 this->addition(help, *this);
	 }
	 while (this->num[0] == '0' && this->num.size() > 1) {
		 this->num.erase(0, 1);
	 }
	 return *this;
}
Big_int&Big_int::subtraction(const Big_int& big1, const Big_int& big2){
	std::string new_num = big1.num; int l = big2.num.size() - 1; int b = big1.num.size() - 1;
	int remain = 0;
	while (l >= 0) {
		int n = big1.return_num(b) - big2.return_num(l) + remain;
		if (n < 0) {
			remain = -1;
			n += big1.sistem;
		}
		new_num[b] = this->return_char(n); l--; b--;
    }
	while (remain != 0) {
		int n = big1.return_num(b) + remain;
		if (n < 0) {
			remain = -1;
			n += big1.sistem;
		}
		else {
			remain = 0;
		}
		new_num[b] = this->return_char(n); l--; b--;
	}
	while (new_num[0] == '0' && new_num.size() > 1) {
		new_num.erase(0, 1);
	}

	this->num = new_num;
	this->sistem = big1.sistem;
	return *this;
}

bool Big_int::is_max(const Big_int& big)const {
	if (this->num.size() > big.num.size()) {
		return 1;
	}
	if (this->num.size() < big.num.size()) {
		return 0;
	}
	int l = 0;
	while (l != num.size()) {
		if (num[l] > big.num[l])
			return 1;
		if (num[l] < big.num[l])
			return 0;
		l++;
	}
	return 0;

}

Big_int& Big_int::add_or_sub(const Big_int& big1, const Big_int& big2) {
	if (big1.sign == big2.sign) {
		if (big2.is_max(big1)) {
			this->addition(big2, big1);
			this->sign = big2.sign;
		}
		else {
		     this->addition(big1, big2);
			 this->sign = big1.sign;
		}
		 
	}
	else {
		if (big2.is_max(big1)) {
			this->subtraction(big2, big1);
			this->sign = big2.sign;

		}
		else {
			this->subtraction(big1, big2);
			this->sign = big1.sign;
		}
	}
	return*this;

}

int Big_int::fromsistem(std::string str, int base) {
	int num = 0;
	int i = 0;
	int numb = 0;
	int len = str.length();
	while (i < len) {


		numb = (isdigit(str[i]) ? (str[i] - '0') : isupper(str[i]) ? \
			(str[i] - 'A' + 10) : (str[i] - 'a' + 36));

		num = num * base + numb;
		i++;
	}
	return num;
}
Big_int Big_int::tosistem(int num, const int& base){
	std::string str = "";
	do {
		char remains = num % base;
		(remains < 10) ? (remains += '0') : (remains = remains - 10 + 'A');
		str = remains + str; num /= base;
	} while (num != 0);

	Big_int big(str, base);
	return big;
}

Big_int& Big_int::tosistem(const int base){
	Big_int my_base = re_base(base);
	Big_int resault("0", base);
	int i = 0;
	int len = this->num.length();
	while (i < len) {

		std::string res = ""; res+=num[i];
		Big_int numb = re_num(base, res);
		resault = resault * my_base;
		resault =  resault + numb;
		i++;
	}
	this->num = resault.num;
	this->sistem = base;

	return *this;
	
}
