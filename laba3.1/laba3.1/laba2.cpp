#include "laba2.h"
bool isitconvex(int num, ...){
	va_list arg;
	 
	va_start(arg, num);
	int i = 0;
	 
	while (i < num) {

		Point point = va_arg(arg, Point);
		 
		i++;
	}
	va_end(arg);
	return 0;
}