#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ms_i multiset<int>::iterator
#define s_i set<int>::iterator
#define v_i vector<int>::iterator
#define m_i map<int, int>::iterator
#define mod 1000000007
#define capacity 10
class node
{
public:
    node *left;
    int val;
    node *right;
};
class BinaryTree
{
public:
    int ar[capacity];
    int size;
    int leftIndex(int);
    int rightIndex(int);
    int parentIndex(int);
    int search(int);
    void delete_last();
    void insert(int);
    void display();
    BinaryTree();
    bool isEmpty();
};

BinaryTree::BinaryTree()
{
    size = 0;
}
int BinaryTree::search(int key)
{
    for (int i = 0; i < size; i++)
    {
        if (ar[i] == key)
        {
            return i + 1;
        }
    }
    cout << "Key not found in the tree!\n";
    return -1;
}
void BinaryTree::insert(int key)
{
    if (size == capacity)
    {
        cout << "Max capacity reached!\n";
        return;
    }
    ar[size] = key;
    size++;
}
void BinaryTree::display()
{
    for (int i = 0; i < size; i++)
    {
        cout << ar[i] << " ";
    }
}
void BinaryTree::delete_last()
{
    if (size > 0)
    {
        ar[size - 1] = -1;
        size--;
    }
    else
    {
        cout << "No element in the tree to delete!\n";
    }
}
int BinaryTree::leftIndex(int key)
{
    int index = search(key);
    if (index != -1)
        return 2 * search(key);
    else
        return -1;
}
int BinaryTree::rightIndex(int key)
{
    int index = search(key);
    if (index != -1)
        return 2 * search(key) + 1;
    else
        return -1;
}
int BinaryTree::parentIndex(int key)
{
    int index = search(key);
    if (index != -1)
        return index / 2;
    else
        return -1;
}
bool BinaryTree::isEmpty()
{
    if (size == 0)
        return true;
    else
        return false;
}


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
void extreme_right_to_null(node *start, node *extremeRight)
{
    queue<node *> q;
    node *temp = NULL;
    q.push(start);
    while (q.empty() == false)
    {
        temp = q.front();
        q.pop();
        if (temp->left != NULL)
            if (temp->left == extremeRight)
            {
                temp->left = NULL;
                cout << "FOUND\n";
                return;
            }
            else
            {
                q.push(temp->left);
            }
        if (temp->right != NULL)
            if (temp->right == extremeRight)
            {
                temp->right = NULL;
                cout << "FOUND\n";
                return;
            }
            else
            {
                q.push(temp->right);
            }
    }
}
void delete_node(node *start, int key)
{
    node *nodetodelete = search(start, key);
    if (nodetodelete == NULL)
        cout << "NODE doesnt't exist\n";
    else
    {
        queue<node *> q;
        q.push(start);
        node *temp = NULL;
        while (q.empty() == false)
        {
            temp = q.front();
            q.pop();
            if (temp->left != NULL)
                q.push(temp->left);
            if (temp->right != NULL)
                q.push(temp->right);
        }
        int deepest_right_key = temp->val;
        nodetodelete->val = deepest_right_key;

        extreme_right_to_null(start, temp);
    }
}
void dft_inorder(node *root)
{
    if (root == NULL)
        return;
    else
    {
        dft_inorder(root->left);
        cout << root->val << ", ";
        dft_inorder(root->right);
    }
}
void dft_preorder(node *root)
{
    if (root == NULL)
        return;
    else
    {
        cout << root->val << ", ";
        dft_preorder(root->left);
        dft_preorder(root->right);
    }
}
void dft_preorder_max(node *root, int *mxm)
{
    if (root == NULL)
        return;
    else
    {
        cout << root->val << ", ";
        *mxm = max(*mxm, root->val);
        dft_preorder_max(root->left, mxm);
        dft_preorder_max(root->right, mxm);
    }
}
void dft_postorder(node *root)
{
    if (root == NULL)
        return;
    else
    {
        dft_postorder(root->left);
        dft_postorder(root->right);
        cout << root->val << ", ";
    }
}
string print_bft_level(node *root, int level)
{
    if (root == NULL)
        return "-";
    else if (level == 1)
        return to_string(root->val);
    else if (level > 1)
        return print_bft_level(root->left, level - 1) + ", " + print_bft_level(root->right, level - 1);
}
void print_tree(node *root, int height)
{
    for (int i = 1; i <= height + 1; i++)
    {
        cout << print_bft_level(root, i) << "\n";
    }
}

int32_t main()
{
    BinaryTree bt;

    cout << bt.search(3);
    cout << "\n";
    bt.display();
    bt.delete_last();
    bt.delete_last();
    cout << "\n";
    bt.display();
    cout << "\n"
         << bt.leftIndex(2);
    cout << "\n"
         << bt.isEmpty();
}