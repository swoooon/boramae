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

// ax + b 꼴의 직선들에 대해 최대값 구한다. logN
// 최소값을 원하면, 기울기에 -1을 곱해 x축 대칭 시킨다.
// 실수 사용을 원하면, inf = 1/.0, div(a,b) = a/b
struct Line
{
    mutable ll k, m, p;
    bool operator<(const Line &o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>>
{
    const ll inf = LLONG_MAX;
    ll div(ll a, ll b)
    { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y)
    {
        if (y == end())
        {
            x->p = inf;
            return false;
        }
        if (x->k == y->k)
            x->p = x->m > y->m ? inf : -inf;
        else
            x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll a, ll b)
    {
        auto z = insert({a, b, 0}), y = z++, x = y;
        while (isect(y, z))
            z = erase(z);
        if (x != begin() && isect(--x, y))
            isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x)
    {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
} CHT;

ll arr[101010];
ll arr2[101010];
ll dp[101010];

void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    for (int i = 1; i <= n; i++)
        cin >> arr2[i];
    for (int i = 2; i <= n; i++)
    {
        CHT.add(-arr2[i - 1], dp[i - 1]);
        dp[i] = CHT.query(arr[i]);
    }
    ct(-dp[n]);
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
