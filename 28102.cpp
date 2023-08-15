#include <bits/stdc++.h>

#define FASTIO                                                                 \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(0);                                                                  \
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

template <class T> void ct(T &&v) { cout << forward<T>(v) << '\n'; }

template <class T, class... Args> void ct(T &&v, Args &&...args) {
  cout << forward<T>(v) << ' ';
  ct(forward<Args>(args)...);
}

vector<int> adj[101010];
int uf[101010];
int vis[101010];
int isbi[101010];

int find(int a) {
  if (uf[a] == a)
    return a;
  return uf[a] = find(uf[a]);
}

void merge(int a, int b) {
  a = find(a), b = find(b);
  if (a == b)
    return;
  uf[b] = a;
  return;
}

void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) {
    uf[i] = i;
    vis[i] = -1;
  }
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].push_back(b);
    adj[b].push_back(a);
    merge(a, b);
  }
  queue<pii> que;
  for (int i = 1; i <= n; i++) {
    if (vis[i] != -1)
      continue;
    int bi = 1;
    que.push({i, 1});
    while (!que.empty()) {
      auto [a, b] = que.front(); que.pop();
      for (int nxt : adj[a]) {
        if (vis[nxt] != -1) {
          if (vis[nxt] == b) {
            bi = 0;
          }
          continue;
        }
        vis[nxt] = b ^ 1;
        que.push({nxt, b ^ 1});
      }
    }
    if (bi)
      isbi[find(i)] = 1;
  }

  while (q--) {
    int a, b, k;
    cin >> a >> b >> k;
    if (find(a) != find(b)) {
      ct("No");
      continue;
    }
    if (isbi[find(a)]) {
      if (k & 1) {
        ct("Yes");
      } else {
        if (vis[a] == vis[b])
          ct("Yes");
        else
          {ct("No");}
      }
    } else
      ct("Yes");
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
