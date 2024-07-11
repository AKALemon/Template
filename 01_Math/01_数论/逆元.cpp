// p为质数， O(n)递推逆元，求多个逆元
i64 n, p;
i64 inv[N];
void init() {
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i]=(p - p / i) * inv[p % i] % p;
    }
}