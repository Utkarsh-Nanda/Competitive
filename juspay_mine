#include <bits/stdc++.h>
using namespace std;
struct Node
{
    bool isResourceInUse;
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
    bool isRunning;
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
    bool lock(Tree *tt , string v, int id)
    {
        // if (tt->isRunning)
        //     while (tt->isRunning)
        //         ;
        // tt->isRunning = true;
        Node *t = vton[v];
        // if (t->isResourceInUse) //
            // while (t->isResourceInUse) //
                // ;
        // t->isResourceInUse = true; //
        if (t->isLocked || t->is_ancestor_locked != 0 || t->is_decendants_locked != 0)
        {
            // t->isResourceInUse = false;
            return false;
        }
        Node *cur = t->parent_node;
        vector<Node *> st;
        while (cur)
        {
            // if (cur->isResourceInUse)
            //     while (cur->isResourceInUse)
            //     ;
            // cur->isResourceInUse = true; //
            // st.push_back(cur); 
            // if (cur->isLocked)
            // {
            //     for (int i = 0; i < st.size(); i++)
            //     {
            //         st[i]->isResourceInUse = false;
            //     }
            //     return false;
            // }
            cur->is_decendants_locked++;
            // cur->isResourceInUse = false; //
            cur = cur->parent_node;
        }
        inform_decendants(t, 1);
        t->isLocked = true;
        t->user_id = id;
        // t->isResourceInUse = false; // 
        // tt->isRunning = false;
        return true;
    }
    bool unlock(Tree *tt, string v, int id)
    {
        // if (tt->isRunning)
        //     while (tt->isRunning)
        //         ;
        // tt->isRunning = true;
        Node *t = vton[v];
        if (!t->isLocked)
        {
            return false;
        }
        if (t->isLocked && t->user_id != id)
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
        // tt->isRunning = false;
        return true;
    }
    bool upgrade(Tree *tt, string v, int id)
    {
        // if (tt->isRunning)
        //     while (tt->isRunning)
        //         ;
        // tt->isRunning = true;
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
                unlock(tt, k->value, id);
            }
        }
        else
        {
            return false;
        }
        lock(tt, v, id);
        // tt->isRunning = false;
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
    t.isRunning = false;
    int operation, user_id;
    string sequence;
    for (int i = 0; i < q; i++)
    {
        cin >> operation >> sequence >> user_id;
        if (t.isRunning)
            while (t.isRunning)
                ;
        t.isRunning = true;
        if (operation == 1)
        {
            if (t.lock(&t, sequence, user_id))
            {
                cout << "true\n";
            }
            else
            {
                cout << "false\n";
            }
        }
        else if (operation == 2)
        {
            if (t.unlock(&t, sequence, user_id))
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
            if (t.upgrade(&t, sequence, user_id))
            {
                cout << "true\n";
            }
            else
            {
                cout << "false\n";
            }
        }
        t.isRunning = false;
    }
    return 0;
}
