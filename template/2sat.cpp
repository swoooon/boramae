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

const int MAX = 10101; //정점의 최대 개수
struct twoSAT
{
    int discovered[MAX * 2], sccNumber[MAX * 2], cnt1, cnt2;
    vector<int> adj[MAX * 2];
    stack<int> S;
    int scc(int here)
    {
        discovered[here] = cnt1++;
        int ret = discovered[here];
        S.push(here);
        for (int &there : adj[here])
        {
            if (discovered[there] == -1)
                ret = min(ret, scc(there));
            else if (sccNumber[there] == -1)
                ret = min(ret, discovered[there]);
        }
        if (ret == discovered[here])
        {
            while (true)
            {
                int tmp = S.top();
                S.pop();
                sccNumber[tmp] = cnt2;
                if (tmp == here)
                    break;
            }
            ++cnt2;
        }
        return ret;
    }
    vector<int> solve(int V = MAX)
    {
        V *= 2;
        memset(discovered, -1, sizeof(discovered));
        memset(sccNumber, -1, sizeof(sccNumber));
        cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < V; ++i)
            if (discovered[i] == -1)
                scc(i);
        for (int i = 0; i < V; i += 2)
            if (sccNumber[i] == sccNumber[i + 1])
                return vector<int>();
        vector<int> ans(V / 2, -1);
        int arr[MAX * 2];
        for (int i = 0; i < V; ++i)
            arr[i] = i;
        sort(arr, arr + V, [&](int &a, int &b)
             {
                 if (sccNumber[a] != sccNumber[b])
                     return sccNumber[a] > sccNumber[b];
                 return a < b;
             });
        for (int i = 0; i < V; ++i)
            if (ans[arr[i] / 2] == -1)
                ans[arr[i] / 2] = !(arr[i] & 1);
        return ans;
    }
    void makeEdge(int X, bool XisTrue, int Y, bool YisTrue)
    {
        adj[2 * X + !XisTrue].push_back(2 * Y + YisTrue);
        adj[2 * Y + !YisTrue].push_back(2 * X + XisTrue);
    }
};

struct twoSAT_other
{
    vector<int> discovered, sccNumber;
    vector<vector<int>> adj;
    int cnt1, cnt2, n;

    twoSAT_other(int n)
    {
        this->n = n + 1;
        discovered.resize(2 * n + 1);
        sccNumber.resize(2 * n + 1);
        adj.resize(2 * n + 1);
    }

    stack<int> S;
    int scc(int here)
    {
        discovered[here] = cnt1++;
        int ret = discovered[here];
        S.push(here);
        for (int &there : adj[here])
        {
            if (discovered[there] == -1)
                ret = min(ret, scc(there));
            else if (sccNumber[there] == -1)
                ret = min(ret, discovered[there]);
        }
        if (ret == discovered[here])
        {
            while (true)
            {
                int tmp = S.top();
                S.pop();
                sccNumber[tmp] = cnt2;
                if (tmp == here)
                    break;
            }
            ++cnt2;
        }
        return ret;
    }
    vector<int> solve()
    {
        int V = n;
        V *= 2;
        fill(all(discovered), -1);
        fill(all(sccNumber), -1);
        cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < V; ++i)
            if (discovered[i] == -1)
                scc(i);
        for (int i = 0; i < V; i += 2)
            if (sccNumber[i] == sccNumber[i + 1])
                return vector<int>();
        vector<int> ans(V / 2, -1);
        vector<int> arr(2 * n + 1);
        for (int i = 0; i < V; ++i)
            arr[i] = i;
        sort(all(arr), [&](int &a, int &b)
             {
                 if (sccNumber[a] != sccNumber[b])
                     return sccNumber[a] > sccNumber[b];
                 return a < b;
             });
        for (int i = 0; i < V; ++i)
            if (ans[arr[i] / 2] == -1)
                ans[arr[i] / 2] = !(arr[i] & 1);
        return ans;
    }
    void makeEdge(int X, bool XisTrue, int Y, bool YisTrue)
    {
        adj[2 * X + !XisTrue].push_back(2 * Y + YisTrue);
        adj[2 * Y + !YisTrue].push_back(2 * X + XisTrue);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    twoSAT TS;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        int at = 1, bt = 1;
        if (a < 0)
            a = -a, at = 0;
        if (b < 0)
            b = -b, bt = 0;
        TS.makeEdge(a, at, b, bt);
    }
    auto ans = TS.solve();
    ct(!ans.empty());
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
