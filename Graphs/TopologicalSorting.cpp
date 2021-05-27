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
vector<int> graphs[10001];
int vis[10001];
int in_edge[10001];
vector<int> ans;
set<int> s;
void kahn()
{
    while (s.size() != 0)
    {
        int node = *s.begin();
        s.erase(s.begin());
        ans.pb(node);
        for (int child : graphs[node])
        {
            in_edge[child]--;
            if (in_edge[child] == 0)
                s.insert(child);
        }
    }
}
int32_t main()
{
    boost;
    int n, m;
    cin >> n >> m;
    rep(i, 0, m - 1)
    {
        int a, b;
        cin >> a >> b;
        graphs[a].pb(b);
        graphs[b].pb(a);
        in_edge[b]++; // this stores the number of in edges for any node
    }
    for (int i = 1; i <= n; i++)
    {
        if (in_edge[i] == 0) // s inititally has all the nodes with in_edge 0
            s.insert(i);
    }
    kahn();
    if (ans.size() != n)         // if the size != n that means the graph contains a cycle, and topological sorting is not possible
        cout << "Sandro fails."; // as, the moment it encounters a cycle, then no node with zero in_node will be passed
    else                         // ans while loop will end even though all the nodes have not been inserted into the ans vector
        for (auto i : ans)
            cout << i << " ";
}