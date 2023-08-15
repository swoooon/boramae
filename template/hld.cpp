#include <bits/stdc++.h>

#define FASTIO                   \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef long double ld;
#define xx first
#define yy second
#define all(x) x.begin(), x.end()
const int mod = 1e9 + 7;
const ll INF = 1e18;

int dy[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dx[8] = {0, 1, 0, -1, 1, -1, 1, -1};
int kdy[8] = {2, 2, 1, 1, -2, -2, -1, -1}, kdx[8] = {1, -1, 2, -2, 1, -1, 2, -2};

int out1(int i, int j, int a, int b) { return i > a || i < 1 || j > b || j < 1; }
int out0(int i, int j, int a, int b) { return i >= a || i < 0 || j >= b || j < 0; }

template <class T>
void ct(T &&v)
{
    cout << forward<T>(v) << '\n';
}

template <class T, class... Args>
void ct(T &&v, Args &&...args)
{
    cout << forward<T>(v) << ' ';
    ct(forward<Args>(args)...);
}

const int NMAX = 100010;
int N, M;

class LazySegmentTree
{
public:
    vector<ll> seg;
    vector<ll> lazy;
    int n;
    LazySegmentTree(int n)
    {
        seg.resize(4 * n + 5);
        lazy.resize(4 * n + 5);
        this->n = n;
    }
    void prop(int node, int l, int r)
    {
        if (lazy[node] == 0)
            return;
        seg[node] += lazy[node] * (r - l + 1);
        if (l != r)
        {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    void upd(int node, int l, int r, int wl, int wr, ll val)
    {
        prop(node, l, r);
        if (wr < l || wl > r)
            return;
        if (wl <= l && r <= wr)
        {
            lazy[node] += val;
            prop(node, l, r);
            return;
        }

        int mid = (l + r) / 2;
        upd(node * 2, l, mid, wl, wr, val);
        upd(node * 2 + 1, mid + 1, r, wl, wr, val);
        seg[node] = (seg[node * 2] +
                     seg[node * 2 + 1]);
    }

    ll query(int node, int l, int r, int wl, int wr)
    {
        prop(node, l, r);
        if (l > wr || r < wl)
            return 0;
        if (wl <= l && r <= wr)
            return seg[node];
        int mid = (l + r) / 2;
        return (
            query(node * 2, l, mid, wl, wr) +
            query(node * 2 + 1, mid + 1, r, wl, wr));
    }
    void upd(int wl, int wr, ll val)
    {
        upd(1, 1, n, wl, wr, val);
    }
    ll query(int wl, int wr)
    {
        return query(1, 1, n, wl, wr);
    }
} seg(101010);

struct hld
{
    vector<int> par, head, heavy, pos, weight, dep;
    vector<pii> adj[NMAX];
    int cur_pos;
    void init()
    {
        dep = weight = par = head = pos = vector<int>(NMAX);
        heavy = vector<int>(NMAX, -1);
        cur_pos = 1;
        dfs(1);
        decompose(1, 0);
    }
    int dfs(int cur)
    {
        int ret = 1, mxc = 0;
        for (pii it : adj[cur])
        {
            int next = it.first, w = it.second;
            if (next == par[cur])
                continue;
            weight[next] = w, par[next] = cur, dep[next] = dep[cur] + 1;
            int csz = dfs(next);
            ret += csz;
            if (csz > mxc)
                mxc = csz, heavy[cur] = next;
        }
        return ret;
    }
    void decompose(int cur, int h)
    {
        head[cur] = h, pos[cur] = cur_pos++;
        if (heavy[cur] != -1)
            decompose(heavy[cur], h);
        for (pii it : adj[cur])
        {
            int next = it.first;
            if (next != par[cur] && next != heavy[cur])
                decompose(next, next);
        }
    }
    ll query(int a, int b)
    {
        ll ret = 0;
        for (; head[a] != head[b]; b = par[head[b]])
        {
            if (dep[head[a]] > dep[head[b]])
                swap(a, b);
            ll tmp = seg.query(pos[head[b]], pos[b]);
            ret += tmp;
        }
        if (dep[a] > dep[b])
            swap(a, b);
        if (pos[a] != pos[b])
        {
            ll tmp = seg.query(pos[a] + 1, pos[b]);
            ret += tmp;
        }

        return ret;
    }
    void upd(int a, int b, int val)
    {
        for (; head[a] != head[b]; b = par[head[b]])
        {
            if (dep[head[a]] > dep[head[b]])
                swap(a, b);
            seg.upd(pos[head[b]], pos[b], val);
        }
        if (dep[a] > dep[b])
            swap(a, b);
        if (pos[a] != pos[b])
        {
            seg.upd(pos[a] + 1, pos[b], val);
        }
    }
} hld;

void solve()
{
    cin >> N >> M;
    for (int i = 1; i <= N - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        hld.adj[u].push_back({v, 0});
        hld.adj[v].push_back({u, 0});
    }

    hld.init();
    while (M--)
    {
        char cmd;
        cin >> cmd;
        int a, b;
        cin >> a >> b;
        if (cmd == 'P')
        {
            hld.upd(a, b, 1);
        }
        else
        {
            ct(hld.query(a, b));
        }
    }
}

int main()
{
    FASTIO
    int T = 1;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    while (T--)
    {
        solve();
    };
}
