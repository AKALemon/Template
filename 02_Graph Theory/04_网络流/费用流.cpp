constexpr int V = 2050, E = 20050;
template<typename T>
struct MinCostGraph{
	int s, t, vtot;
	int head[V], etot;
	T dis[V], flow, cost, pf[V];
	int pre[V];
	bool vis[V];
	struct edge {
		int v, nxt;
		T f, c;
	}e[E * 2];
	void addedge(int u, int v, T f1, T c, T f2 = 0) {
		e[etot] = {v, head[u], f1, c}; head[u] = etot++;
		e[etot] = {u, head[v], f2, -c}; head[v] = etot++;
	}
	bool spfa() {
		T INF = numeric_limits<T>::max() / 2;
		for (int i = 1; i <= vtot; i++) {
			dis[i] = INF;
			vis[i] = false;
			pre[i] = -1;
			pf[i] = INF;
		}
		dis[s] = 0;
		vis[s] = true;
		queue<int> q;
		q.push(s);
		while (!q.empty()) {
			int u = q.front();
			for (int i = head[u]; ~i; i = e[i].nxt) {
				int v = e[i].v;
				if (e[i].f && dis[v] > dis[u] + e[i].c) {
					dis[v] = dis[u] + e[i].c;
					pre[v] = i;
					pf[v] = min(pf[u], e[i].f);
					if (!vis[v]) {
						vis[v] = 1;
						q.push(v);
					}
				}
			}
			q.pop();
			vis[u] = false;
		}
		return dis[t] != INF;
	}
	void augment() {
		int u = t;
		T f = pf[t];
		flow += f;
		cost += f * dis[t];
		u = t;
		while(~pre[u]) {
			e[pre[u]].f -= f;
			e[pre[u] ^ 1].f += f;
			u = e[pre[u] ^ 1].v;
		}
	}
	pair<T, T> solve() {
		flow = 0;
		cost = 0;
		while (spfa()) augment();
		return {flow, cost};
	}
	void init(int s_, int t_, int vtot_) {
		s = s_;
		t = t_;
		vtot = vtot_;
		etot = 0;
		for (int i = 1; i <= vtot; i++) head[i] = -1;
	}
};
