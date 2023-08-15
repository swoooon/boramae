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
int kdx[8] = {2, 2, 1, 1, -2, -2, -1, -1}, kdy[8] = {1, -1, 2, -2, 1, -1, 2, -2};

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

void solve()
{
}

int main()
{
    FASTIO
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T = 1;
    for (int i = 1; i <= T; i++)
    {
        solve();
    };
}
