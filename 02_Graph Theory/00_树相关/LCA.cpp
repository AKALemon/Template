vector<int> deep(n + 1);
vector fa(n + 1, vector<int> (LOGN + 1));
auto dfs = [&](auto self, int u, int father) ->void{
    deep[u] = deep[father] + 1;
    fa[u][0] = father;
    for (int i = 1; i <= LOGN; i++) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for (auto v : g[u]) {
        if (v == father) continue;
        self(self, v, u);
    }
};
dfs(dfs, 1, 0);
auto lca = [&](int x, int y) ->int {
    if (deep[x] < deep[y]) swap(x, y);
    for (int i = LOGN; i >= 0; i--) {
        if (deep[x] - (1 << i) >= deep[y]) x = fa[x][i];
    }
    if (x == y) return x;
    for (int i = LOGN; i>= 0; i--)
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i], y = fa[y][i];
        }
    return fa[x][0];
};