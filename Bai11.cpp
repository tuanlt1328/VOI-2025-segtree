#include <bits/stdc++.h>
#define FILE ""
#define ll long long
#define endl '\n'
#define fi first
#define se second

using namespace std;

const ll MAX = 1e5 + 9;
const ll oo = 1e18;
const ll mod = 1e9 + 7;

void inp()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen (FILE".INP", "r", stdin);
    //freopen (FILE".OUT", "w", stdout);
}

ll n, m;
ll arr[MAX], ans[MAX];
ll tree[MAX * 4], lazy[MAX * 4];

void build (ll id, ll l, ll r)
{
    if (l == r) tree[id] = arr[l];
    else
    {
        ll mid = (l + r) / 2;
        build (id * 2, l, mid);
        build (id * 2 + 1, mid + 1, r);
        tree[id] = min (tree[id * 2], tree[id * 2 + 1]);
    }
}

void push_down (ll id)
{
    if (lazy[id])
    {
        if (tree[id * 2] != oo) tree[id * 2] += lazy[id];
        if (tree[id * 2 + 1] != oo) tree[id * 2 + 1] += lazy[id];

        lazy[id * 2] += lazy[id];
        lazy[id * 2 + 1] += lazy[id];

        lazy[id] = 0;
    }
}

void update_segment (ll id, ll l, ll r, ll u, ll v, ll w)
{
    if (l > v || r < u) return;
    if (u <= l && r <= v)
    {
        if (tree[id] != oo) tree[id] -= w;
        lazy[id] -= w;
        return;
    }

    push_down (id);
    ll mid = (l + r) / 2;
    update_segment (id * 2, l, mid, u, v, w);
    update_segment (id * 2 + 1, mid + 1, r, u, v, w);
    tree[id] = min (tree[id * 2], tree[id * 2 + 1]);
}

ll find_negative (ll id, ll l, ll r, ll u, ll v)
{
    if (l > v || r < u) return -1;
    if (tree[id] > 0) return -1;
    if (l == r) return l;

    push_down (id);
    ll mid = (l + r) / 2;
    ll res = find_negative (id * 2, l, mid, u, v);
    if (res != -1) return res;
    else return find_negative (id * 2 + 1, mid + 1, r, u, v);

}

void update_point (ll id, ll l, ll r, ll pos)
{
    if (l == r)
    {
        tree[id] = arr[l] = oo;
        lazy[id] = 0;
        return;
    }

    push_down (id);
    ll mid = (l + r) / 2;
    if (pos <= mid) update_point (id * 2, l, mid, pos);
    else update_point (id * 2 + 1, mid + 1, r, pos);
    tree[id] = min (tree[id * 2], tree[id * 2 + 1]);
}

int main()
{
    inp();

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        ans[i] = -1;
    }

    build (1, 1, n);

    for (int time = 1; time <= m; time++)
    {
        ll a, b, w;
        cin >> a >> b >> w;
        update_segment (1, 1, n, a, b, w);

        while (true)
        {
            ll pos = find_negative (1, 1, n, a, b);
            if (pos == -1) break;
            ans[pos] = time;
            update_point (1, 1, n, pos);
        }
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";

    return 0;
}

