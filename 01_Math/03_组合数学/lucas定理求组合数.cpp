ll fac[N];
ll qpow(ll a, ll b){
    ll ans = 1;
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
ll inv(ll x, ll mod){
    return qpow(x, mod - 2);
}
inline ll C(ll n, ll m) {
    return n < m ? 0 : fac[n] * inv(fac[m], mod) % mod * inv(fac[n - m], mod) % mod;
}
inline ll lucas(ll n, ll m) {
    return m == 0 ? 1 % mod : lucas(n / mod, m / mod) * C(n % mod, m % mod) % mod;
}