#pragma once
#include <vector>
#include <iostream>
template<typename Tkey>
class comparer
{
public:
	virtual int compare(const Tkey& left, const Tkey& right) = 0;
	virtual ~comparer() = default;
};

template<typename Tkey, typename Tvalue>
class BinareaPyramid : public AC<Tkey, Tvalue>
{
	comparer* _comparer = nullptr;
	BinareaPyramid(comparer* _comparer) {
		this->_comparer = _comparer;
	}
	struct Elem {
		Tkey key;
		Tvalue value;
		Elem() {}
		Elem(const Tkey& key, const Tvalue& value) {
			this->key = key;
			this->value = value;
		}
	};
	std::vector<Elem> Pyramid;
public:
	static AC<Tkey, Tvalue>* factory_method(comparer* _comparer) {
		return new BinareaPyramid<Tkey, Tvalue>(_comparer);
	}
};


template<typename Tkey, typename Tvalue >
class BinomialPyramid : public AC<Tkey, Tvalue>
{
	struct Elem {
		Tkey key;
		Tvalue value;
		Elem() {}
		Elem(const Tkey& key, const Tvalue& value) {
			this->key = key;
			this->value = value;
		}
	};
	std::vector<Elem> Pyramid;
	comparer* _comparer = nullptr;
	BinomialPyramid(comparer* _comparer) {
		this->_comparer = _comparer;
	};
public:
	static AC<Tkey, Tvalue>* factory_method(comparer* _comparer) {
		return new BinomialPyramid<Tkey, Tvalue>(_comparer);
	}
};


template<typename Tkey, typename Tvalue>
class FibonacciPyramid : public AC<Tkey, Tvalue>
{
	comparer* _comparer = nullptr;
	FibonacciPyramid(comparer* _comparer) {
		this->_comparer = _comparer;
	}
	struct Elem {
		Tkey key;
		Tvalue value;
		Elem() {}
		Elem(const Tkey& key, const Tvalue& value) {
			this->key = key;
			this->value = value;
		}
	};
	std::vector<Elem> Pyramid;
public:

	static AC<Tkey, Tvalue>* factory_method(comparer* _comparer, int TYPE) {
		return new FibonacciPyramid<Tkey, Tvalue>(_comparer);
	}
};
