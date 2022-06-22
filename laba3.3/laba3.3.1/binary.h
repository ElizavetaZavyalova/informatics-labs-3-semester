#pragma once
#include <vector>
#include <iostream>
#include <list>
 #define BINAREAPYRAMID 0
#define BINOMINALPYRAMID 1
#define FIBONACCIPYRAMID 2

template<typename Tkey, typename Tvalue>
class AC;

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
	comparer<Tkey>* _comparer = nullptr;
	BinareaPyramid(comparer<Tkey>* _comparer) {
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
		void swap_elem(Elem&elem1) {
			Elem elem2(key, value);
			key = elem1.key;
			value = elem1.value;
			elem1.key = elem2.key;
			elem1.value= elem2.value;
		}
	};
	 
	std::vector<Elem> Pyramid;
public:
	static AC<Tkey, Tvalue>* factory_method(comparer<Tkey>* _comparer) {
		return new BinareaPyramid<Tkey, Tvalue>(_comparer);
	}
	void insert(const Tkey & key, const Tvalue & value) {
			Elem elem(key, value);
			Pyramid.push_back(elem);

			int chield = Pyramid.size() - 1;
			if (chield == 0)
				return;
			int parent = chield/2;

			while (chield > 0)
			{
				if (_comparer->compare(Pyramid[parent].key, Pyramid[chield].key) <= 0) {
					break;
				}
				elem = Pyramid[chield];
				Pyramid[chield] = Pyramid[parent];
				Pyramid[parent] = elem;

				chield= parent;
				parent = chield / 2;
				 
			}
			if (_comparer->compare(Pyramid[parent].key, Pyramid[chield].key) == 0) {
				//throw "exept";
			}
	};
	Tvalue& minimum(const Tkey& key, const Tvalue& value) {
		if (Pyramid.size() == 0) {
			//exept
		}
		return Pyramid[0].value; };
	Tvalue extractminimum() {
		if (Pyramid.size() == 0) {
			//exept
		}
		Tvalue value = Pyramid[0].value;
		Pyramid[0] = Pyramid[Pyramid.size() - 1];
		Pyramid.pop_back();
		int parent = 0;
		int chield[2];
		chield[0] = 1;
		chield[1] = 2; bool end = 1;
		while(end){
			int elem_min = parent;
			for (int i = 0; i < 2; i++) {
				 
				if (chield[i] <= Pyramid.size() - 1) {
					if (_comparer->compare(Pyramid[parent].key, Pyramid[chield[i]].key) > 0) {
						elem_min = chield[i];
					}
				}
				else {
					end = 0;
				}
			}
			Pyramid[parent].swap_elem(Pyramid[elem_min]);
			parent++;
			chield[0] = 2*parent+1;
			chield[1] = 2 * parent + 2; 
		}
		return value;

	};
	AC<Tkey, Tvalue>* merge(const AC<Tkey, Tvalue>* help)const {
		AC<Tkey, Tvalue>* mis = nullptr;
		mis = const_cast<AC<Tkey, Tvalue>*>(help);
		BinareaPyramid<Tkey, Tvalue>* help_me = nullptr;
		help_me = dynamic_cast<BinareaPyramid<Tkey, Tvalue>*>(mis);
		for (auto i = this->Pyramid.cbegin(); i != this->Pyramid.cend(); i++) {
			help_me->insert(i->key, i->value);
		}
		return help_me;
	};
	~BinareaPyramid() {};

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
		Elem(const Elem& elem) {
			this->key = elem.key;
			this->value = elem.value;

		}
	};
	struct Node {
		Elem elem;
		int size = 1;
		Node* next = this;
		Node* tree = nullptr;
		Node(const Tkey&key, const Tvalue&value) {
			elem.key = key;
			elem.value = value;
		}
		Node() {}
		void add_node_in_list(Node* nod)
		{
			Node* add = next;
			next = nod;
			nod->next = add;
		}
		void add_node_in_tree(Node* nod) {
			if (tree ==nullptr) {
				tree = nod;
			}
			else {
				Node* tree = (nod->tree);
				tree->add_node_in_list(nod);
			}
			 
		}
		void swap_elem(Elem& elem) {
			Elem elem_new = this->elem;
			this->elem = elem;
			elem = elem_new;
		}
	};
	Node* min = nullptr;
