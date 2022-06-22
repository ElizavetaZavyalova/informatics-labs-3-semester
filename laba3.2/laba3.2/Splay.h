#pragma once
//#include "AC.h"

 

enum side { left = 0, right = 1, centre = 2, not_go = 3 };
enum color { Black = 0, Red = 1 };

template<typename Tkey, typename Tvalue>
class tree_exception :public std::exception {
	Tkey key; Tvalue value;
public:
	Tkey Key()const {
		return key;
	}
	Tvalue Value() const {
		return value;
	}
	tree_exception(const char* str, const Tkey& key, const Tvalue& value) :std::exception(str) {
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
class BT
{
protected:
	struct Node
	{
		Tkey key;
		Tvalue value;
		Node* link[2];
		Node() {
			link[0] = nullptr;
			link[1] = nullptr;
		}
		Node(const Tkey& key, const Tvalue& value) :Node() {
			this->key = key;
			this->value = value;
		}
		virtual int bf() { return 0; };
		virtual void bf(int b) {};
	};

protected:

	class finding_template {
	public:
		enum status
		{
			ok,
			key_not_found
		};
	public:
		status invoke(Node*& Root, const Tkey& key, Tvalue*& value, comparer<Tkey>*& _comparer)
		{

			std::pair<std::stack<Node*>, std::stack<bool>> way = find_way(key, Root, _comparer);

			if (!way.first.empty()) {
				value = &(way.first.top()->value);
				this->balance(way.first, way.second, Root);
				return ok;
			}
			return 	key_not_found;
		}

	private:
		std::pair<std::stack<Node*>, std::stack<bool>> \
			find_way(const Tkey& key, Node* Root, comparer<Tkey>*& _comparer)
		{
			std::pair<std::stack<Node*>, std::stack<bool>> way;


			way.first.push(Root);

			while (Root != nullptr) {

				if (_comparer->compare(Root->key, key) < 0) {
					way.first.push(way.first.top()->link[right]);
					way.second.push(right);
					Root = Root->link[right];

				}
				else if (_comparer->compare(Root->key, key) > 0) {
					way.first.push(way.first.top()->link[left]);
					way.second.push(left);
					Root = Root->link[left];

				}
				else if (_comparer->compare(Root->key, key) == 0) {

					return way;
				}
			}

			std::pair<std::stack<Node*>, std::stack<bool>> way1;
			return way1;

		}

	protected:
		virtual void balance(std::stack<Node*>& nodes, std::stack<bool>& way, Node*& Root) {

		}
	};


	class insertion_template
	{
	public:
		enum status
		{
			ok,
			duplicate_key
		};

	public:
		status invoke(Node*& Root, const Tkey& key, const Tvalue& value, comparer<Tkey>*& _comparer)
		{
			if (Root == nullptr) {
				Root = set(key, value);
				return ok;
			}
			std::pair<std::stack<Node*>, std::stack<bool>> way = find_way(key, Root, _comparer);

			if (!way.first.empty()) {


				way.first.top()->link[way.second.top()] = set(key, value);
				way.first.push(way.first.top()->link[way.second.top()]);
				this->balance(way.first, way.second, Root);
				return ok;
			}
			return 	duplicate_key;
		}
	public:
		virtual  Node* set(const Tkey& key, const Tvalue& value) {
			return new Node(key, value);
		}
	public:
		virtual  Node* set() {
			return new Node;
		}
		virtual void set_bf(Node*& me, Node*& obj) {

		}
	public:
		std::pair<std::stack<Node*>, std::stack<bool>> \
			find_way(const Tkey& key, Node* Root, comparer<Tkey>*& _comparer)
		{
			std::pair<std::stack<Node*>, std::stack<bool>> way;

			way.first.push(Root);

			while (Root != nullptr) {

				if (_comparer->compare(Root->key, key) < 0) {
					way.first.push(way.first.top()->link[right]);
					way.second.push(right);
					Root = Root->link[right];

				}
				else if (_comparer->compare(Root->key, key) > 0) {
					way.first.push(way.first.top()->link[left]);
					way.second.push(left);
					Root = Root->link[left];

				}
				else if (_comparer->compare(Root->key, key) == 0) {
					std::pair<std::stack<Node*>, std::stack<bool>> way1;
					return way1;
				}
			}

			way.first.pop();
			return way;

		}

	public:
		virtual void balance(std::stack<BT<Tkey, Tvalue>::Node*>& nodes, std::stack<bool>& way,
			BT<Tkey, Tvalue>::Node*& Root) {
			int y = 0;
		}
	};

	class removing_template
	{

	public:
		enum status
		{
			ok,
			key_not_found
		};
	public:
		virtual status invoke(Node*& Root, const Tkey& key, Tvalue& value, comparer<Tkey>*& _comparer)
		{
			if (Root == nullptr) {
				return key_not_found;
			}
			bool splay = 0;
			std::pair<std::stack<Node*>, std::stack<bool>> way = find_way(key, Root, value, _comparer, splay);
			if (!way.first.empty())
			{
				if (!splay) {
					Node* kill = way.first.top(); way.first.pop();
					if (way.first.empty()) {
						if (kill->link[left] != nullptr) {
							Root = kill->link[left];
							way.first.push(Root);
						}
						else if (kill->link[right] != nullptr) {
							Root = kill->link[right];
							way.first.push(Root);
						}
						else {
							Root = nullptr;
							delete kill;
							return ok;

						}

					}
					else {
						if (kill->link[left] != nullptr) {
							way.first.top()->link[way.second.top()] = kill->link[left];
							way.first.push(kill->link[left]);
						}
						else if (kill->link[right] != nullptr) {
							way.first.top()->link[way.second.top()] = kill->link[right];
							way.first.push(kill->link[right]);
						}
						else {
							way.first.top()->link[way.second.top()] = nullptr;
							way.first.push(nullptr);

						}
					}
					way.first.push(kill);
					this->balance(way.first, way.second, Root);

					delete kill;
					return ok;
				}
				else {
					this->balance(way.first, way.second, Root);
					return ok;
				}
			}
			return key_not_found;
		}
		std::pair<std::stack<Node*>, std::stack<bool>> \
			find_way(const Tkey& key, Node* Root, Tvalue& value, comparer<Tkey>* _comparer, bool& splay)
		{

			bool find = 0;
			std::pair<std::stack<Node*>, std::stack<bool>> way;


			way.first.push(Root);
			while (Root != nullptr) {

				if (_comparer->compare(Root->key, key) < 0) {
					way.first.push(way.first.top()->link[right]);
					way.second.push(right);
					Root = Root->link[right];

				}
				else if (_comparer->compare(Root->key, key) > 0) {
					way.first.push(way.first.top()->link[left]);
					way.second.push(left);
					Root = Root->link[left];

				}
				else if (_comparer->compare(Root->key, key) == 0) {
					find = 1;
					break;
				}
			}
			find_kill(find, Root, way, value, splay);
			return way;

		}

	protected:
		virtual void balance(std::stack<Node*>& nodes, std::stack<bool>& way, Node*& Root) {

		}
		virtual void find_kill(const bool& find, Node*& Root, \
			std::pair<std::stack<Node*>, std::stack<bool>>& way, Tvalue& value, bool& splay) {
			if (find) {
				Node* kill = Root;
				value = Root->value;
				if (kill->link[left] == nullptr || kill->link[right] == nullptr)
					return;
				else {
					Root = Root->link[left];
					way.first.push(way.first.top()->link[left]);
					way.second.push(left);
					while (Root->link[right] != nullptr) {
						way.first.push(way.first.top()->link[right]);
						way.second.push(right);
						Root = Root->link[right];
					}
					kill->key = Root->key;
					kill->value = Root->value;
				}
				return;
			}

			std::pair<std::stack<Node*>, std::stack<bool>> way1;
			way = way1;
		}
	};

protected:
	Node* root = nullptr;
protected:
	comparer<Tkey>* _comparer;
	insertion_template* _inserter = nullptr;;
	removing_template* _remover = nullptr;
	finding_template* _finder = nullptr;

public:

	BT(comparer<Tkey>* comparer)
	{
		_comparer = comparer;
		_inserter = new  insertion_template;
		_remover = new removing_template;
		_finder = new finding_template;
	}
protected:
	BT() {};
private:
	void infixTree(Node* node, void (*func)(Tkey& key, Tvalue& value, int height), int height1) {
		if (node == nullptr)
			return;

		infixTree(node->link[left], func, height1 + 1);
		func(node->key, node->value, height1);
		infixTree(node->link[right], func, height1 + 1);

	}
	void prefixTree(Node* node, void (*func)(Tkey& key, Tvalue& value, int height), int height1) {
		if (node == nullptr)
			return;
		func(node->key, node->value, height1);
		prefixTree(node->link[left], func, height1 + 1);
		prefixTree(node->link[right], func, height1 + 1);

	}
	void posfixTree(Node* node, void (*func)(Tkey& key, Tvalue& value, int height), int height1) {
		if (node == nullptr)
			return;

		posfixTree(node->link[left], func, height1 + 1);
		posfixTree(node->link[right], func, height1 + 1);
		func(node->key, node->value, height1);
	}
public:
	void insert(const Tkey& key, const Tvalue& value) override
	{

		if (_inserter->invoke(root, key, value, _comparer) != 0) {
			throw tree_exception<Tkey, Tvalue>::tree_exception("dublicate key", key, value);
		}



	}

	Tvalue remove(const Tkey& key) override
	{
		Tvalue value;
		if (_remover->invoke(root, key, value, _comparer) != 0) {
			throw tree_exception<Tkey, Tvalue>::tree_exception("key_not_found", key);
		}
		return value;
	}

	Tvalue& find(const Tkey& key) override
	{
		Tvalue* value = nullptr;
		if (_finder->invoke(root, key, value, _comparer) != 0) {
			throw tree_exception<Tkey, Tvalue>::tree_exception("key_not_found", key);
		}
		return *value;
	}
	void destroy(Node* node) {
		if (node == nullptr)
			return;
		destroy(node->link[left]);
		destroy(node->link[right]);
		delete node;
	}
	void coppy(Node* els, Node* my) {
		if (my == nullptr) {
			return;
		}
		els->key = my->key;
		els->value = my->value;
		this->_inserter->set_bf(els, my);
		if (my->link[left] != nullptr) {
			els->link[left] = _inserter->set();
			coppy(els->link[left], my->link[left]);
		}
		if (my->link[right] != nullptr) {
			els->link[right] = _inserter->set();
			coppy(els->link[right], my->link[right]);
		}
	}

	BT(const BT<Tkey, Tvalue>& obj) {
		this->_comparer = obj.comp;
		delete _inserter;
		this->_inserter = obj._inserter;
		delete _remover;
		this->_remover = obj._remover;
		delete _finder;
		this->_finder = obj._finder;
		if (root != nullptr) {
			destroy(root);
			root = nullptr;
		}
		if (obj.root != nullptr) {
			root = _inserter->set();
			coppy(root, obj.root);
		}
	};
	virtual void coppy_ptr(AC<Tkey, Tvalue>*& my) {
		BT<Tkey, Tvalue>* me = new  BT<Tkey, Tvalue>(_comparer);
		BT<Tkey, Tvalue>* obj = dynamic_cast<BT<Tkey, Tvalue>*> (this);
		if (obj->root != nullptr) {
			me->root = new Node;
			coppy(me->root, obj->root);
		}
		my = me;
	}

	void operator=(const BT<Tkey, Tvalue>& obj) {
		this->_comparer = obj.comp;
		delete _inserter;
		this->_inserter = obj._inserter;
		delete _remover;
		this->_remover = obj._remover;
		delete _finder;
		this->_finder = obj._finder;
		if (root != nullptr) {
			destroy(root);
			root = nullptr;
		}
		if (obj.root != nullptr) {
			root = _inserter->set();
			coppy(root, obj.root);
		}

	};
	~BT() {
		destroy(root);
		root = nullptr;
		delete _finder;
		delete _remover;
		delete _inserter;

	};
	void infix(void (*func)(Tkey& key, Tvalue& value, int height)) {
		infixTree(root, func, 0);
	}
	void prefix(void (*func)(Tkey& key, Tvalue& value, int height)) {
		prefixTree(root, func, 0);
	}
	void posfix(void (*func)(Tkey& key, Tvalue& value, int height)) {
		posfixTree(root, func, 0);
	}
};

template<typename Tkey, typename Tvalue>
void write(Tkey& key, Tvalue& value, int height) {
	std::cout << height << "->" << "key" << key << "=" << "value" << value << '\n';
	return;
}
template<typename Tkey, typename Tvalue>
class Splay : public BT<Tkey, Tvalue> {
public:
	void coppy_ptr(AC<Tkey, Tvalue>*& my) {
		Splay<Tkey, Tvalue>* me = new  Splay<Tkey, Tvalue>(this->_comparer);
		Splay<Tkey, Tvalue>* obj = dynamic_cast<Splay<Tkey, Tvalue>*> (this);
		if (obj->root != nullptr) {
			me->root = this->_inserter->set();
			this->coppy(me->root, obj->root);
		}
		my = me;
	}
private:
	class Help {
	public:
		BT<Tkey, Tvalue>::Node* rotate(BT<Tkey, Tvalue>::Node* root, bool way1, bool way2) {
			auto node = root->link[way1];
			root->link[way1] = node->link[way2];
			node->link[way2] = root;
			return node;
		}
		BT<Tkey, Tvalue>::Node* zig_zag(BT<Tkey, Tvalue>::Node* root, bool& way1) {
			root->link[way1] = rotate(root->link[way1], !way1, way1);
			root = rotate(root, way1, !way1);
			return root;
		}
		BT<Tkey, Tvalue>::Node* zig_zig(BT<Tkey, Tvalue>::Node* root, bool& way1) {
			root = rotate(root, way1, !way1);
			root = rotate(root, way1, !way1);
			return root;
		}
		BT<Tkey, Tvalue>::Node* zig_or_zag(BT<Tkey, Tvalue>::Node* root, bool& way1, bool& way2) {
			if (way1 == way2) {
				return zig_zig(root, way1);
			}
			if (way1 != way2) {
				return zig_zag(root, way1);
			}
		}
		BT<Tkey, Tvalue>::Node* splay(std::stack<BT<Tkey, Tvalue>::Node*>& nodes, \
			std::stack<bool>& way) {
			auto root = nodes.top(); nodes.pop();

			while (!nodes.empty()) {
				bool way1 = way.top(); way.pop();
				nodes.top()->link[way1] = root;
				auto node = nodes.top(); nodes.pop();
				if (nodes.empty()) {
					root = rotate(node, way1, !way1);
					break;
				}
				root = nodes.top(); nodes.pop();
				bool way2 = way.top(); way.pop();
				root = zig_or_zag(root, way2, way1);
			}
			return root;
		}
		BT<Tkey, Tvalue>::Node* merge(BT<Tkey, Tvalue>::Node* Root) {
			auto l = Root->link[left];
			auto r = Root->link[right];
			delete Root;
			std::stack<typename BT<Tkey, Tvalue>::Node*> nodes;
			std::stack<bool> way;
			if (l != nullptr) {
				nodes.push(l);
				while (l->link[right] != nullptr) {
					way.push(right);
					l = l->link[right];
					nodes.push(l);
				}
				l = splay(nodes, way);
				l->link[right] = r;

				return l;
			}
			else
				return r;
		}
	};
private:

	class finding :public BT<Tkey, Tvalue>::finding_template {
		void balance(std::stack<BT<Tkey, Tvalue>::Node*>& nodes, \
			std::stack<bool>& way, BT<Tkey, Tvalue>::Node*& Root) {
			Help h;
			Root = h.splay(nodes, way);

		}
	};
	class insertion : public BT<Tkey, Tvalue>::insertion_template {
		void balance(std::stack<BT<Tkey, Tvalue>::Node*>& nodes, \
			std::stack<bool>& way, BT<Tkey, Tvalue>::Node*& Root) {
			Help h;
			Root = h.splay(nodes, way);
		}
	};
	class removing : public BT<Tkey, Tvalue>::removing_template {
		void find_kill(const bool& find, BT<Tkey, Tvalue>::Node* Root, \
			std::pair<std::stack<BT<Tkey, Tvalue>::Node*>, std::stack<bool>>& way, \
			Tvalue& value, bool& splay) {
			splay = 1;
		}
	private:
		void balance(std::stack<BT<Tkey, Tvalue>::Node*>& nodes, \
			std::stack<bool>& way, BT<Tkey, Tvalue>::Node*& Root) {
			Help h;
			Root = h.splay(nodes, way);
			Root = h.merge(Root);
		}

	};
public:
	Splay(comparer<Tkey>* comparer) {
		this->_finder = new finding;
		this->_remover = new removing;
		this->_inserter = new insertion;
		this->_comparer = comparer;
	}
};

 
