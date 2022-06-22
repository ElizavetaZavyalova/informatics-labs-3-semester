#pragma once
#include "BT_T2_3.h"

template<typename Tkey, typename Tvalue>
class RB : public BT<Tkey, Tvalue> {
public:
	void coppy_ptr(AC<Tkey, Tvalue>*& my) {
		RB<Tkey, Tvalue>* me = new  RB<Tkey, Tvalue>(this->_comparer);
		RB<Tkey, Tvalue>* obj = dynamic_cast<RB<Tkey, Tvalue>*> (this);
		if (obj->root != nullptr) {
			me->root = new NodeRB;
			this->coppy(me->root, obj->root);
		}
		my = me;
	}
private:
	class help {
	public:
		bool get_color(BT<Tkey, Tvalue>::Node*& n) {
			if (n == nullptr) {
				return Black;
			}
			return n->bf();
		}
		BT<Tkey, Tvalue>::Node* rebalans(BT<Tkey, Tvalue>::Node* root, const bool& way, bool& end) {
			if (root->link[!way] == nullptr) {
				return brother_black_no_red(root, way, end);
			}
			if (get_color(root->link[!way]) == Red) {
				return brother_red(root, way, end);
			}
			else if (get_color(root->link[!way]->link[!way]) == Red) {
				return brother_black_nocentre_red(root, way, end);
			}
			else if (get_color(root->link[!way]->link[way]) == Red) {
				return brother_black_centre_red(root, way, end);
			}
			else {
				return brother_black_no_red(root, way, end);
			}
		}
		BT<Tkey, Tvalue>::Node* brother_red(BT<Tkey, Tvalue>::Node* root, const bool& way, bool& end) {
			auto nod = root->link[way];
			root->link[!way] = nod->link[way];
			nod->link[way] = root;
			root = nod;
			root->bf(Black);
			root->link[way]->bf(Red);
			root->link[way] = rebalans(root->link[way], way, end);
			return root;
		}
		BT<Tkey, Tvalue>::Node* brother_black_no_red(BT<Tkey, Tvalue>::Node* root, const bool& way, bool& end) {
			if (root->bf() == Red)
				end = 1;
			root->bf(Black);
			if (root->link[!way] == nullptr)
				return root;
			root->link[!way]->bf(Red);
			return root;

		}
		BT<Tkey, Tvalue>::Node* brother_black_centre_red(BT<Tkey, Tvalue>::Node* root, const bool& way, bool& end) {
			auto node = root->link[!way];
			root->link[!way] = root->link[!way]->link[way];
			node->link[!way] = root->link[!way]->link[!way];
			root->link[!way]->link[!way] = node;
			root->link[!way]->bf(Black);
			root->link[!way]->link[!way]->bf(Red);
			return brother_black_nocentre_red(root, way, end);
		}
		BT<Tkey, Tvalue>::Node* brother_black_nocentre_red(BT<Tkey, Tvalue>::Node* root, const bool& way, bool& end) {
			auto node = root->link[!way];
			root->link[!way] = node->link[way];
			node->link[way] = root;
			root = node;
			root->bf(root->link[way]->bf());
			root->link[way]->bf(Black);
			root->link[!way]->bf(Black);
			end = 1;
			return root;
		}
		BT<Tkey, Tvalue>::Node* balans(BT<Tkey, Tvalue>::Node* root, bool* w) {
			int s1 = w[0]; int s2 = (s1 + 1) % 2;
			if (w[0] != w[1]) {
				auto nod = root->link[s1];
				root->link[s1] = nod->link[s2];
				nod->link[s2] = nod->link[s2]->link[s1];
				root->link[s1]->link[s1] = nod;

			}

			if (this->get_color(root->link[s2]) == Red) {
				root->bf(Red);
				root->link[s1]->bf(Black);
				root->link[s2]->bf(Black);
			}
			else {
				auto nod = root->link[s1];
				root->link[s1] = root->link[s1]->link[s2];
				nod->link[s2] = root;
				root = nod;
				root->bf(Black);
				root->link[s2]->bf(Red);
			}
			return root;
		}
	};

private:
	struct NodeRB :public BT<Tkey, Tvalue>::Node {
		bool color = Black;

