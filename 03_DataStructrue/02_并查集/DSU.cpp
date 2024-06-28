struct DSU {
    vector<int> fa, sz;
    DSU() {}
    DSU(int n) { init(n); } 
    void init(int n){
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
        sz.assign(n, 1);
    }
    int find(int x){ return fa[x] == x ? x : fa[x] = find(fa[x]); }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return false;
        sz[x] += sz[y];
        fa[y] = x;
        return true;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return sz[find(x)]; }
};
