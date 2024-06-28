ll baby_step(ll a, ll b, ll p) {
    map<ll, ll> mp;
    b %= p;
    ll t = sqrt(p) + 1;
    for (int j = 0; j < t; j++) {
        ll val = b * qpow(a, j, p) % p;
        mp[val] = j;
    }
    a = qpow(a, t, p);
    if (a == 0) return b == 0 ? 1 : -1;
    for (int i = 0; i < t; i++) {
        ll val = qpow(a, i, p);
        ll j = mp.find(val) == mp.end() ? -1 : mp[val];
        if (j >= 0 && i * t - j >= 0) return i * t - j;
    }
    return -1;
}