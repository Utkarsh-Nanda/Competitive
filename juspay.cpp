#include<bits/stdc++.h>
using namespace std;
struct Node
{
	Node *parent_node;
	string value;
	vector<Node *> child_node;
	int is_ancestor_locked, is_decendants_locked, user_id;
	bool isLocked;
	void add_children(vector<string> l, Node *p)
	{
		for (auto &i : l)
		{
			child_node.push_back(new Node(i, p));
		}
	}
	Node(string x, Node *p)
	{
		value = x;
		parent_node = p;
		is_ancestor_locked = 0;
		is_decendants_locked = 0;
		user_id = 0;
		isLocked = false;
	}
};
struct Node *build_tree(Node *root, int &m, vector<string> &s)
{
	queue<Node *> q;
	q.push(root);
	int st = 1;
	while (!q.empty())
	{
		Node *r = q.front();
		q.pop();
		if (st >= s.size())
		{
			continue;
		}
		vector<string> temp;
		for (int i = st; i < st + m; i++)
		{
			temp.push_back(s[i]);
		}
		r->add_children(temp, r);
		st += m;

		for (auto k : r->child_node)
		{
			q.push(k);
		}
	}
	return root;
}

class Tree
{
	private: 
	Node *root;
	map<string, Node *> vton;

	public: 
		Tree(Node *r) 
		{
			root = r;
		}
		Node *get_root()
		{
			return root;
		}
		void fillVtoN(Node *r)
		{
			if (!r)
			{
				return;
			}
			vton[r->value] = r;
			for (auto k : r->child_node)
			{
				fillVtoN(k);
			}
		}
		void inform_decendants(Node *r, int val)
		{
			for (auto k : r->child_node)
			{
				k->is_ancestor_locked += val;
				inform_decendants(k, val);
			}
		}
		bool verify_decendants(Node *r, int &id, vector<Node *> &v)
		{
			if (r->isLocked)
			{
				if (r->user_id != id)
				{
					return false;
				} 
				v.push_back(r);
			}
			if (r->is_decendants_locked == 0)
			{
				return true;
			}
			bool ans = true;
			for (auto k : r->child_node)
			{
				ans &= verify_decendants(k, id, v);
				if (ans == false)
				{
					return false;
				}
			}
			return ans;
		}
		bool lock(string v, int id)
		{
			Node *t = vton[v];
			if (t->isLocked)
			{
				return false;
			}
			if (t->is_ancestor_locked != 0)
			{
				return false;
			}
			if (t->is_decendants_locked != 0)
			{
				return false;
			}
			Node *cur = t->parent_node;
			while (cur)
			{
				cur->is_decendants_locked++;
				cur = cur->parent_node;
			}
			inform_decendants(t, 1);
			t->isLocked = true;
			t->user_id = id;
			return true;
		}
		bool unlock(string v, int id)
		{
			Node *t = vton[v];
			if(!t->isLocked)
			{
				return false;
			}
			if(t->isLocked && t->user_id != id)
			{
				return false;
			}
			Node *cur = t->parent_node;
			while (cur)
			{
				cur->is_decendants_locked--;
				cur = cur->parent_node;
			}
			inform_decendants(t, -1);
			t->isLocked = false;
			return true;
		}
		bool upgrade(string v, int id)
		{
			Node *t = vton[v];
			if (t->isLocked)
			{
				return false;
			}
			if (t->is_ancestor_locked != 0)
			{
				return false;
			}
			if (t->is_decendants_locked == 0)
			{
				return false;
			}
			vector<Node *> vec;
			if (verify_decendants(t, id, vec))
			{
				for (auto k : vec)
				{
					unlock(k->value, id);
				}
			}
			else 
			{
				return false;
			}
			lock(v, id);
			return true;
		}
};

int main()
{
	int n, m, q;
	cin >> n >> m >> q;
	vector<string> s(n);
	for (int i = 0; i < n; i++)
	{
		cin >> s[i];
	}
	Node *r = new Node(s[0], nullptr);
	r = build_tree(r, m, s);
	Tree t(r);
	t.fillVtoN(t.get_root());

	int operation, user_id;
	string sequence;
	for (int i = 0; i < q; i++)
	{
		cin >> operation >> sequence >> user_id;
		if (operation == 1)
		{
			if (t.lock(sequence, user_id))
			{
				cout << "true\n";
			}
			else 
			{
				cout << "false\n";
			}
		}
		else if(operation == 2)
		{
			if (t.unlock(sequence, user_id))
			{
				cout << "true\n";
			}
			else
			{
				cout << "false\n";
			}
		}
		else 
		{
			if (t.upgrade(sequence, user_id))
			{
				cout << "true\n";
			}
			else
			{
				cout << "false\n";
			}
		}
	}
	return 0;
}
