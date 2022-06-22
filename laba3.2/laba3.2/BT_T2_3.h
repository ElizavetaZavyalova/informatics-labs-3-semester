#pragma once
#include "AC.h"

template<typename Tkey, typename Tvalue>
class BT : public AC<Tkey, Tvalue>
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
		BT<Tkey, Tvalue>*me = new  BT<Tkey, Tvalue>(_comparer);
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
class T2_3 : public AC<Tkey, Tvalue>
{
public:
	T2_3(comparer<Tkey>* _comparer) {
		this->_comparer = _comparer;
	}

private:
	comparer<Tkey>* _comparer = nullptr;
	struct Data {
		Tkey key;
		Tvalue value;
		Data() {};
		Data(const Tkey& key, const Tvalue& value) {
			this->key = key;
			this->value = value;
		}
	};
	struct Node
	{
		int size = 0;
		Data data[2];
		Node* link[3];
		Node() {
			for (int i = 0; i < 3; i++) {
				link[i] = nullptr;
			}
		}
		int were_go(const Tkey& key, comparer<Tkey>* _comparer) {
			if (size == 0)
				return not_go;
			if (find(key, _comparer) != 2) {
				return not_go;
			}
			if (_comparer->compare(key, data[0].key) < 0) {
				return left;
			}
			if (size == 1) {
				return right;
			}
			if (_comparer->compare(key, data[1].key) < 0) {
				return centre;
			}
			else
				return right;
		}
		Node(const Tkey& key, const Tvalue& value) :Node() {
			data[0].key = key;
			data[0].value = value;
			size = 1;
		}
		void sort(comparer<Tkey>* _comparer) {
			if (size == 2)
				if (_comparer->compare(data[0].key, data[1].key) > 0) {
					Data d = data[0];
					data[0] = data[1];
					data[1] = d;
				}
		}
		bool set(const Tkey& key, const Tvalue& value) {
			if (size != 2) {
				data[1].key = key;
				data[1].value = value;
				size++;
				return 1;
			}
			return 0;
		}
		int find(const Tkey& key, comparer<Tkey>* _comparer) {
			for (int i = 0; i < size; i++) {
				if (_comparer->compare(data[i].key, key) == 0) {
					return i;
				}
			}
			return 2;
		}
		Data give_central(Data& elem, comparer<Tkey>* _comparer) {
			if (_comparer->compare(data[0].key, elem.key) > 0) {
				Data d = data[0];
				data[0] = elem;
				return d;

			}
			if (_comparer->compare(data[1].key, elem.key) > 0) {
				return elem;
			}
			if (_comparer->compare(data[1].key, elem.key) < 0) {
				Data d = data[1];
				data[1] = elem;
				return d;
			}
		}


	};

private:
	Node* root = nullptr;
protected:
	class insertion_template
	{
	public:
		enum status
		{
			ok,
			duplicate_key
		};
	public:
		status invoke(Node*& root, const Tkey& key, const Tvalue& value, comparer<Tkey>* _comparer)
		{
			if (root == nullptr) {
				root = new Node(key, value);
				return ok;
			}
			std::pair<std::stack<Node*>, std::stack<int>> way = find_way(key, root, _comparer);
			if (!way.first.empty())
			{
				way.first.pop();
				way.second.pop();
				if (way.first.top()->size == 1) {
					way.first.top()->set(key, value);
					way.first.top()->sort(_comparer);
					return ok;

				}
				else {
					Data data(key, value);
					data = way.first.top()->give_central(data, _comparer);
					way.first.top()->link[left] = new Node(way.first.top()->data[0].key, \
						way.first.top()->data[0].value);
					way.first.top()->link[right] = new Node(way.first.top()->data[1].key, \
						way.first.top()->data[1].value);
					way.first.top()->data[0] = data;
					way.first.top()->size = 1;
					Node* nod = way.first.top();
					way.first.pop();
					while (!way.first.empty()) {
						nod = plus(way.first.top(), nod, way.second.top(), _comparer);
						if (nod->size == 2) {
							return ok;
						}
						way.first.pop();
						way.second.pop();

					}
					root = nod;
					return ok;
				}



			}
			return duplicate_key;
		}
	private:
		std::pair<std::stack<Node*>, std::stack<int>> find_way(const Tkey& key, Node* root, \
			comparer<Tkey>* _comparer)
		{
			std::pair<std::stack<Node*>, std::stack<int>> way;
			way.first.push(root);
			while (root != nullptr) {
				int l = root->were_go(key, _comparer);
				if (l == not_go) {
					std::pair<std::stack<Node*>, std::stack<int>> way1;
					return way1;
				}
				else {
					root = root->link[l];
					way.second.push(l);
					way.first.push(root);
				}
			}
			return way;

		}
		Node* plus(Node*& me, Node* nod, int way, comparer<Tkey>* _comparer) {
			if (way == left) {
				if (me->size == 1) {
					me->link[centre] = nod->link[right];
					me->link[left] = nod->link[left];
					me->set(nod->data[0].key, nod->data[0].value);
					me->sort(_comparer);
					delete nod;
					return me;
				}
				Node* root = new Node(me->data[0].key, me->data[0].value);
				root->link[left] = nod;
				root->link[right] = me;
				me->data[0] = me->data[1];
				me->size = 1;
				me->link[left] = me->link[centre];
				return root;

			}
			if (way == right) {
				if (me->size == 1) {
					me->link[centre] = nod->link[left];
					me->link[right] = nod->link[right];
					me->set(nod->data[0].key, nod->data[0].value);
					me->sort(_comparer);
					delete nod;
					return me;
				}
				Node* root = new Node(me->data[1].key, me->data[1].value);
				root->link[right] = nod;
				root->link[left] = me;
				me->size = 1;
				me->link[right] = me->link[centre];
				return root;
			}
			if (way == centre) {
				Node* root = new Node(me->data[1].key, me->data[1].value);
				me->size = 1;
				root->link[left] = nod->link[right];
				nod->link[right] = root;
				me->link[right] = nod->link[left];
				nod->link[right] = me;
				return nod;
			}
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
		status invoke(Node*& root, const Tkey& key, Tvalue& value, comparer<Tkey>* _comparer) {
			if (root == nullptr) {

				return key_not_found;
			}
			std::pair<std::stack<Node*>, std::stack<int>> way = find_way(key, root, _comparer, \
				value);
			if (!way.first.empty()) {
				Node* kill = way.first.top(); way.first.pop();
				if (kill->size == 1) {
					return ok;
				}
				if (way.first.empty()) {
					delete kill;
					root = nullptr;
				}
				Node* parent = kill;
				while (!way.first.empty()) {
					kill = parent;
					parent = way.first.top();
					way.first.pop();
					if (parent->size == 2) {

						parent2(parent, way.second.top());
						return ok;
					}
					if (parent->link[(way.second.top() + 1) % 2]->size == 2) {
						chield2(parent, way.second.top());
						return ok;
					}
					fix(parent, way.second.top());
					way.second.pop();
				}
				delete parent;
				root = kill;
				return ok;


			}

		}
	private:
		void fix(Node* parent, int& way) {
			if (parent->link[way]->link[(way + 1) % 2] != nullptr) {
				parent->link[way]->link[way] = parent->link[way]->link[(way + 1) % 2];
				parent->link[way]->link[(way + 1) % 2] = nullptr;
			}
			if (way == left) {
				parent->link[left]->size = 2;
				parent->link[left]->data[0] = parent->data[0];
				parent->link[left]->data[1] = parent->link[right]->data[0];
				parent->link[left]->link[centre] = parent->link[right]->link[left];
				parent->link[left]->link[right] = parent->link[right]->link[right];
				delete parent->link[right];
				parent->size = 0;
				parent->link[right] = nullptr;
				return;

			}
			if (way == right) {
				parent->link[right]->size = 2;
				parent->link[right]->data[1] = parent->data[0];
				parent->link[right]->data[0] = parent->link[left]->data[0];
				parent->link[right]->link[centre] = parent->link[left]->link[right];
				parent->link[right]->link[left] = parent->link[left]->link[left];
				delete parent->link[left];
				parent->size = 0;
				parent->link[left] = nullptr;
				return;
			}

		}
		void parent2(Node* parent, int& way) {
			int part = (way == centre ? left : way);
			if (parent->link[part]->link[(part + 1) % 2] != nullptr) {
				parent->link[part]->link[part] = parent->link[part]->link[(part + 1) % 2];
				parent->link[part]->link[(part + 1) % 2] = nullptr;
			}
			if (way == left) {
				if (parent->link[centre]->size == 2) {
					parent->link[left]->size = 1;
					parent->link[left]->data[0] = parent->data[0];
					parent->data[0] = parent->link[centre]->data[0];
					parent->link[left]->link[right] = parent->link[centre]->link[left];
					parent->link[centre]->data[0] = parent->link[centre]->data[1];
					parent->link[centre]->size = 1;
					parent->link[centre]->link[left] = parent->link[centre]->link[centre];
					parent->link[centre]->link[centre] = nullptr;
					return;
				}
				else {
					parent->size = 1;
					parent->link[left]->size = 2;
					parent->link[left]->data[0] = parent->link[centre]->data[0];
					parent->link[left]->data[1] = parent->data[0];
					parent->data[0] = parent->data[1];
					parent->link[left]->link[centre] = parent->link[centre]->link[left];
					parent->link[left]->link[right] = parent->link[centre]->link[right];
					delete parent->link[centre];
					parent->link[centre] = nullptr;
					return;
				}
			}
			if (way == right) {
				if (parent->link[centre]->size == 2) {
					parent->link[right]->size = 1;
					parent->link[right]->data[0] = parent->data[1];
					parent->data[1] = parent->link[centre]->data[1];
					parent->link[right]->link[left] = parent->link[centre]->link[right];
					parent->link[centre]->size = 1;
					parent->link[centre]->link[right] = parent->link[centre]->link[centre];
					parent->link[centre]->link[centre] = nullptr;
					return;
				}
				else {
					parent->size = 1;
					parent->link[right]->size = 2;
					parent->link[right]->data[0] = parent->link[centre]->data[0];
					parent->link[right]->data[1] = parent->data[1];
					parent->link[right]->link[centre] = parent->link[centre]->link[right];
					parent->link[right]->link[left] = parent->link[centre]->link[left];
					delete parent->link[centre];
					parent->link[centre] = nullptr;
					return;

				}
			}
			if (way == centre) {
				if (parent->link[right]->size == 2) {
					parent->link[centre]->size = 1;
					parent->link[centre]->data[0] = parent->data[1];
					parent->data[1] = parent->link[right]->data[0];
					parent->link[centre]->link[right] = parent->link[right]->link[left];
					parent->link[right]->data[0] = parent->link[right]->data[1];
					parent->link[right]->size = 1;
					parent->link[right]->link[left] = parent->link[right]->link[centre];
					parent->link[right]->link[centre] = nullptr;
					return;

				}
				else {
					parent->size = 1;
					parent->link[right]->size = 2;
					parent->link[right]->data[1] = parent->link[right]->data[0];
					parent->link[right]->data[0] = parent->data[1];
					parent->link[right]->link[centre] = parent->link[right]->link[left];
					parent->link[right]->link[left] = parent->link[centre]->link[left];
					delete parent->link[centre];
					parent->link[centre] = nullptr;
					return;

				}
			}
		}
		void chield2(Node* parent, int& way) {
			if (parent->link[way]->link[(way + 1) % 2] != nullptr) {
				parent->link[way]->link[way] = parent->link[way]->link[(way + 1) % 2];
				parent->link[way]->link[(way + 1) % 2] = nullptr;
			}
			if (way == left) {
				parent->link[left]->size = 1;
				parent->link[right]->size = 1;
				parent->link[left]->data[0] = parent->data[0];
				parent->data[0] = parent->link[right]->data[0];
				parent->link[right]->data[0] = parent->link[right]->data[1];
				parent->link[left]->link[right] = parent->link[right]->link[left];
				parent->link[right]->link[left] = parent->link[right]->link[centre];
				parent->link[right]->link[centre] = nullptr;
				return;

			}
			if (way == right) {
				parent->link[right]->size = 1;
				parent->link[left]->size = 1;
				parent->link[right]->data[0] = parent->data[0];
				parent->data[0] = parent->link[left]->data[1];
				parent->link[right]->link[left] = parent->link[left]->link[right];
				parent->link[left]->link[right] = parent->link[left]->link[centre];
				parent->link[left]->link[centre] = nullptr;
				return;
			}

		}
	private:
		std::pair<std::stack<Node*>, std::stack<int>> find_way(const Tkey& key, Node* root, \
			comparer<Tkey>* _comparer, Tvalue& value)
		{
			std::pair<std::stack<Node*>, std::stack<int>> way;
			way.first.push(root);
			while (root != nullptr) {
				int l = root->were_go(key, _comparer);
				if (l == not_go) {
					break;
				}
				else {
					root = root->link[l];
					way.second.push(l);
					way.first.push(root);
				}
			}
			if (root == nullptr) {
				std::pair<std::stack<Node*>, std::stack<int>> way1;
				return way1;
			}
			Node* kill = root;

			bool elem = kill->find(key, _comparer);
			value = root->data[elem].value;
			if (root->link[left] == nullptr) {
				root->data[0] = root->data[!elem];
				root->size--;
				return way;
			}
			if (root->link[elem] != nullptr) {
				way.second.push(elem);
				way.first.push(root->link[elem]);
				root = root->link[elem];
				while (root->link[!elem] != nullptr) {
					way.second.push(!elem);
					way.first.push(root->link[!elem]);
					root = root->link[!elem];
				}
			}
			if (root->size == 2) {
				kill->data[elem] = root->data[!elem];
				root->data[0] = root->data[elem];
				root->size = 1;
			}
			else if (root->size == 1) {
				kill->data[elem] = root->data[0];
				root->size = 0;
			}
			return way;
		}


	};