	public:
		NodeRB(Tkey key, Tvalue value) :BT<Tkey, Tvalue>::Node(key, value) {}
		NodeRB() :BT<Tkey, Tvalue>::Node() {};
		int bf() {
			return color;
		}
		void bf(int h) {
			color = h;
		}

	};


private:

	class finding :public BT<Tkey, Tvalue>::finding_template {
		void balance(std::stack<BT<Tkey, Tvalue>::Node*>& nodes, \
			std::stack<bool>& way, BT<Tkey, Tvalue>::Node*& Root) {

		}
	};
	class insertion : public BT<Tkey, Tvalue>::insertion_template {
		BT<Tkey, Tvalue>::Node* set(const Tkey& key, const Tvalue& value) {
			return new NodeRB(key, value);
		}
	public:
		BT<Tkey, Tvalue>::Node* set() {
			return new NodeRB;
		}
		void set_bf(BT<Tkey, Tvalue>::Node*& me, BT<Tkey, Tvalue>::Node*& obj) {
			me->bf(obj->bf());
		}
	private:
		void balance(std::stack<BT<Tkey, Tvalue>::Node*>& nodes, \
			std::stack<bool>& way, BT<Tkey, Tvalue>::Node*& Root) {
			nodes.top()->bf(Red); help f;
			bool w[2];
			auto nod = nodes.top(); nodes.pop();
			auto nod1 = nodes.top(); nodes.pop();
			while (!nodes.empty()) {
				if (nod1->bf() == Black || nod->bf() == Black) {
					break;
				}
				w[1] = way.top(); way.pop();
				w[0] = way.top(); way.pop();
				nod = nodes.top(); nodes.pop();
				nod = f.balans(nod, w);
				if (nodes.empty()) {
					Root = nod;
					break;
				}
				nod1 = nodes.top(); nodes.pop();
				nod1->link[way.top()] = nod;
			}
			Root->bf(Black);
			return;
		}
	};
	class removing : public BT<Tkey, Tvalue>::removing_template {

		void balance(std::stack<BT<Tkey, Tvalue>::Node*>& nodes, \
			std::stack<bool>& way, BT<Tkey, Tvalue>::Node*& Root) {
			if (nodes.top()->bf() == Red) {
				return;
			}
			nodes.pop(); help f; bool end = 0;
			auto nod = nodes.top(); nodes.pop();
			while (!nodes.empty() && !end) {
				nodes.top()->link[way.top()] = nod;
				nod = nodes.top(); nodes.pop();
				nod = f.rebalans(nod, way.top(), end);
				way.pop();
			}
			if (nodes.empty()) {
				Root = nod;
				Root->bf(Black);
			}
			else {
				nodes.top()->link[way.top()] = nod;
			}

		}
	};
public:
	RB(comparer<Tkey>* comparer) {
		this->_finder = new finding;
		this->_remover = new removing;
		this->_inserter = new insertion;
		this->_comparer = comparer;
	}
};

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

template<typename Tkey, typename Tvalue>
class AVL : public BT<Tkey, Tvalue> {
public:
	void coppy_ptr(AC<Tkey, Tvalue>*& my) {
		AVL<Tkey, Tvalue>* me = new  AVL<Tkey, Tvalue>(this->_comparer);
		AVL<Tkey, Tvalue>* obj = dynamic_cast<AVL<Tkey, Tvalue>*> (this);
		if (obj->root != nullptr) {
			me->root = new NodeAVL;
			this->coppy(me->root, obj->root);
		}
		my = me;
	}
private:
	class help {
	public:
		int get_height(BT<Tkey, Tvalue>::Node*& n) {
			if (n == nullptr) {
				return 0;
			}
			return n->bf();
		};
		int set_height(BT<Tkey, Tvalue>::Node*& n) {
			if (n == nullptr) {
				return 0;
			}
			(get_height(n->link[left]) > get_height(n->link[right])) ? \
				n->bf(get_height(n->link[left]) + 1) :\
				n->bf(get_height(n->link[right]) + 1);
			return n->bf();
		}
		int balans_factor(BT<Tkey, Tvalue>::Node* node) {
			return get_height(node->link[right]) - get_height(node->link[left]);
		}
		BT<Tkey, Tvalue>::Node* rotate(BT<Tkey, Tvalue>::Node* root, side s1, side s2) {
			auto node = root->link[s1];
			root->link[s1] = node->link[s2];
			node->link[s2] = root;
			set_height(root);
			set_height(node);
			return node;
		}
	};
private:

