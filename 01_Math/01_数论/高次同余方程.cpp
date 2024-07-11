i64 baby_step(i64 a, i64 b, i64 p) {
    map<i64, i64> mp;
    b %= p;
    i64 t = sqrt(p) + 1;
    for (int j = 0; j < t; j++) {
        i64 val = b * qpow(a, j, p) % p;
        mp[val] = j;
    }
    a = qpow(a, t, p);
    if (a == 0) return b == 0 ? 1 : -1;
    for (int i = 0; i < t; i++) {
        i64 val = qpow(a, i, p);
        i64 j = mp.find(val) == mp.end() ? -1 : mp[val];
        if (j >= 0 && i * t - j >= 0) return i * t - j;
    }
    return -1;
}