template<class T>
struct Trie {
    #define L 26
    vector<array<int, L>> ch;
    vector<T> val;
    int root, tot;
    Trie() {root = tot = 0; ch.emplace_back(array<int, L>{}), val.emplace_back(0);}
    int newnode() {
        ch.emplace_back(array<int, L>{});
        val.emplace_back(0);
        return ++tot;
    }
    #undef L
    void insert(string &S, T v) {
        int u = root;
        for (auto x : S) {
            int c = x - 'a';
            if (!ch[u][c]) ch[u][c] = newnode();
            u = ch[u][c];
            val[u] += v; 
        }
    }
    T calc(string &S) {
        int u = root;
        for (auto x : S) {
            int c = x - 'a';
            if (!ch[u][c]) return 0;
            u = ch[u][c];
        }
        return val[u];
    }
};