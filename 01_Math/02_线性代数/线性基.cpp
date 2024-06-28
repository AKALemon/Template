const int B = 60;
struct linear_basic {
    vector<ll> num;
    linear_basic() {num.resize(B + 1);}
    linear_basic(int n) {num.resize(n);}
    bool insert(ll x) {
        for (int i = B - 1; i >= 0; i--) {
            if (x & (1ll << i)) {
                if (num[i] == 0) {num[i] = x; return true; }
                x ^= num[i];
            }
        }
        return false;
    }
    ll querymin(ll x) {
        for (int i = B - 1; i >= 0; i--) {
            x = min(x, x ^ num[i]);
        }
        return x;
    }
    ll querymax(ll x) {
        for (int i = B - 1; i >= 0; i--) {
            x = max(x, x ^ num[i]);
        }
        return x;
    }
};