public:
	comparer<Tkey>* _comparer = nullptr;
	BinomialPyramid(comparer<Tkey>* _comparer) {
		this->_comparer = _comparer;
	};
	void merge_node(Node* enother) {
		if (min == nullptr) {
			min = enother;
			return;
		}
		 
		Node* min_new = nullptr;
		(this->_comparer->compare(enother->elem.key, min->elem.key) < 0) ? (min_new = enother) : (min_new = min);
		Node* parent = min;
		Node* chield = parent->next;
		 do
		 {
			 if (enother->size == chield->size) 
			 {
				 if (_comparer->compare(enother->elem.key, chield->elem.key) < 0) {
					 enother->add_node_in_tree(chield);
					 
				 }
				 else {
					chield->add_node_in_tree(enother);
					enother = chield;
					 
				 }
				 enother->size++;
				 parent->next = chield->next;
				 chield = parent->next;
			 }
			 else {
				 parent = parent->next;
				 chield = chield->next;
			 }
		} while (chield != min->next);
		min->add_node_in_list(enother);
		min = min_new;
	}

public:
	static AC<Tkey, Tvalue>* factory_method(comparer<Tkey>* _comparer) {
		return new BinomialPyramid<Tkey, Tvalue>(_comparer);
	}
	void insert(const Tkey& key, const Tvalue& value) {
		Node* node_n = new Node(key, value);
		merge_node(node_n);

	};
	Tvalue& minimum(const Tkey& key, const Tvalue& value) { 
		if (min == nullptr) {
			//exeption
		}
		else return min->elem.value;
	};
	Tvalue extractminimum() {
		Node* first_min = min->next;
		Node* first_elem = min;
		Tvalue value = min->elem.value;
		if (min == nullptr) {
			///exept
		}
		if (min != min->next) {
			do {
				first_elem = first_elem->next;
				if (_comparer->compare(first_min->elem.key, first_elem->elem.key) > 0) {
					first_min = first_elem;
				}

			} while (first_elem->next != min);
			first_elem->next = min->next;
		}
		Node* list = min->tree;
		delete min;
		min = first_min;
		if (list == nullptr) {
			return value;
		}
		 
		Node* chield = list->next->next;
		list->next = nullptr;
		while (chield != nullptr) {
			Node* parent = chield->next;
			chield->next = nullptr;
			merge_node(chield);
			chield = parent;
		}
		return value;
	};

	AC<Tkey, Tvalue>* merge(const AC<Tkey, Tvalue>* help1)const {
		 
		return new BinomialPyramid<Tkey, Tvalue>(_comparer);
	};
	~BinomialPyramid() {

	};
};


template<typename Tkey, typename Tvalue>
class FibonacciPyramid : public AC<Tkey, Tvalue>
{
	comparer<Tkey>* _comparer = nullptr;
	FibonacciPyramid(comparer<Tkey>* _comparer) {
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
	static AC<Tkey, Tvalue>* factory_method(comparer<Tkey>* _comparer) {
		return new FibonacciPyramid<Tkey, Tvalue>(_comparer);
	}
	void insert(const Tkey& key, const Tvalue& value) {};
	Tvalue& minimum(const Tkey& key, const Tvalue& value) { return Pyramid[0].value; };
	Tvalue extractminimum() { return Pyramid[0].value; };
	AC<Tkey, Tvalue>* merge(const AC<Tkey, Tvalue>* help)const { return new FibonacciPyramid<Tkey,Tvalue>(_comparer); };
	~FibonacciPyramid() {
		 
	};
};
 

 
template<typename Tkey>
class comparer1 : public comparer<Tkey>
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
	~comparer1() {}
};

template<typename Tkey, typename Tvalue>
class AC
{
public:
	virtual void insert(const Tkey& key, const Tvalue& value) = 0;
	virtual Tvalue& minimum(const Tkey& key, const Tvalue& value) = 0;
	virtual Tvalue extractminimum() = 0;
	virtual AC<Tkey, Tvalue>* merge(const AC<Tkey, Tvalue>* help)const = 0;
	static AC* factory_method(comparer<Tkey>* _comparer , int TYPE) {
		TYPE = TYPE % 3;
		if (TYPE == BINAREAPYRAMID) {
			return BinareaPyramid<Tkey, Tvalue>::factory_method(_comparer);
		}
		else if(TYPE == BINOMINALPYRAMID) {
			return BinomialPyramid<Tkey, Tvalue>::factory_method(_comparer);
		}
		else if(TYPE == FIBONACCIPYRAMID) {
			return FibonacciPyramid<Tkey, Tvalue>::factory_method(_comparer);
		}
	}
	virtual ~AC() = default;
};

 






