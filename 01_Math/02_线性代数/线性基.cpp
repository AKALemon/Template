constexpr int B = 60;
struct linear_basic {
    vector<i64> num;
    linear_basic() {num.resize(B + 1);}
    linear_basic(int n) {num.resize(n);}
    bool insert(i64 x) {
        for (int i = B - 1; i >= 0; i--) {
            if (x & (1ll << i)) {
                if (num[i] == 0) {num[i] = x; return true; }
                x ^= num[i];
            }
        }
        return false;
    }
    i64 querymin(i64 x) {
        for (int i = B - 1; i >= 0; i--) {
            x = min(x, x ^ num[i]);
        }
        return x;
    }
    i64 querymax(i64 x) {
        for (int i = B - 1; i >= 0; i--) {
            x = max(x, x ^ num[i]);
        }
        return x;
    }
};