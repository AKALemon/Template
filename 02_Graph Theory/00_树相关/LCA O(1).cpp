namespace LCA_Solver {
    int dep[N], seq[N], fir[N], f[N][LOGN], _log[N], idx;
    i64 dis[N];
    void DFS(int u = 1, int fa = 0) {
        seq[++idx] = u; 
        fir[u] = idx; 
        dep[u] = dep[fa] + 1;
        for (auto [v, w] : g[u]) {
            if (v == fa) continue;
            dis[v] = dis[u] + w;
            DFS(v, u);
            seq[++idx] = u;
        }
    }
    int mindep(int x, int y) {
        return dep[x] < dep[y] ? x : y;
    }
    void Init(int u = 1) {
        DFS(u);
        _log[0] = -1; 
        for (int i = 1; i <= idx; ++i) 
            _log[i] = _log[i >> 1] + 1;
        for (int i = 1; i <= idx; ++i) 
            f[i][0] = seq[i];
        for (int j = 1; j < LOGN; ++j) 
        for (int i = 1; i + (1 << j) - 1 <= idx; ++i)
            f[i][j] = mindep(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
    }
    int LCA(int x, int y) {
        x = fir[x]; y = fir[y]; 
        if (x > y) swap(x, y);
        int k = _log[y - x + 1]; 
        return mindep(f[x][k], f[y - (1 << k) + 1][k]);
    }
    i64 getdis(int x,int y) {
        if (x == 0 || y == 0) return 0;
        return dis[x] + dis[y] - 2LL * dis[LCA(x, y)];
    }
};