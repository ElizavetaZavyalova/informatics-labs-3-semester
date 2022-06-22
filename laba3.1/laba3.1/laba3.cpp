#include "laba3.h"
#include<cstdlib>
float mnogochlen(float point, int degree, ...) {
	 
	va_list arg;
	degree++;
	va_start(arg, degree);
	int i = 0;

    float resault = 0 ;
	while (i < degree) {
		 
		resault = va_arg(arg, int)+point*resault;
	 
		i++;
	}
	va_end(arg);
	return resault;
}
