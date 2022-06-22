#include <iostream>
#include <stack>
#include <exception>

enum side { left=0, right=1, centre=2, not_go=3};
enum color { Black=0, Red=1 };

template<typename Tkey, typename Tvalue>
class tree_exception:public std::exception {
	Tkey key; Tvalue value;
public:
	Tkey Key()const {
		return key;
	 }
	Tvalue Value() const{
		return value;
	}
	tree_exception(const char* str, const Tkey&key, const Tvalue&value) :std::exception(str){
		this->key = key;
		this->value = value;
	}
	tree_exception(const char* str, const Tkey& key) :std::exception(str) {
		this->key = key;
	}

};
template<typename Tkey> 
class comparer
{
public:
	virtual int compare(const Tkey& left, const Tkey& right) = 0;
	virtual ~comparer() = default;
};

template<typename Tkey>
class comparer1: public comparer<Tkey>
{
public:
	int compare(const Tkey& left, const Tkey& right) {
		if (left > right)
			return 1;
		if (left < right)
			return -1;
		else
			return 0;
	}
	~comparer1(){}
};

template<typename Tkey, typename Tvalue> 
class AC
{
public:
	virtual void insert(const Tkey& key, const Tvalue& value) = 0;
	virtual Tvalue remove(const Tkey& key) = 0;
	virtual Tvalue& find(const Tkey& key) = 0;

	void virtual coppy_ptr( AC< Tkey, Tvalue>*& obj) = 0;
	virtual ~AC() = default;
};
 

 

 

 

 