//x范围[1, n], 求f(n)
template<class T>
T lagrange_interpolation(const vector<T> &y, const T k) {
    const int n = y.size();
    if (k <= n) return y[k - 1];
    vector<T> pre(n + 1), suf(n + 2), fac(n + 1), inv(n + 1);
    pre[0] = suf[n + 1] = fac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % mod;
        pre[i] = pre[i - 1] * (k - i) % mod;
    }
    inv[n] = qpow(fac[n], mod - 2);
    for (int i = n; i >= 1; i--) {
        inv[i - 1] = inv[i] * i % mod;
        suf[i] = suf[i + 1] * (k - i) % mod;
    }
    T ans = 0;    
    for (int i = 1; i <= n; i++) {
        T P = pre[i - 1] * suf[i + 1] % mod;
        T Q = inv[i - 1] * inv[n - i] % mod;
        T mul = ((n - i) & 1) ? -1 : 1;
        ans = (ans + (Q * mul + mod) % mod * P % mod * y[i - 1] % mod) % mod;
    }
    return ans;
}