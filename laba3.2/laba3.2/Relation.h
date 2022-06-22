#pragma once
#include "RB_Splay_AVL.h"
#include <map>
#include <vector>
#include <functional>
enum tree_name {
	bt, avl, splay, rb, t2_3
};

template<typename Tkey>
class comparersize : public comparer<Tkey>
{
public:
	int compare(const Tkey& left, const Tkey& right) {
		if (left.size() > right.size())
			return 1;
		if (left.size() < right.size())
			return -1;
		else
			return 0;
	}
	~comparersize() {}
};

template<typename Tkey, typename Tvalue>
class Relation
{
	class relation_exception :public std::exception {
		std::string name;
	public:

		relation_exception(const char* str, std::string name) :std::exception(str) {
			this->name = name;
		}
		relation_exception(const char* str) :std::exception(str) {

		}

	};

	std::map<std::string, AC<Tkey, Tvalue>*> Tree;
	std::vector<std::pair<Tkey, Tvalue>> data;
	 
public:
	Relation(const Relation& obj) {
		this->data = obj.data;
		for (auto i = Tree.begin(); i != Tree.end(); i++) {
			delete i->second;
			Tree.erase(i->first);
		}
		for (auto i = obj.Tree.begin(); i != obj.Tree.end(); i++) {
			std::string name = i->first;
			AC<Tkey, Tvalue>* nod = i->second;
			AC<Tkey, Tvalue>* t = nullptr;
			  nod->coppy_ptr(t);
			Tree[name] = t;
		}
	 }
	Relation& operator=(const Relation& obj) {
		this->data = obj.data;
		for (auto i = Tree.begin(); i != Tree.end(); i++) {
			delete i->second;
			Tree.erase(i->first);
		}
		for (auto i = obj.Tree.begin(); i != obj.Tree.end(); i++) {
			std::string name = i->first;
			AC<Tkey, Tvalue>* nod = i->second;
			AC<Tkey, Tvalue>* t = nullptr;
			nod->coppy_ptr(t);
			Tree[name] = t;
		}
		return *this;
	}
	Relation() {}
	~Relation() {
		for (auto i = Tree.begin(); i != Tree.end(); i++) {
			delete i->second;
		}
	}
	Relation&insert_index(const std::string str, tree_name name, comparer<Tkey>* _comparer) {
		if (_comparer != nullptr) {
			BuilderInsert insert(_comparer);
			 
			if (insert.is_correct(str)) {
				if (Tree.find(str) == Tree.end()) {
					Tree[str] = insert.set_tree(name);
					for (auto i = data.begin(); i != data.end(); i++) {
						try {
							Tree[str]->insert(i->first, i->second);
						}
						catch (const std::exception& ex) {
							Tree.erase(str);
							throw relation_exception("can't use comparer", str);
						};
					}
					return*this;
				}
				throw relation_exception("dublicate name", str);
			}
			else
				throw relation_exception("not correct name", str);
		}
		else
			throw relation_exception("comparer is null");

	}
	Relation& delete_index(const std::string str) {
		if (Tree.find(str) != Tree.end()) {
			delete Tree[str];
			Tree.erase(str);
			return*this;
		}
		else {
			throw relation_exception("not found name", str);
		}

	}
	class BuilderInsert {
		comparer<Tkey>* _comparer = nullptr;
		AC<Tkey, Tvalue>* tree = nullptr;
	 
		 
		AC<Tkey, Tvalue>* set_AVL(){return new AVL<Tkey,Tvalue>(_comparer); }
		AC<Tkey, Tvalue>* set_Splay(){return new Splay<Tkey,Tvalue>(_comparer); }
		AC<Tkey, Tvalue>* set_BT(){return new BT<Tkey,Tvalue>(_comparer); }
	    AC<Tkey, Tvalue>* set_RB(){return new RB<Tkey,Tvalue>(_comparer); }
		AC<Tkey, Tvalue>* set_T2_3(){return new T2_3<Tkey,Tvalue>(_comparer); }
	public:
		AC<Tkey, Tvalue>* set_tree(const tree_name name) {
			if (name == avl)
				return set_AVL();
			if (name == rb)
				return set_RB();
			if (name == splay)
				return set_Splay();
			if (name == t2_3)
				return set_T2_3();
			if (name == bt)
				return set_BT();
			else
				throw relation_exception("not correct tree");
		}
		bool is_correct(std::string str) {
			if (str.size() == 0) {
				return 0;
			}
			if (str.size() > 32) {
				return 0;
			}
			if (isalpha(str[0])) {
				for (int i = 0; i < str.size(); i++) {
					if (!isalpha(str[i]) && !isdigit(str[i]))
						return 0;
				}
				return 1;
			}
			return 0;
		}
		BuilderInsert(comparer<Tkey>* _comparer) {
			this->_comparer = _comparer;
		}
		void set_comparer(comparer<Tkey>* _comparer) {
			this->_comparer = _comparer;
		}
	};
	class Finding{
    	AC<Tkey, Tvalue>* tree;
	public:
		Finding( AC<Tkey, Tvalue>*tree) {
			tree->coppy_ptr(this->tree);
			 
	    }
		bool find(const Tkey& key) {
			try{
				tree->find(key);
			}
			catch (tree_exception<Tkey,Tvalue>& ex) {
				return 1;
			}
			return 0;
		}
		void set( AC<Tkey, Tvalue>* tree) {
			delete this->tree;
			tree->coppy_ptr(this->tree);
		}
		~Finding() {
			delete tree;
		}

	};
	Relation& insert(const Tkey& key, const Tvalue& value) {
		for (auto i = Tree.begin(); i != Tree.end(); i++) {
			Finding find(i->second);
			if (!find.find(key)) {
				throw relation_exception("dublicate index", i->first);
			}
		}
		std::pair<Tkey, Tvalue> element;
		element.first = key;
		element.second = value;
		data.push_back(element);
		for (auto i = Tree.begin(); i != Tree.end(); i++) {
			 
			
			i->second->insert(key, value);
		}
		return *this;
	}
	Relation& remove(const Tkey& key) {
		for (auto i = Tree.begin(); i != Tree.end(); i++) {
			Finding find(i->second);
			if (find.find(key)) {
				throw relation_exception("dublicate index", i->first);
			}
		}
		Tvalue value;
		for (auto i = Tree.begin(); i != Tree.end(); i++) {
			value=i->second->remove(key);
		}
		std::pair<Tkey, Tvalue> elem;
		elem.first = key;
		elem.second = value;
		for (auto i = data.begin(); i != data.end(); i++) {
			if (*i == elem) {
				i = data.erase(i);
			}
		}
		return *this;
	}
	Tvalue& find(const Tkey& key, std::string name) {
		if (Tree.find(name) == Tree.end()) {
			throw relation_exception("tree not found", name);
		}
		else {
			return Tree[name]->find(key);
		}
	}
};


 