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

struct A {
    int s, i, p;
} arr[55];

int dp[1010][1010];
int ans[1010][1010];

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].s >> arr[i].i >> arr[i].p;
        if (arr[i].s == 1 || arr[i].i == 1) dp[1][1] += arr[i].p, ans[1][1]++;
    }
    int ret = 0;
    for (int i = 1; i <= 1000; i++) {
        for (int j = 1; j <= 1000; j++) {
            if (dp[i][j - 1] == 0 && dp[i - 1][j] == 0) continue;
            pii a = {ans[i][j - 1], dp[i][j - 1] - 1}, b = {ans[i - 1][j], dp[i - 1][j] - 1};
            for (int k = 0; k < n; k++) {
                if (arr[k].s == i && arr[k].i > j) {
                    b.xx++;
                    b.yy += arr[k].p;
                }
                if (arr[k].i == j && arr[k].s > i) {
                    a.xx++;
                    a.yy += arr[k].p;
                }
            }
            pii s = max(a, b);
            dp[i][j] = s.yy;
            ans[i][j] = s.xx;
            ret = max(ans[i][j], ret);
        }
    }
    ct(ret);
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
