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
const ll mod = 1e9 + 7;
const ll INF = 1e18;
int dy[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dx[8] = {0, 1, 0, -1, 1, -1, 1, -1};
int kdy[8] = {2, 2, 1, 1, -2, -2, -1, -1}, kdx[8] = {1, -1, 2, -2, 1, -1, 2, -2};

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

int ccw(pll a, pll b, pll c)
{
    ll op = a.first * b.second + b.first * c.second + c.first * a.second;
    op -= (a.second * b.first + b.second * c.first + c.second * a.first);
    if (op > 0)
        return 1;
    else if (op == 0)
        return 0;
    else
        return -1;
}

int isIntersect(pair<pll, pll> x, pair<pll, pll> y)
{
    pll a = x.first;
    pll b = x.second;
    pll c = y.first;
    pll d = y.second;
    ll ab = ccw(a, b, c) * ccw(a, b, d);
    ll cd = ccw(c, d, a) * ccw(c, d, b);
    if (ab == 0 && cd == 0)
    {
        if (a > b)
            swap(a, b);
        if (c > d)
            swap(c, d);
        return c <= b && a <= d;
    }
    return ab <= 0 && cd <= 0;
}

void solve()
{
    pair<pll, pll> x, y;
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    x = {{a, b}, {c, d}};
    cin >> a >> b >> c >> d;
    y = {{a, b}, {c, d}};
    ct(isIntersect(x, y));
}

int main()
{
    FASTIO
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    int T = 1;
    for (int i = 1; i <= T; i++)
    {
        solve();
    };
}
