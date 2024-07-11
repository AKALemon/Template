vector<array<i64, 2>> g[N], vg[N];

int dfn[N], deep[N], tot = 0, fa[N][LOGN + 1];
i64 mdis[N][LOGN + 1];

void Dfs(int u, int father) {
    deep[u] = deep[father] + 1;
    fa[u][0] = father;
    dfn[u] = ++tot;    
    for (int i = 1; i <= LOGN; i++) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
        mdis[u][i] = min(mdis[u][i - 1], mdis[fa[u][i - 1]][i - 1]);
    }

    for (auto [v, w] : g[u]) {
        if (v == father) continue;
        mdis[v][0] = w;
        Dfs(v, u);
    }
}

int Lca(int x, int y){
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
}

i64 getdis(int x, int y) {
    i64 val = inf;
    for (int i = LOGN; i >= 0; i--) {
        if (deep[x] - (1 << i) >= deep[y]) {
            val = min(val, mdis[x][i]), x = fa[x][i];
        }
    }
    return val;
}

bool cmp(int i, int j) {
    return dfn[i] < dfn[j];
}

void connect(int u, int v) {
    i64 w = getdis(v, u);
    vg[u].push_back({v, w});
};
bool vis[N];

i64 dfs(int u) {
    i64 res = 0;
    for (auto [v, w] : vg[u]) {
        i64 nx = dfs(v);
        if (vis[v]) res += w;
        else res += min(w, nx);
    }
    vg[u].clear();
    return res;
}

void solve(){
    int n;cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, w;cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    for (int i = 0; i <= LOGN; i++)
        mdis[0][i] = mdis[1][i] = inf;
    Dfs(1, 0);
    int q; cin >> q;
    while (q--) {
        int m;cin >> m;
        vector<int> k(m);
        for (int i = 0; i < m; i++) {
            cin >> k[i];
            vis[k[i]] = true;
        }
        auto build_vt = [&]() {
            sort(k.begin(), k.end(), cmp);
            vector<int> a;
            a.emplace_back(1);
            for (int i = 0; i < m - 1; i++) {
                a.emplace_back(k[i]);
                a.emplace_back(Lca(k[i], k[i + 1]));
            }
            a.emplace_back(k[m - 1]);
            sort(a.begin(), a.end(), cmp);
            a.erase(unique(a.begin(), a.end()), a.end());
            int len = a.size();
            for (int i = 0; i < len - 1; i++) {
                connect(Lca(a[i], a[i + 1]), a[i + 1]);
            }
        };
        build_vt();
        cout << dfs(1) << '\n';
        for (auto x : k) {
            vis[x] = false;
        }
    }

}
