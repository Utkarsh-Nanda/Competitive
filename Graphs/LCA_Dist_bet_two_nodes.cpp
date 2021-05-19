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
#define maxN 11
vector<int> graph[1001];
int vis[1001];
int lvl[1001];
int par[1001][maxN];
int n;
void dfs(int node, int level, int parent)
{
    vis[node] = 1;
    lvl[node] = level;
    par[node][0] = parent;
    for (int child : graph[node])
    {
        if (vis[child] == 0) // this also means if the child is not parent of the node
        {
            dfs(child, level + 1, node);
        }
    }
}
void init()
{
    dfs(1, 0, -1);
    for (int i = 1; i <= maxN; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (par[j][i - 1] != -1)
            {
                int temp = par[j][i - 1];
                par[j][i] = par[temp][i - 1];
            }
        }
    }
}
int getLCA(int a, int b)
{
    if (lvl[a] > lvl[b])
        swap(a, b); // b should be greater
    int d = lvl[b] - lvl[a];
    while (d > 0)
    {
        int jump = log2(d);
        b = par[b][jump];
        d -= 1 << jump;
    }
    if (a == b)
        return a;
    for (int i = maxN; i >= 0; i--)
    {
        if (par[a][i] != -1 && (par[a][i] != par[b][i]))
        {
            a = par[a][i];
            b = par[b][i];
        }
    }
    return par[a][0];
}
int getDist(int a, int b)
{
    return lvl[a] + lvl[b] - 2 * lvl[getLCA(a, b)];
}
int32_t main()
{
    boost;
    cin >> n;
    memset(par, -1, sizeof(par));
    rep(i, 0, n - 2) // make the graph
    {
        int a, b;
        cin >> a >> b;
        graph[a].pb(b);
        graph[b].pb(a);
    }
    init();
    int q;
    cin >> q;
    rep(i, 0, q - 1)
    {
        int a, b;
        cin >> a >> b;
        cout << getDist(a, b) << "\n";
    }
}