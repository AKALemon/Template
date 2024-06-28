#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
// #define int long long
constexpr int N = 1e6 + 50, LOGN = 30;
constexpr ll mod = 1e9 + 7, inf = 1e18;

template <typename T>
struct Fenwick {
    int n;
    vector<T> a;
    
    Fenwick(int n_ = 0) {
        init(n_);
    }
    
    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }
    
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }
    
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    
    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};


void solve(){
    int n; cin >> n;
    vector<array<ll, 2>> a(n);
    for (int i = 0; i < n; i++) {
        ll A, B; cin >> A >> B;
        a[i] = {B, A};
    }
    sort(a.begin(), a.end());

    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int i, int j) {
        return a[i][1] > a[j][1];
    });

    vector<int> A(n);
    vector<ll> B(n);
    for (int i = 0; i < n; i++) {
        A[p[i]] = i;
        B[i] = a[i][0];
    }   

    Fenwick<ll> t1(n);
    Fenwick<ll> t2(n);
    int cur = 0;
    auto get = [&](int i, int m) -> ll {
        while (cur < i) {
            t1.add(A[cur], 1);
            t2.add(A[cur], a[cur][1]);
            cur++;
        }       
        while (cur > i) {
            cur--;
            t1.add(A[cur], -1);
            t2.add(A[cur], -a[cur][1]);
        }
        int k = t1.select(m);
        return t2.sum(k);
    };

    vector<ll> ans(n + 1, -inf);
    auto calc = [&](auto self, int l, int r, int L, int R) -> void {
        if (l > r) return;
        int m = (l + r) >> 1;
        int k = -1;
        for (int i = max(L, m); i <= R; i++) {
            ll res = get(i, m) - B[i - 1];
            if (ans[m] < res) {
                ans[m] = res;
                k = i;
            }
        }
        self(self, l, m - 1, L, k);
        self(self, m + 1, r, k, R);
    };
    calc(calc, 1, n, 1, n);
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

