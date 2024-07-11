i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    i64 d = a;
    if (b) d = exgcd(b, a % b, y, x), y -= x * (a / b);
    else x = 1, y = 0;
    return d;
}

// x % m[i] = a[i]
i64 excrt(const vector<i64> &m, const vector<i64> &a) {
    i64 M = m[0], R = a[0];
    int n = a.size();
    for (int i = 1; i < n; i++) {
        i64 x = 0, y = 0, d = exgcd(M, m[i], x, y);
        if ((R - a[i]) % d) return -1;
//        x = mul((R - a[i]) / d, x, m[i]);
        x = (R - a[i]) / d * x % m[i];
        R -= M * x;
        M = M / d * m[i];
        R %= M;
    }
    if (R < 0) R += M;
    return R;
}