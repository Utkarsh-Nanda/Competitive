#include <bits/stdc++.h>
using namespace std;
#define int long long
#define boost                         \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define testcases \
    int t;        \
    cin >> t;     \
    while (t--)
#define rep(i, j, k) for (int i = j; i <= k; i++)
#define pb push_back
#define pf push_front
#define mp make_pair
#define pi 3.14159265358979323846
#define mod 1000000007
vector<pair<pair<int, int>, int>> edges;
int par[10001];
int siz[10001];
bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
    if (a.second < b.second)
        return true;
    else
        return false;
}
int find(int a)
{
    if (par[a] < 0)
        return a;
    int x = find(par[a]);
    return x;
}
void Union(int a, int b) // this ensures logn time complexity
{
    if (siz[a] < siz[b])
    {
        par[a] = b;
        siz[b] += siz[a];
    }
    else
    {
        par[b] = a;
        siz[a] += siz[b];
    }
}
int32_t main()
{
    boost;
    int n, m;
    cin >> n >> m;
    rep(i, 0, m - 1) // taking all the input
    {
        int a, b, w;
        cin >> a >> b >> w;
        edges.pb(mp(mp(a, b), w));
    }
    rep(i, 1, n)
    {
        par[i] = -1;
        siz[i] = 1;
    }
    sort(edges.begin(), edges.end(), comp);
    int sum = 0;
    for (auto i : edges)
    {
        int a = i.first.first;
        int b = i.first.second;
        int x = find(a);
        int y = find(b);
        if (x != y)
        {
            Union(x, y);
            sum += i.second;
        }
    }
    cout << sum;
}