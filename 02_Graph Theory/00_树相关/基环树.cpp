#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
const int N = 2e5 + 50, LOGN = 30;
const int mod = 1e9 + 7, inf = 0x3f3f3f3f;

void solve(){
    int n;cin >> n;
    vector<int> p(n + 1), val(n + 1);
    vector<vector<int>> g(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> val[i] >> p[i];
        g[p[i]].push_back(i);
    }

    vector<bool> vis(n + 1), oncyc(n + 1);
    vector<array<ll, 2>> dp(n + 1), f(n + 1);

    auto dfs = [&] (auto self, int u) -> void{
        vis[u] = true;
        dp[u][1] = val[u];
        for (auto v : g[u]) {
            if(oncyc[v])continue;
            self(self, v);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        } 
    };
    ll ans = 0;
    for (int i = 1; i <= n; i++) if(!vis[i]) {

        int u = i;
        while(!vis[u]) {
            vis[u] = true;
            u = p[u];
        }
        int v = u;
        vector<int> cyc;
        while(true) {
            cyc.push_back(v);
            oncyc[v] = true;
            v = p[v];
            if(v == u)break;
        }

        for (auto x : cyc) {
            dfs(dfs, x);
        }

        int m = cyc.size();
        ll res = -1e18;
        for (int t = 0; t < 2; t++) {
            for (int i = 0; i < 2; i++) {
                if(i == t) f[0][i] = dp[cyc[0]][i];
                else f[0][i] = -1e18;
            }

            for (int i = 1; i < m; i++) {
                int u = cyc[i];
                f[i][0] = max(f[i - 1][0], f[i - 1][1]) + dp[u][0];
                f[i][1] = f[i - 1][0] + dp[u][1];
            }

            if(t == 0) res = max({res, f[m - 1][0], f[m - 1][1]});
            else res = max(res, f[m - 1][0]);
        }
        ans += res;
    }
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