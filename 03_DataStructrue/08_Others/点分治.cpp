#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef double db;
// #define int long long
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
const int N = 4e4 + 50, LOGN = 30;
const ll mod = 1e9 + 7, inf = 1e9;

vector<pair<int, int>> g[N];
ll ans = 0;
int sz[N], maxs[N], k;
bool del[N];

void dfs(int u, int s) {
    int mx = s + 1, root = -1;

    auto dfs1 = [&](auto self, int u, int fa) -> void{
        sz[u] = 1;
        maxs[u] = 0;
        for (auto [v, w] : g[u]) {
            if (del[v] || v == fa) continue;
            self(self, v, u);
            sz[u] += sz[v];
            maxs[u] = max(maxs[u], sz[v]);
        }
        maxs[u] = max(maxs[u], s - sz[u]);
        if (maxs[u] < mx) mx = maxs[u], root = u;

    };
    dfs1(dfs1, u, -1);


    /////主要修改位置
    auto calc = [&] (vector<int> &d) -> ll{
        sort(d.begin(), d.end());
        int n = d.size(), r = n - 1;
        ll res = 0;
        for (int l = 0; l < n; l++) {
            while (r >= 0 && d[r] + d[l] > k)r--;
            if (r > l) res += r - l;
        }
        return res;
    };
    vector<int> d1;
    d1.push_back(0);
    for (auto [v, w] : g[root]) {
        if (del[v]) continue;
        vector<int> d2;
        auto dfs2 = [&](auto self, int u, int fa, int dep) -> void{
            d1.push_back(dep);
            d2.push_back(dep);
            sz[u] = 1;
            for (auto [v, w] : g[u]) {
                if (del[v] || v == fa)continue;

                self(self, v, u, dep + w);
                sz[u] += sz[v];
            }
        };

        dfs2(dfs2, v, root, w);
        ans -= calc(d2);
    }
    ans += calc(d1);
    /////




    del[root] = true;
    for (auto [v, w] : g[root]) {
        if (!del[v]) dfs(v, sz[v]);
    }

}

void solve(){
    int n; cin >> n;    
    for (int i = 1; i < n; i++) {
        int u, v, w;cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    cin >> k;
    dfs(1, n);
    cout << ans << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << setprecision(15) << fixed;
    int t = 1;
    //cin >> t;
    while(t--)solve();
    return 0;
}