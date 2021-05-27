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
deque<int> ans;
int counter = 0;
vector<int> graph[26];
int vis[26][26];
// this method finds the eulerian path, make a 2D vis array, to see which edges have been visited, also store the nodes you visit.
// First node from which you start the dfs doesn't repeat in the sequence, other nodes repeat.
void dfs(int node) 
{
    for (int child : graph[node])
    {
        if (vis[node][child] == 0)
        {
            vis[node][child] = 1;
            dfs(child);
        }
    }
    ans.pf(node);
}
int32_t main()
{
    boost;
    int n, k;
    cin >> n >> k;
    
    rep(i, 0, k - 1) // graph is ready
    {
        rep(j, 0, k - 1)
        {
            graph[i].pb(j);
        }
    }
    dfs(0);
    string s;
    for (int i = 1; i < ans.size(); i++)
        s += (char)(ans[i] + 'a');
    string final;
    final += s;
    while (final.size() < n)
    {
        final += s;
    }
    rep(i, 0, n - 1)
    {
        cout << final[i];
    }
}