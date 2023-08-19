#include <bits/stdc++.h>

#define FASTIO                   \
    ios::sync_with_stdio(false); \
    cin.tie(0);
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
void ct(T&& v) { cout << forward<T>(v) << '\n'; }

template <class T, class... Args>
void ct(T&& v, Args&&... args) {
    cout << forward<T>(v) << ' ';
    ct(forward<Args>(args)...);
}

inline ll outer(const pii a, const pii b) {
    return a.xx * b.yy - a.yy * b.xx;
}

inline ll ccw(const pii& a, const pii& b, const pii& c) {
    auto tmp = outer({b.xx - a.xx, b.yy - a.yy}, {c.xx - a.xx, c.yy - a.yy});
    return (tmp ? (tmp < 0 ? -1 : 1) : 0);
}

vector<pii> convex_hull(vector<pii>& dat) {
    if (dat.size() <= 2) return dat;
    vector<pii> upper, lower;
    sort(dat.begin(), dat.end(), [](const pii& a, const pii& b) {
        return (a.xx == b.xx) ? a.yy < b.yy : a.xx < b.xx;
    });
    for (const auto& p : dat) {
        while (upper.size() >= 2 && ccw(*++upper.rbegin(), *upper.rbegin(), p) >= 0) upper.pop_back();
        while (lower.size() >= 2 && ccw(*++lower.rbegin(), *lower.rbegin(), p) <= 0) lower.pop_back();
        upper.emplace_back(p);
        lower.emplace_back(p);
    }
    upper.insert(upper.end(), ++lower.rbegin(), --lower.rend());
    return upper;
}

void solve() {
    int n;
    cin >> n;
    vector<pii> v;
    for (int i = 0; i < n; i++) {
        pii t;
        cin >> t.xx >> t.yy;
        v.push_back(t);
    }
    auto ans = convex_hull(v);
    for (int i = 1; i < int(ans.size()); i++) {
        ans[i].xx -= ans[0].xx;
        ans[i].yy -= ans[0].yy;
    }
    ll a = 0;
    for (int i = 1; i < int(ans.size()) - 1; i++) {
        a += outer(ans[i], ans[i + 1]);
    }
    a = abs(a);
    ct(a / 100);
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