	struct NodeAVL :public BT<Tkey, Tvalue>::Node {
		int height = 1;

	public:
		NodeAVL(Tkey key, Tvalue value) :BT<Tkey, Tvalue>::Node(key, value) {}
		NodeAVL() :BT<Tkey, Tvalue>::Node() {};
		int bf() {
			return height;
		}
		void bf(int h) {
			height = h;
		}

	};

	class finding :public BT<Tkey, Tvalue>::finding_template {
		void balance(std::stack<BT<Tkey, Tvalue>::Node*>& nodes, \
			std::stack<bool>& way, BT<Tkey, Tvalue>::Node*& Root) {

		}
	};
	class insertion : public BT<Tkey, Tvalue>::insertion_template {
		BT<Tkey, Tvalue>::Node* set(const Tkey& key, const Tvalue& value) {
			return new NodeAVL(key, value);
		}
	public:
		BT<Tkey, Tvalue>::Node* set() {
			return new NodeAVL;
		}
		void set_bf(BT<Tkey, Tvalue>::Node*& me, BT<Tkey, Tvalue>::Node*& obj) {
			me->bf(obj->bf());
		}
	private:
		void balance(std::stack<BT<Tkey, Tvalue>::Node*>& nodes, \
			std::stack<bool>& way, BT<Tkey, Tvalue>::Node*& Root) {
			auto nod = nodes.top(); nodes.pop(); help f;
			while (!nodes.empty()) {
				nodes.top()->link[way.top()] = nod; way.pop();
				nod = nodes.top(); nodes.pop();
				f.set_height(nod);
				if (f.balans_factor(nod) == 2) {
					if (f.balans_factor(nod->link[right]) < 0)
						nod->link[right] = f.rotate(nod->link[right], left, right);
					nod = f.rotate(nod, right, left);
				}
				else if (f.balans_factor(nod) == -2) {
					if (f.balans_factor(nod->link[left]) > 0)
						nod->link[left] = f.rotate(nod->link[left], right, left);
					nod = f.rotate(nod, left, right);
				}
			}
			Root = nod;

		}
	};
	class removing : public BT<Tkey, Tvalue>::removing_template {

		void balance(std::stack<BT<Tkey, Tvalue>::Node*>& nodes, \
			std::stack<bool>& way, BT<Tkey, Tvalue>::Node*& Root) {
			nodes.pop();
			auto nod = nodes.top(); nodes.pop(); help f;
			while (!nodes.empty()) {
				nodes.top()->link[way.top()] = nod; way.pop();
				nod = nodes.top(); nodes.pop();
				f.set_height(nod);
				if (f.balans_factor(nod) == 2) {
					if (f.balans_factor(nod->link[right]) < 0)
						nod->link[right] = f.rotate(nod->link[right], left, right);
					nod = f.rotate(nod, right, left);
				}
				else if (f.balans_factor(nod) == -2) {
					if (f.balans_factor(nod->link[left]) > 0)
						nod->link[left] = f.rotate(nod->link[left], right, left);
					nod = f.rotate(nod, left, right);
				}
			}
			Root = nod;

		}
	};
public:
	AVL(comparer<Tkey>* comparer) {
		this->_finder = new finding;
		this->_remover = new removing;
		this->_inserter = new insertion;
		this->_comparer = comparer;
	}
};
