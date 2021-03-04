#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ms_i multiset<int>::iterator
#define s_i set<int>::iterator
#define v_i vector<int>::iterator
#define m_i map<int, int>::iterator
#define mod 1000000007
struct node
{
    node *left;
    int val;
    node *right;
};
node *create_node(int val)
{
    node *temp = new node;
    temp->val = val;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
node *search(node *root, int val)
{
    queue<node *> q;
    if (root == NULL)
    {
        return NULL;
    }
    q.push(root);
    node *out = NULL;
    while (q.empty() == false)
    {
        node *temp = q.front();
        q.pop();
        if (temp->left != NULL)
        {
            q.push(temp->left);
        }
        if (temp->right != NULL)
        {
            q.push(temp->right);
        }
        if (temp->val == val)
        {
            out = temp;
            cout << "HIT\n";
        }
    }
    return out;
}
void insert(node **root, int val)
{
    if (*root == NULL)
    {
        node *temp = create_node(val);
        *root = temp;
        return;
    }
    queue<node *> q;
    q.push(*root);
    while (!q.empty())
    {
        node *temp = q.front();
        q.pop();
        if (temp->left == NULL)
        {
            temp->left = create_node(val);
            return;
        }
        else
            q.push(temp->left);

        if (temp->right == NULL)
        {
            temp->right = create_node(val);
            return;
        }
        else
            q.push(temp->right);
    }
}
int32_t main()
{
    node *root = NULL;
    for (int i = 0; i < 10; i++)
    {
        insert(&root, i);
    }
    cout << root->left->left->right->val;
}