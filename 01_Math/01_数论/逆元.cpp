// p为质数， O(n)递推逆元，求多个逆元
i64 inv[N];
void init(int n) {
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i]=(P - P / i) * inv[P % i] % P;
    }
}