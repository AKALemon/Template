#include<bits/stdc++.h>

using i64 = long long;
constexpr int P = 1e9 + 7, N = 3e6 + 10;

i64 fac[N], invfac[N];
i64 C(int n, int m) {
    if (n < m || m < 0) return 0;
    return fac[n] * invfac[m] % P * invfac[n - m] % P;
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
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i - 1] * i % P;
    }
    invfac[N - 1] = qpow(fac[N - 1], P - 2);
    for (int i = N - 1; i > 0; i--) {
        invfac[i - 1] = invfac[i] * i % P; 
    }

    auto flip = [&](int &x, int &y, int d) -> void {
        std::swap(x, y);
        x -= d, y += d;
    };
    int n, m; std::cin >> n >> m;

    int x = n + m + 1, y = n;
    int d1 = 1, d2 = - m -2;
    i64 ans = C(x + y, x);
    while (x >= 0 && y >= 0) {
        flip(x, y, d1); (ans += P - C(x + y, x)) %= P;
        flip(x, y, d2); (ans += C(x + y, x)) %= P;
    }
    x = n + m + 1, y = n;
    while (x >= 0 && y >= 0) {
        flip(x, y, d2); (ans += P - C(x + y, x)) %= P;
        flip(x, y, d1); (ans += C(x + y, x)) %= P;
    }
    std::cout << ans << "\n";
    
    return 0;
}