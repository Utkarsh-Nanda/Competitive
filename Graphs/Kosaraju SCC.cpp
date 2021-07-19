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
#define repo(i, j, k) for (int i = j; i >= k; i--)
#define pb push_back
#define pf push_front
#define mp make_pair
#define mod 1000000007
vector<int> ar[1001];
vector<int> tr[1001];

vector<int> order;
vector<int> SCC;

int vis[1001];

void dfs(int node)
{
    vis[node] = 1;

    for (int child : ar[node])
        if (vis[child] == 0)
            dfs(child);

    order.pb(node);
}

void dfs1(int node)
{
    vis[node] = 1;

    for (int child : tr[node])
        if (vis[child] == 0)
            dfs1(child);

    SCC.pb(node);
}

int main()
{
    int n, a, b, m, t;
    cin >> t;

    while (t--)
    {
        cin >> n >> m;
        rep(i, 1, n)
            ar[i]
                .clear(),
            tr[i].clear(), vis[i] = 0;
        order.clear();

        rep(i, 1, m)
        {
            cin >> a >> b;
            ar[a].pb(b);
            tr[b].pb(a);
        }

        rep(i, 1, n) if (vis[i] == 0)
            dfs(i);

        rep(i, 1, n)
            vis[i] = 0;

        REP(i, n)
        if (vis[order[n - i]] == 0)
        {
            SCC.clear();
            dfs1(order[n - i]);

            cout << "dfs1() called from " << order[n - i] << " and printing SCC" << endl;
            for (int node : SCC)
                cout << node << " ";
            cout << endl;
        }
    }
}
