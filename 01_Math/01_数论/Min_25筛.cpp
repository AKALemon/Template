#include<bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
constexpr int N = 1e6 + 50, LOGN = 30;
constexpr i64 P = 1e9 + 7, inf = 1e9;

int p[N], num;
i64 pr[N];
i64 sum1[N], sum2[N];
i64 n, sqr;
void init(int n) {
    p[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!p[i]) {
            pr[++num] = i;
            sum1[num] = (sum1[num - 1] + i) % P;
            sum2[num] = (sum2[num - 1] + 1ll * i * i % P) % P;
        }
        for (int j = 1; j <= num && pr[j] * i <= n; j++) {
            p[i * pr[j]] = 1;
            if (i % pr[j] == 0) break;
        }
    }
}

i64 qpow(i64 a, i64 b) {
    i64 res = 1;
    while (b) {
        if (b & 1) res = res * a % P;
        b >>= 1;
        a = a * a % P;
    }
    return res;
}
i64 w[N], id1[N], id2[N], tot;
i64 g1[N], g2[N], inv2, inv6;

i64 S(i64 x, int y) {
    if (pr[y] >= x) return 0;
    i64 k = x <= sqr ? id1[x] : id2[n / x];
    i64 ans = (g2[k] - g1[k] + P - (sum2[y] - sum1[y]) + P) % P;
    for (int i = y + 1; i <= num && pr[i] * pr[i] <= x; i++) {
        i64 pe = pr[i];
        for (int e = 1; pe <= x; e++, pe *= pr[i]) {
            i64 xx = pe % P;
            ans = (ans + xx * (xx - 1) % P * (S(x / pe, i) + (e != 1)) % P) % P;
        }
    }
    return ans;
}

void solve(){
    cin >> n;
    sqr = sqrt(n);
    inv2 = qpow(2, P - 2), inv6 = qpow(6, P - 2);
    init(sqr);
    for (i64 l = 1, r; l <= n;l = r + 1) {
        r = n / (n / l);
        w[++tot] = n / l;
        g1[tot] = w[tot] % P;
        g2[tot] = g1[tot] * (g1[tot] + 1) % P * (2 * g1[tot] % P + 1) % P * inv6 % P;
        g2[tot] = (g2[tot] - 1 + P) % P;
        g1[tot] = (g1[tot] * (g1[tot] + 1) % P * inv2 % P - 1 + P) % P;
        if (n / l <= sqr) id1[n / l] = tot;
        else id2[n / (n / l)] = tot;
    }
    for (int i = 1; i <= num; i++)
    for (int j = 1; j <= tot && pr[i] * pr[i] <= w[j]; j++) {
        i64 k = w[j] / pr[i] <= sqr ? id1[w[j] / pr[i]] : id2[n / (w[j] / pr[i])];
        g1[j] = (g1[j] - pr[i] * (g1[k] - sum1[i - 1] + P) % P + P) % P;
        g2[j] = (g2[j] - pr[i] * pr[i] % P * (g2[k] - sum2[i - 1] + P) % P + P) % P;
    }
    cout << (S(n, 0) + 1) % P << "\n";
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

