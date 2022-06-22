#pragma once
#include "Big_int.h"

class Big_num:public Big_int
{
public:
	Big_num(const std::string&num, int base = 10) :Big_int(num, base) {}
	Big_num(){}
	Big_num& Karacube(const Big_num& big1, const Big_num& big2);
	Big_num& Fourier(const Big_num& big1, const Big_num& big2) { return *this; }
};

