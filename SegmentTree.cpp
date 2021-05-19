#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ms_i multiset<int>::iterator
#define s_i set<int>::iterator
#define v_i vector<int>::iterator
#define m_i map<int, int>::iterator
#define rep(i, j, k) for (int i = j; i <= k; i++)
#define pb push_back
#define mp make_pair
#define pi 3.14159265358979
#define mod 1000000007
int st[4 * 100001];
int ar[100001];
int lazy[4 * 100001];
int query( int si, int ss, int se, int qs, int qe)
{
    if (qs > se || qe < ss)
        return INT_MAX;
    if (ss >= qs && se <= qe)
        return st[si];
    int mid = (ss + se) / 2;
    return min(query(2 * si, ss, mid, qs, qe), query(2 * si + 1, mid + 1, se, qs, qe));
}
int updateST(int si, int ss, int se, int qi)
{
    if (ss == se)
    {
        st[si] = ar[qi];
        return ar[qi];
    }
    int mid = (ss + se) / 2;
    if (qi <= mid)
        updateST( 2 * si, ss, mid, qi);
    else
        updateST(2 * si + 1, mid + 1, se, qi);
    st[si] = min(st[2 * si], st[2 * si + 1]);
}
void updateSTOE(int *ar, pair<int, int> *st, int si, int ss, int se, int qi)
{
    if (ss == se)
    {
        if (ar[qi] % 2 == 0)
            st[si] = mp(1, 0);
        else    
            st[si] = mp(0, 1);
        return;
    }
    int mid = (ss + se) / 2;
    if (qi <= mid)
        updateSTOE(ar, st, 2 * si, ss, mid, qi);
    else
        updateSTOE(ar, st, 2 * si + 1, mid + 1, se, qi);
    st[si] = mp(st[2 * si].first + st[2 * si + 1].first, st[2 * si].second + st[2 * si + 1].second);
}
void createSTOE(int *ar, pair<int, int> *st, int si, int ss, int se)
{
    if (ss == se)
    {
        if (ar[ss] % 2 == 0)
            st[si] = mp(1, 0);
        else
            st[si] = mp(0, 1);
        return;
    }
    int mid = (ss + se) / 2;
    createSTOE(ar, st, 2 * si, ss, mid);
    createSTOE(ar, st, 2 * si + 1, mid + 1, se);
    st[si] = mp(st[2 * si].first + st[2 * si + 1].first, st[2 * si].second + st[2 * si + 1].second);
}
int createST(int si, int ss, int se)
{
    if (ss == se)
    {
        st[si] = ar[ss];
        return st[si];
    }
    int mid = (ss + se) / 2;
    st[si] = min(createST(2 * si, ss, mid), createST(2 * si + 1, mid + 1, se));
    return st[si];
}
pair<int, int> querySTOE(pair<int, int> *st, int ss, int se, int qs, int qe, int si)
{
    if (ss >= qs && se <= qe)
    {
        return st[si];
    }
    else if (ss > qe || se < qs)
    {
        return mp(0, 0);
    }
    else
    {
        int mid = (ss + se) / 2;
        pair<int, int> fir = querySTOE(st, ss, mid, qs, qe, 2 * si);
        pair<int, int> sec = querySTOE(st, mid + 1, se, qs, qe, 2 * si + 1);
        return mp(fir.first + sec.first, fir.second + sec.second);
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(false); // remove it at the time of debugging
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    rep(i, 1, n)
    {
        cin >> ar[i];
    }
    createST(1, 1, n);
    cout << query(1, 1, n, 2, 5);
    
    
}