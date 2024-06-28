vector<int> sz(n + 1);
vector<int> weight(n + 1);
vector<int> root;
auto dfs = [&](auto self, int u, int fa) -> void {
	sz[u] = 1;
	weight[u] = 0;
	for (auto v : g[u]) {
		if (v == fa) continue;
		self(self, v, u);
		sz[u] += sz[v];
		weight[u] = max(weight[u], sz[v]);
	}
	weight[u] = max(weight[u], n - sz[u]);
	if (weight[u] <= n / 2) root.push_back(u);
};