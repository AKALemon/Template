template<class T>
struct Xortrie {
    vector<array<int, 2>> ch;
    vector<T> val;
    int root, tot;
    Xortrie() {root = tot = 0; ch.push_back({0, 0}), val.push_back(0);}
    int newnode() {
        ch.push_back({0, 0});
        val.push_back(0);
        return ++tot;
    }
    void insert(int x, T v) {
        for (int i = LOGN, u = root; i >= 0; i--) {
            int c = ((x >> i) & 1);
            if (!ch[u][c]) ch[u][c] = newnode();
            u = ch[u][c];
            val[u] = (val[u] + v) % mod; 
        }
    }
    T calc(T x, T y) {
        T res = 0;
        int u = root;
        for (int i = LOGN; i >= 0; i--) {
            int j = ((x >> i) & 1);
            int k = ((y >> i) & 1);
            if (k == 1) {
                if (ch[u][j]) res = (res + val[ch[u][j]]) % mod;
                u = ch[u][j ^ 1];
            }else {
                u = ch[u][j];
            }
            if (!u) break;
        }
        res = (res + val[u]) % mod;
        return res;
    }
};