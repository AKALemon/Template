#include<bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
constexpr int N = 1e6 + 50, LOGN = 30;
constexpr i64 P = 998244353, inf = 1e9;

//FWT 完后需要先模一遍
template<typename T>
void fwt(i64 a[], int n, T f) {
    for (int d = 1; d < n; d *= 2)
        for (int i = 0, t = d * 2; i < n; i += t)
            for(int j = 0; j < d; j ++)
                f(a[i + j], a[i + j + d]);
}

void AND(i64& a, i64& b) { a += b; }
void OR(i64& a, i64& b) { b += a; }
void XOR (i64& a, i64& b) {
    i64 x = a, y = b;
    a = (x + y) % P;
    b = (x - y + P) % P;
}
void rAND(i64& a, i64& b) { a -= b; }
void rOR(i64& a, i64& b) { b -= a; }
void rXOR(i64& a, i64& b) {
    static i64 INV2 = (P + 1) / 2;
    i64 x = a, y = b;
    a = (x + y) * INV2 % P;
    b = (x - y + P) * INV2 % P;
}

// //FWT 子集卷积 i与j=0，i或j为k
// a[popcount(x)][x] = A[x]
// b[popcount(x)][x] = B[x]
// fwt(a[i]) fwt(b[i])
// c[i + j][x] += a[i][x] * b[j][x]
// rfwt(c[i])
// ans[x] = c[popcount(x)][x]

i64 a[N], b[N], A[N], B[N];
void solve(){
    int n; cin >> n;    
    int m = (1 << n);
    for (int i = 0; i < m; i++) cin >> A[i];
    for (int i = 0; i < m; i++) cin >> B[i];

    for (int i = 0; i < m; i++) a[i] = A[i], b[i] = B[i];
    fwt(a, m, OR);fwt(b, m, OR);
    for (int i = 0; i < m; i++) {
        a[i] = ((a[i] % P) * (b[i] % P) % P + P) % P;
    }
    fwt(a, m, rOR);
    for (int i = 0; i < m; i++) {
        cout << (a[i] % P + P) % P << " \n"[i == m - 1];
    } 
    for (int i = 0; i < m; i++) a[i] = A[i], b[i] = B[i];
    fwt(a, m, AND);fwt(b, m, AND);
    for (int i = 0; i < m; i++) {
        a[i] = ((a[i] % P) * (b[i] % P) % P + P) % P;
    }
    fwt(a, m, rAND);
    for (int i = 0; i < m; i++) {
        cout << (a[i] % P + P) % P << " \n"[i == m - 1];
    }
    for (int i = 0; i < m; i++) a[i] = A[i], b[i] = B[i];
    fwt(a, m, XOR);fwt(b, m, XOR);
    for (int i = 0; i < m; i++) {
        a[i] = ((a[i] % P) * (b[i] % P) % P + P) % P;
    }
    fwt(a, m, rXOR);
    for (int i = 0; i < m; i++) {
        cout << (a[i] % P + P) % P << " \n"[i == m - 1];
    }
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

