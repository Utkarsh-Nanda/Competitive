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
int dist[101];
vector<pair<int, int>> graph[101];
void ssc(int source)
{
    set<pair<int, int>> s; // first = node, second = distance from source
    dist[source] = 0;
    s.insert(mp(source, 0));
    while (!s.empty())
    {
        pair<int, int> temp = *s.begin();
        s.erase(s.begin());
        for (auto child : graph[temp.first])
        {
            if (dist[child.first] > temp.second + child.second) // temp.second = distance of the node from source, child.second = edge weight between node and child
            {
                dist[child.first] = temp.second + child.second;
                s.insert(mp(child.first, dist[child.first]));
            }
        }
    }
}
int32_t main()
{
    boost;
    int n, m;
    cin >> n >> m;
    rep (i, 1, n)
        dist[i] = LLONG_MAX;
    rep (i, 0, m - 1) // creating the graph
    {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].pb(mp(b, w));
        graph[b].pb(mp(a, w));
    }
    ssc(1);
    rep (i, 1, n)
        cout << dist[i] << " ";
}	