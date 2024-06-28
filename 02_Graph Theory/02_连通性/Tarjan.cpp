#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 50;
int cnt;
int low[N], num[N], dfn;
int sccno[N];
stack<int> st;

vector<int> g[N];
void dfs(int u){
	st.push(u);
	low[u] = num[u] = ++dfn;
	for(int i = 0; i < g[u].size(); i++){
		int v = g[u][i];
		if(!num[v]){
			dfs(v);
			low[u] = min(low[v], low[u]);
		}else if(!sccno[v]){
			low[u] = min(low[u], num[v]);
		}
	}
	if(low[u] == num[u]){
		cnt++;
		while(1){
			int v = st.top();st.pop();
			sccno[v] = cnt;
			if(u == v)break;
		}
	}
}
void Tarjan(int n){
	cnt = dfn = 0;
	memset(sccno, 0, sizeof(sccno));
	memset(num, 0, sizeof(num));
	memset(low, 0, sizeof(low));
	for(int i = 1; i <= n; i++){
		if(!num[i])
			dfs(i);
	}
}
int main(){
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		g[i].clear();
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
	}
	Tarjan(n);
	cout << (cnt == 1 ? "Yes" : "No") << '\n';
}