	class finding_template
	{
	public:
		enum status
		{
			ok,
			key_not_found
		};
		status invoke(Node*& root, const Tkey& key, Tvalue*& value, comparer<Tkey>* _comparer)
		{
			if (root == nullptr) {
				return key_not_found;
			}
			Node* node = find_way(key, root, _comparer);
			if (node != nullptr) {
				value = &(node->data[node->find(key, _comparer)].value);
				return ok;
			}
			return key_not_found;
		}
		Node* find_way(const Tkey& key, Node* root, \
			comparer<Tkey>* _comparer)
		{

			while (root != nullptr) {
				int l = root->were_go(key, _comparer);
				if (l == not_go) {

					return root;
				}
				else {
					root = root->link[l];

				}
			}
			return root;

		}


	};
	finding_template _finder;
	removing_template _remover;
	insertion_template _inserter;
public:
	void insert(const Tkey& key, const Tvalue& value) override
	{

		if (_inserter.invoke(root, key, value, _comparer) != 0) {
			throw tree_exception<Tkey, Tvalue>::tree_exception("dublicate key", key, value);
		}



	}

	Tvalue remove(const Tkey& key) override
	{
		Tvalue value = 0;
		if (_remover.invoke(root, key, value, _comparer) != 0) {
			throw tree_exception<Tkey, Tvalue>::tree_exception("key_not_found", key);
		}
		return value;
	}

