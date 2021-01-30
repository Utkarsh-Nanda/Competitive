#include <bits/stdc++.h>
#define lld long long int
using namespace std;
struct node
{
  int a;
  struct node *next;
};

//node *first = NULL;
node *create(int a[], int n)
{
  node *temp;
  node *last;

  node *fi = new node;
  temp = fi;
  temp->a = a[0];
  temp->next = NULL;
  last = fi;
  for (int i = 1; i < n; i++)
  {
    temp = new node;
    temp->a = a[i];
    temp->next = NULL;
    last->next = temp;
    last = temp;
  }
  return fi;
}
void display(struct node *fir)
{
  cout << fir->a << " ";
  if (fir->next != NULL)
  {
    display(fir->next);
  }
}
int count(struct node *fir)
{
  static int counter = 0;
  counter++;
  if (fir->next != NULL)
  {
    count(fir->next);
  }
  else
    return counter;
}
int sum(struct node *fir)
{
  static int suma = 0;
  suma += fir->a;
  if (fir->next != NULL)
  {
    sum(fir->next);
  }
  else
    return suma;
}
int max(struct node *fir)
{
  static int maxi = 0;
  maxi = max(maxi, fir->a);
  if (fir->next != NULL)
  {
    max(fir->next);
  }
  else
    return maxi;
}
bool search(struct node *fir, int key)
{
  if (fir->a == key)
    return true;
  if (fir->next == NULL)
    return false;

  else
    search(fir->next, key);
}
node *insert(struct node *fir, int pos, int val)
{
  node *fi = fir;
  node *counter = fir;
  node *temp = new node;
  temp->a = val;
  if (fir == NULL)
  {
    temp->next = NULL;
    fi = temp;
  }
  else
  {
    while (pos-- > 2)
    {
      counter = counter->next;
    }
    temp->next = counter->next;
    counter->next = temp;
  }
  return fi;
}
node *sortedInsert(struct node *fir, int x)
{
  node *fi = fir;
  node *temp = new node;
  temp->a = x;
  node *p = fir;
  if (fir == NULL)
  {
    temp->next = NULL;
    fi = temp;
  }
  else if (fir->next == NULL)
  {
    if (x > fir->a)
    {
      fir->next = temp;
      temp->next = NULL;
    }
    else
    {
      temp->next = fir;
      fi = temp;
    }
  }
  else
  {

    while (p->next->a < x && p->next != NULL)
    {

      p = p->next;
    }
    temp->next = p->next;
    p->next = temp;
  }
  return fi;
}
node *delete_node(struct node *fir, int val)
{
  node *fi = fir;
  node *temp = NULL;
  if (fir->next == NULL)
  {
    fi = NULL;
    delete (fir);
  }
  else
  {
    while (fir->next->a != val)
    {
      fir = fir->next;
    }
    temp = fir->next;
    fir->next = fir->next->next;
    delete (temp);
  }
  return fi;
}
node *merge(node *fir, node *sec)
{
  node *temp = fir;
  while (fir->next != NULL)
    fir = fir->next;
  fir->next = sec;
  return temp;
}
int main()
{
  ios_base::sync_with_stdio(false);
  int ar[] = {5, 9, 12, 67, 128};
  node *first = NULL;
  node *second = NULL;
  second = create(ar, 5);

  display(second);
  //delete_node(first, 12);
  cout << "\n";
  // display(first);
  //  cout << sum(first) << "\n";
  // cout << max(first) << "\n";
  // bool flag = search(first, 32) != 0 ? true : false;
  // cout << flag << "\n";
  first = sortedInsert(first, 130);
  first = sortedInsert(first, 260);
  first = sortedInsert(first, 11);
  display(first);
  cout << "\n";
  first = merge(second, first);
  display(first);
}