#pragma once

#include <iostream>
#include <string>
#include <exception>

using namespace std;

template<typename T>
class base {
public:
	virtual int compare(const T& left, const T& right) const = 0;
	virtual ~base() = default;
};

template<typename T>
class sravny : public base<T> {

public:
	int compare(const T& left, const T& right) const override {
		if (left > right)
			return 1;

		if (left < right)
			return -1;
		else
			return 0;
	}
};




class Myexcept : public exception {

public:
	Myexcept(const char* ex) :exception(ex) {

	}
};



template<typename T1, typename T2>
struct Res {
	T1 key;
	T2 elem;
};

template<typename T1, typename T2>
class Tree;

template<typename T1, typename T2>
class Node {
	Node<T1, T2>* left = nullptr;
	Node <T1, T2>* right = nullptr;
	Res<T1, T2> res;
public:
	friend class Tree<T1, T2>;
};

template<typename T1, typename T2>
class Tree {
	Node<T1, T2>* Top = nullptr;
	base<T1>* comp = nullptr;
	void infixTree(Node<T1, T2>* node, void (*func)(Res<T1, T2>& res, int height), int height1);
	void prefixTree(Node<T1, T2>* node, void (*func)(Res<T1, T2>& res, int height), int height1);
	void posfixTree(Node<T1, T2>* node, void (*func)(Res<T1, T2>& res, int height), int height1);
	void destroy(Node<T1, T2>* node) {
		if (node == nullptr)
			return;
		destroy(node->left);
		destroy(node->right);
		delete node;
	}
	void coppy(Node<T1, T2>* els, const Node<T1, T2>* my) {
		if (my == nullptr) {
			return;
		}
		els->res.key = my->res.key;
		els->res.elem = my->res.elem;
		if (my->left != nullptr) {
			els->left = new Node<T1, T2>;
			coppy(els->left, my->left);
		}
		if (my->right != nullptr) {
			els->right = new Node<T1, T2>;
			coppy(els->right, my->right);
		}
	}
public:

	~Tree() {
		destroy(Top);
		Top = nullptr;

	};
	T2& operator[] (const T1 key) const;
	void operator=(const Tree<T1, T2>& obj) {
		this->comp = obj.comp;
		if (Top != nullptr) {
			destroy(Top);
			Top = nullptr;
		}
		if (obj.Top != nullptr) {
			Top = new Node < T1, T2 >;
			coppy(Top, obj.Top);
		}

	};

	Tree(const Tree<T1, T2>& obj) {
		this->comp = obj.comp;
		if (Top != nullptr) {
			destroy(Top);
			Top = nullptr;
		}
		if (obj.Top != nullptr) {
			Top = new Node < T1, T2 >;
			coppy(Top, obj.Top);
		}
	};

	void operator+= (Res<T1, T2> some);
	void operator*= (Res<T1, T2> some);
	void operator-= (Res<T1, T2> some);
	Tree(base<T1>* comp = nullptr) {

		this->comp = comp;

	};

	void infix(void (*func)(Res<T1, T2>& res, int height)) {
		infixTree(Top, func, 0);
	}
	void prefix(void (*func)(Res<T1, T2>& res, int height)) {
		prefixTree(Top, func, 0);
	}
	void posfix(void (*func)(Res<T1, T2>& res, int height)) {
		posfixTree(Top, func, 0);
	}


};

template<typename T1, typename T2>
void write(Res<T1, T2 >& res, int height) {
	std::cout << "Key: " << res.key << " elem: " << res.elem << " height " << height << '\n';
}

template<typename T1, typename T2>
void Tree<T1, T2>::operator+= (Res<T1, T2> some) {
	if (Top == nullptr) {
		Top = new Node<T1, T2>;
		Top->res.elem = some.elem;
		Top->res.key = some.key;
		return;
	}
	Node<T1, T2>* node = Top;
	while (1) {
		int h = comp->compare(some.key, node->res.key);
		if (h == 1) {
			if (node->right != nullptr)
				node = node->right;
			else {
				node->right = new Node<T1, T2>;
				(node->right)->res.elem = some.elem;
				(node->right)->res.key = some.key;
				return;
			}
		}
		else if (h == -1) {
			if (node->left != nullptr)
				node = node->left;
			else {
				node->left = new Node<T1, T2>;
				((node->left)->res).elem = some.elem;
				((node->left)->res).key = some.key;
				return;
			}
		}
		else {
			throw Myexcept("the same key was found ");
			return;
		}
	}
};


