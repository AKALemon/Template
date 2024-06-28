i64 facinv[N], fac[N];
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
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % mod;
    facinv[N - 1] = qpow(fac[N - 1] , mod - 2);
    for(int i = N - 2; i >= 0; i--) facinv[i] = facinv[i + 1] * (i + 1) % mod;
}
i64 C (i64 n, i64 m){
    if (m > n || m < 0)return 0;
    return fac[n] * facinv[m] % mod * facinv[n - m] % mod;
}
