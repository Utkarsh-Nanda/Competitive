#include <bits/stdc++.h>
using namespace std;
struct node
{
    node *left;
    node *right;
    int val;
};
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
int height(node *root)
{
    int lheight = 0, rheight = 0;
    if (root == NULL)
        return 0;
    else
    {
        lheight = height(root->left);
        rheight = height(root->right);
        return max(lheight, rheight) + 1;
    }
}
node *create_node(int key)
{
    node *temp = new node();
    temp->left = NULL;
    temp->right = NULL;
    temp->val = key;
    return temp;
}
node *insert(node *root, int key)
{
    if (root == NULL) // insert a new node
    {
        node *new_node = create_node(key);
        return new_node;
    }
    if (root->val == key)
    {
        cout << "Value already exists!\n";
        return root;
    }
    else if (key > root->val)
    {
        root->right = insert(root->right, key);
        return root;
    }
    else
    {
        root->left = insert(root->left, key);
        return root;
    }
}
void print_inorder(node *root)
{
    if (root != NULL)
    {
        print_inorder(root->left);
        cout << root->val << " ";
        print_inorder(root->right);
    }
}
node *search(node *root, int key)
{
    if (root == NULL || root->val == key)
        return root;
    if (key > root->val)
        return search(root->right, key);
    if (key < root->val)
        return search(root->left, key);
}
node *min_val(node *root)
{
    if (root == NULL)
        return NULL;
    else if (root->left == NULL && root->right == NULL)
        return root;
    else if (root->left != NULL)
        return min_val(root->left);
    else
        return root;
}

int32_t main()
{ // 5,2 ,1 24, 9, 4, 22
    node *start = NULL;
    start = insert(start, 5);
    start = insert(start, 2);
    start = insert(start, 1);
    start = insert(start, 24);
    start = insert(start, 9);
    start = insert(start, 4);
    start = insert(start, 22);
    cout << "inserted\n";
    print_tree(start, height(start) - 1);
    search(start, 90) != NULL ? cout << "\nSearch location : " << search(start, 90)->val : cout << "\nSearch location : " << -1;
    cout << "\n" << min_val(start)->val << "\n";
    start = delete_node(start, 2);
    print_tree(start, height(start) - 1);
}