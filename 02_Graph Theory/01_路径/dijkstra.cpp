auto dijkstra = [&](int root, vector<int> &dis) -> void {
    priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> que;
    que.push({0, root});
    dis[root] = 0;
    while (!que.empty()) {
        auto [val, u] = que.top(); que.pop();
        if (val > dis[u]) continue;
        for (auto [v, w] : g[u]) {
            if (dis[v] > w + val) {
                dis[v] = w + val;
                que.push({w + val, v});
            }
        }
    }
};