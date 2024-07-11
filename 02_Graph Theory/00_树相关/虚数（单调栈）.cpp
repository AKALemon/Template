#include<bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
constexpr int N = 1e5 + 50, LOGN = 20;

constexpr i64 P = 998244353;
using i64 = long long;
// assume -P <= x < 2P
i64 norm(i64 x) {
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}
template<class T>
T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    i64 x;
    Z(i64 x = 0) : x(norm(x % P)) {}
    i64 val() const {
        return x;
    }
    Z operator-() const {
        return Z(norm(P - x));
    }
    Z inv() const {
        // assert(x != 0);
        if (x == 0) return 0;
        return power(*this, P - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = i64(x) * rhs.x % P;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, Z &a) {
        i64 v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Z &a) {
        return os << a.val();
    }
};
int n, m;
vector<pair<int, Z>> G[N], order[N];
int in[N], out[N], dft;
int fa[N][LOGN];
int dep[N], instack[N];
Z muldep[N];

void dfs(int u, Z d) {
    for (int i = 1; i < LOGN; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    muldep[u] = d;
    in[u] = ++dft;
    instack[u] = 1;
    for (auto [v, w] : G[u]) {
        if (!in[v]) {
            fa[v][0] = u, dep[v] = dep[u] + 1;
            dfs(v, d * w);    
        } else if (in[v] < in[u]) {
            if (!instack[v])
                order[v].push_back({u, w});
        } else {
            order[v].push_back({u, w});
        }
    }
    out[u] = dft;
    instack[u] = 0;
}
vector<int> vG[N];
Z ans[N], val[N], dp[N];
int st[N], tot;

bool ancestor(int u, int v) {
    return in[u] <= in[v] && out[u] >= out[v];
}

int LCA(int u, int v) {
    if (ancestor(u, v)) return u;
    for (int i = LOGN - 1; i >= 0; i--) {
        if (!ancestor(fa[u][i], v)) {
            u = fa[u][i];
        }
    }
    return fa[u][0];
}
void insert(int u) {
    if (tot == -1) {
        st[++tot] = u;
        return;
    }
    int p = LCA(st[tot], u);
    if (p == st[tot]) {
        st[++tot] = u;
        return;
    }
    while (tot >= 1 && dep[st[tot - 1]] >= dep[p]) {
        vG[st[tot - 1]].push_back(st[tot]);
        tot--;
    }
    if (st[tot] != p) {
        vG[p].push_back(st[tot]);
        st[tot] = p;
    }
    st[++tot] = u;
    return;
}

void solve_dp(int u, Z p) {
    dp[u] = 1 - p;
    Z cur = p * (1 - val[u]);
    Z inv = muldep[u].inv();
    for (auto v : vG[u]) {
        solve_dp(v, muldep[v] * inv);
        cur *= dp[v];
    }
    dp[u] += cur;
}
void reset(int u) {
    val[u] = 0;
    for (auto v : vG[u]) reset(v);
    vector<int> ().swap(vG[u]);
}

void solve(){
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, p, q; cin >> u >> v >> p >> q;
        G[u].push_back({v, Z(p) * Z(q).inv()});
    }
    fa[1][0] = 1;
    dfs(1, 1);
    ans[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!in[i]) continue;
        tot = -1;
        bool ok = false;
        for (auto [v, w] : order[i]) {
            if (v == 1) ok = true;
        }
        if (!ok) order[i].push_back({1, Z(0)});
        order[i].push_back({i, Z(1)});
        sort(order[i].begin(), order[i].end(), [&](pair<int, Z> a, pair<int, Z> b) {
            return in[a.first] < in[b.first];
        });
        for (auto [v, w] : order[i]) {
            insert(v), val[v] = w;
        }
        while (tot > 0) vG[st[tot - 1]].push_back(st[tot]), tot--;
        solve_dp(1, 1);
        reset(1);
        ans[i] = 1 - dp[1];
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
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

