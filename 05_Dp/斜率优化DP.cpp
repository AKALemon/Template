#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
// #define int long long
constexpr int N = 1e6 + 50, LOGN = 30;
constexpr ll mod = 1e9 + 7, inf = 1e9;

int q[N];

void solve(){
    int n, s;cin >> n >> s;
    vector<ll> ti(n + 1), c(n + 1);
    for (int i = 1; i <= n; i++) cin >> ti[i] >> c[i];
    for (int i = 1; i <= n; i++) ti[i] += ti[i - 1], c[i] += c[i - 1];

    vector<ll> dp(n + 1, inf);
    dp[0] = 0;
    int h = 1, t = 0;
    auto dy = [&](int i, int j) -> ll {
        return dp[i] - dp[j];
    };
    auto dx = [&](int i, int j) -> ll {
        return c[i] - c[j];
    };

    auto find = [&](int i) -> int {
        if (h == t) return q[h];
        int l = h - 1, r = t + 1;
        while (l + 1 < r) {
            int m = l + r >> 1;
            if (dy(q[m], q[m - 1]) <= (s + ti[i]) * dx(q[m], q[m - 1])) l = m;
            else r = m;
        }
        return q[l];
    };

    for (int i = 1; i <= n; i++) {
        while (h < t && dy(i - 1, q[t]) * dx(q[t], q[t - 1]) <= dy(q[t], q[t - 1]) * dx(i - 1, q[t])) t--;
        q[++t] = i - 1;
        int j = find(i);
        dp[i] = dp[j] + ti[i] * (c[i] - c[j]) + s * (c[n] - c[j]);
    }
    cout << dp[n] << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << setprecision(15) << fixed;
    int t = 1;
    //cin >> t;
    while (t--) solve();
    return 0;
}