template<typename T1, typename T2>
T2& Tree<T1, T2>::operator[] (T1 key) const {
	Node<T1, T2>* node = Top;
	while (1) {
		if (node == nullptr) {
			throw  Myexcept("Key not found");
			break;
		}
		int h = comp->compare(key, node->res.key);
		if (h == 1) {
			node = node->right;
		}
		else if (h == -1) {
			node = node->left;
		}
		else if (h == 0) {

			return node->res.elem;
		}
	}
}

template<typename T1, typename T2>
void Tree<T1, T2>::operator*= (Res<T1, T2> some) {
	Node<T1, T2>* node = Top;
	while (1) {
		if (node == nullptr) {
			throw  Myexcept("Key not found");
			return;
		}
		int h = comp->compare(some.key, node->res.key);
		if (h == 1) {
			node = node->right;
		}
		else if (h == -1) {
			node = node->left;
		}
		else if (h == 0) {
			node->res.elem = some.elem;
			return;
		}
	}

};

template<typename T1, typename T2>
void Tree<T1, T2>::operator-= (Res<T1, T2> some) {
	Node<T1, T2>* node = Top;
	Node<T1, T2>* parent = nullptr;
	while (1) {
		if (node == nullptr) {
			throw Myexcept("Key not found");
			return;
		}
		int h = comp->compare(some.key, node->res.key);
		if (h == 1) {
			parent = node;
			node = node->right;
		}
		else if (h == -1) {
			parent = node;
			node = node->left;
		}
		else if (h == 0) {
			break;
		}
	}
	if (node->left == nullptr && node->right == nullptr) {
		(parent == nullptr) ? (Top = nullptr) : (parent->left == node) ? (parent->left = nullptr) : (parent->right = nullptr);
		delete node;
		return;
	}
	if (node->left != nullptr && node->right == nullptr) {
		if (parent != nullptr) {
			if (parent->left == node)
				parent->left = node->left;
			else if (parent->right == node)
				parent->right = node->left;
		}
		else
			Top = node->left;

		delete node;
		return;
	}
	if (node->left == nullptr && node->right != nullptr) {
		if (parent != nullptr) {
			if (parent->left == node)
				parent->left = node->right;
			else if (parent->right == node)
				parent->right = node->right;
		}
		else
			Top = node->right;
		delete node;
		return;
	}
	Node<T1, T2>* smen = node->left;
	parent = node;
	while (smen->right != nullptr) {
		parent = smen;
		smen = smen->right;
	}
	node->res.key = smen->res.key;
	node->res.elem = smen->res.elem;
	if (smen->left != nullptr) {
		if (parent->left == smen)
			parent->left = smen->left;
		else if (parent->right == smen)
			parent->right = smen->left;
	}
	else {
		if (parent->left == smen)
			parent->left = nullptr;
		else if (parent->right == smen)
			parent->right = nullptr;
	}
	delete smen;
	return;
};

template<typename T1, typename T2>
void Tree<T1, T2>::prefixTree(Node<T1, T2>* node, void (*func)(Res<T1, T2>& res, int height), int height1) {
	if (node == nullptr)
		return;
	func(node->res, height1);
	prefixTree(node->left, func, height1 + 1);
	prefixTree(node->right, func, height1 + 1);

}

template<typename T1, typename T2>
void Tree<T1, T2>::infixTree(Node<T1, T2>* node, void (*func)(Res<T1, T2>& res, int height), int height1) {
	if (node == nullptr)
		return;

	infixTree(node->left, func, height1 + 1);
	func(node->res, height1);
	infixTree(node->right, func, height1 + 1);
}

template<typename T1, typename T2>
void Tree<T1, T2>::posfixTree(Node<T1, T2>* node, void (*func)(Res<T1, T2>& res, int height), int height1) {
	if (node == nullptr)
		return;

	posfixTree(node->left, func, height1 + 1);
	posfixTree(node->right, func, height1 + 1);
	func(node->res, height1);
}