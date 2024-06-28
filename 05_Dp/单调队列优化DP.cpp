#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
// #define int long long
constexpr int N = 1e6 + 50, LOGN = 30;
constexpr ll mod = 1e9 + 7, inf = 2e9;

void solve(){
    int n, m; cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    deque<int> que;
    vector<int> dp(n + 1);
    int ans = inf;
    for (int i = 1; i <= n; i++) {
        while (!que.empty() && dp[que.back()] >= dp[i - 1]) que.pop_back();
        que.push_back(i - 1);
        if (que.front() < i - m) que.pop_front();
        dp[i] = dp[que.front()] + a[i];
        if (i > n - m) ans = min(ans, dp[i]);
    }
    cout << ans << '\n';

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