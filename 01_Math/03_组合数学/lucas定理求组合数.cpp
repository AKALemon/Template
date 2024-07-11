i64 fac[N];
i64 qpow(i64 a, i64 b){
    i64 ans = 1;
    while (b) {
        if (b & 1)ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans % mod;
}
void init(){
    fac[0] = 1;
    for(int i = 1; i < N; i++) fac[i] = i * fac[i - 1] % mod;
}
i64 inv(i64 x, i64 mod){
    return qpow(x, mod - 2);
}
inline i64 C(i64 n, i64 m) {
    return n < m ? 0 : fac[n] * inv(fac[m], mod) % mod * inv(fac[n - m], mod) % mod;
}
inline i64 lucas(i64 n, i64 m) {
    return m == 0 ? 1 % mod : lucas(n / mod, m / mod) * C(n % mod, m % mod) % mod;
}