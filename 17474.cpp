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
#define all(x) x.begin(), x.end()
#define xx first
#define yy second
const ll mod = 1e9 + 7;
const ll INF = 1e18;
int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};
int kdx[8] = {2, 2, 1, 1, -2, -2, -1, -1},
    kdy[8] = {1, -1, 2, -2, 1, -1, 2, -2};

template <class T>
void ct(T &&v) { cout << forward<T>(v) << '\n'; }

template <class T, class... Args>
void ct(T &&v, Args &&...args) {
    cout << forward<T>(v) << ' ';
    ct(forward<Args>(args)...);
}

ll arr[1010101];

struct Segbeats {
    struct Node {
        ll mx, mx2, mxcnt, sum;
    };

    vector<Node> seg;
    int n;
    Segbeats(int n) {
        seg.resize(4 * n + 5);
        this->n = n;
    }

    void init(int node, int l, int r) {
        if (l == r) {
            seg[node] = {arr[l], -1, 1, arr[l]};
            return;
        }
        int mid = (l + r) / 2;
        init(node * 2, l, mid);
        init(node * 2 + 1, mid + 1, r);
        seg[node] = merge(seg[node * 2], seg[node * 2 + 1]);
    }

    Node merge(Node a, Node b) {
        if (a.mx == b.mx) return {a.mx, max(a.mx2, b.mx2), a.mxcnt + b.mxcnt, a.sum + b.sum};
        if (a.mx > b.mx) swap(a, b);
        return {b.mx, max(a.mx, b.mx2), b.mxcnt, a.sum + b.sum};
    }

    void prop(int node, int l, int r) {
        if (l == r) return;
        for (int i : {node * 2, node * 2 + 1}) {
            if (seg[node].mx < seg[i].mx) {
                seg[i].sum -= seg[i].mxcnt * (seg[i].mx - seg[node].mx);
                seg[i].mx = seg[node].mx;
            }
        }
    }

    void upd(int node, int l, int r, int wl, int wr, ll val) {
        prop(node, l, r);
        if (wr < l || wl > r || seg[node].mx <= val)
            return;
        if (wl <= l && r <= wr && seg[node].mx2 < val) {
            seg[node].sum -= seg[node].mxcnt * (seg[node].mx - val);
            seg[node].mx = val;
            prop(node, l, r);
            return;
        }

        int mid = (l + r) / 2;
        upd(node * 2, l, mid, wl, wr, val);
        upd(node * 2 + 1, mid + 1, r, wl, wr, val);
        seg[node] = merge(seg[node * 2],
                          seg[node * 2 + 1]);
    }

    ll getmax(int node, int l, int r, int wl, int wr) {
        prop(node, l, r);
        if (l > wr || r < wl)
            return 0;
        if (wl <= l && r <= wr)
            return seg[node].mx;
        int mid = (l + r) / 2;
        return max(
            getmax(node * 2, l, mid, wl, wr),
            getmax(node * 2 + 1, mid + 1, r, wl, wr));
    }

    ll query(int node, int l, int r, int wl, int wr) {
        prop(node, l, r);
        if (l > wr || r < wl)
            return 0;
        if (wl <= l && r <= wr)
            return seg[node].sum;
        int mid = (l + r) / 2;
        return (
            query(node * 2, l, mid, wl, wr) +
            query(node * 2 + 1, mid + 1, r, wl, wr));
    }
    void upd(int wl, int wr, ll val) {
        upd(1, 1, n, wl, wr, val);
    }
    ll query(int wl, int wr) {
        return query(1, 1, n, wl, wr);
    }
    ll getmax(int wl, int wr) {
        return getmax(1, 1, n, wl, wr);
    }
};

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    Segbeats segbeats(n);
    segbeats.init(1, 1, n);
    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        ll l, r;
        cin >> l >> r;
        if (t == 1) {
            ll x;
            cin >> x;
            segbeats.upd(l, r, x);
        }
        if (t == 2) {
            ct(segbeats.getmax(l, r));
        }
        if (t == 3) {
            ct(segbeats.query(l, r));
        }
    }
}

int main() {
    FASTIO
#ifndef ONLINE_JUDGE
    freopen("others/input.txt", "r", stdin);
    freopen("others/output.txt", "w", stdout);
#endif
    int T = 1;
    for (int i = 1; i <= T; i++) {
        solve();
    };
}
