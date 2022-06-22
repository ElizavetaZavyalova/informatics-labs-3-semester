#include "Big_int.h"
Big_int Big_int::Karacube(const Big_int&nums1, const Big_int& nums2) {
	 
	if (nums1.num.size() == 1 && nums2.num.size()==1) {
		int t = nums1.return_num(0) * nums2.return_num(0);
		std::string s = "";
		s += this->return_char(t % nums1.sistem); t = t / nums1.sistem;
		if (t != 0) {
			s = this->return_char(t) + s;
		}
		Big_int my_resault;
		my_resault.num = s;
		my_resault.sistem = nums1.sistem;
		return my_resault;
	}
	int  s[4];
	std::string new_nums[4];
	for (int i = 0; i < 2; i++) {
		new_nums[i] = nums1.num;
		new_nums[i+2] = nums2.num;
		s[i] = nums1.num.size();
		s[i+2] = nums2.num.size();
	}
	int flag = 0;
		if (s[0]>1) {
			s[0] = s[0] / 2;
			s[1] = s[1] - s[0];
			new_nums[0].erase(0, s[0]);
			new_nums[1].erase(s[0], s[1]);
			 

		}
		else {
			new_nums[1] = "0";
		}
		if (s[2] > 1) {
			s[2] = s[2] / 2;
			s[3] = s[3]  - s[2];
			new_nums[2].erase(0, s[2]);
			new_nums[3].erase(s[2], s[3]);
			 
		}
		else {
			new_nums[3] = "0";
		}

	 
	Big_int my_nums[4];
	Big_int resault[4];
	for (int i = 0; i < 4; i++) {
		my_nums[i].num = new_nums[i];
	}
		resault[0] = Karacube(my_nums[0], my_nums[2]);
		resault[1] = Karacube(my_nums[0], my_nums[3]);
		resault[2] = Karacube(my_nums[1], my_nums[2]);
		resault[3] = Karacube(my_nums[1], my_nums[3]);
		std::string str1(s[1], 48);
		std::string str2(s[3], 48);
		std::string str3(s[3] + s[1], 48);
		resault[3].num += str3;
		resault[1].num += str1;
		resault[2].num += str2;
		return resault[0] + resault[1] + resault[2] + resault[3];
}


Big_int Big_int::Fourier(const Big_int& big1, const Big_int& big2) {

	return *this;
};