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

inline ll outer(const pll a, const pll b)
{
    return a.xx * b.yy - a.yy * b.xx;
}

inline ll ccw(const pll &a, const pll &b, const pll &c)
{
    auto tmp = outer({b.xx - a.xx, b.yy - a.yy}, {c.xx - a.xx, c.yy - a.yy});
    return (tmp ? (tmp < 0 ? -1 : 1) : 0);
}

vector<pll> convex_hull(vector<pll> &dat)
{
    if (dat.size() <= 2)
        return dat;
    vector<pll> upper, lower;
    sort(dat.begin(), dat.end(), [](const pll &a, const pll &b)
         { return (a.xx == b.xx) ? a.yy < b.yy : a.xx < b.xx; });
    for (const auto &p : dat)
    {
        while (upper.size() >= 2 && ccw(*++upper.rbegin(), *upper.rbegin(), p) > 0)
            upper.pop_back();
        while (lower.size() >= 2 && ccw(*++lower.rbegin(), *lower.rbegin(), p) < 0)
            lower.pop_back();
        upper.emplace_back(p);
        lower.emplace_back(p);
    }
    upper.insert(upper.end(), ++lower.rbegin(), --lower.rend());
    return upper;
}

vector<pll> ch;
void solve()
{
    int n;
    cin >> n;
    if (n <= 2)
    {
        ct("Yes");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        ch.push_back({a, b});
    }
    ch.push_back({0, 0});
    auto ans = convex_hull(ch);
    int at = 0;
    for (auto [a, b] : ans)
    {
        if (a == 0 && b == 0)
            at = 1;
    }
    if (at)
        ct("Yes");
    else
        ct("No");
}

int main()
{
    FASTIO
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    int T = 1;
    while (T--)
    {
        solve();
    };
}