	Tvalue& find(const Tkey& key) override
	{
		Tvalue* value = nullptr;
		if (_finder.invoke(root, key, value, _comparer) != 0) {
			throw tree_exception<Tkey, Tvalue>::tree_exception("key_not_found", key);
		}
		return *value;
	}

	void destroy(Node* node) {
		if (node == nullptr)
			return;
		destroy(node->link[left]);
		destroy(node->link[right]);
		destroy(node->link[centre]);
		delete node;
	}
	void coppy(Node* els, const Node* my) {
		if (my == nullptr) {
			return;
		}
		els->size = my->size;
		els->data[0] = my->data[0];
		els->data[1] = my->data[1];

		if (my->link[left] != nullptr) {
			els->link[left] = new Node;
			coppy(els->link[left], my->link[left]);
		}
		if (my->link[right] != nullptr) {
			els->link[right] = new Node;
			coppy(els->link[right], my->link[right]);
		}
		if (my->link[centre] != nullptr) {
			els->link[centre] = new Node;
			coppy(els->link[centre], my->link[centre]);
		}
	}
	void coppy_ptr(AC<Tkey, Tvalue>*& my) {
		T2_3<Tkey, Tvalue>* me = new  T2_3<Tkey, Tvalue>(_comparer);
		T2_3<Tkey, Tvalue>* obj = dynamic_cast<T2_3<Tkey, Tvalue>*>(this);
		if (obj->root != nullptr) {
			me->root = new Node;
			coppy(me->root, obj->root);
		}
		my = me;
	}
	T2_3(const T2_3<Tkey, Tvalue>& obj) {
		this->_comparer = obj._comparer;

		if (root != nullptr) {
			destroy(root);
			root = nullptr;
		}
		if (obj.root != nullptr) {
			root = new Node;
			coppy(root, obj.root);
		}
	};
	void operator=(const T2_3<Tkey, Tvalue>& obj) {
		this->_comparer = obj.comp;

		if (root != nullptr) {
			destroy(root);
			root = nullptr;
		}
		if (obj.root != nullptr) {
			root = new Node;
			coppy(root, obj.root);
		}

	};
	~T2_3() {
		destroy(root);
		root = nullptr;
	};
};
