#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 2e5 + 50, mod = 1e9 + 7, inf = 0x3f3f3f3f;
ull seed, hsh[N];
int sym[N];
vector<int> g[N];
ull shift(ull x){
	x ^= x << 13; 
	x ^= x >> 7;
	x ^= x << 17;
	return x;
}
void dfs(int u, int fa){
	ull sum = seed, xsum = 0;
	for(int v : g[u]){
		if(v == fa) continue;
		dfs(v, u);
		sum += shift(hsh[v]), xsum ^= shift(hsh[v]);
	}
	hsh[u] = sum;
	if(!xsum){
		sym[u] = 1;
	}else {
		for(int v : g[u]){
			if(v == fa)continue;
			if(shift(hsh[v]) == xsum && sym[v]){
				sym[u] = 1;
				break;
			}
		}
	}
}
void solve(){
    srand(time(0)); seed = 1ull * rand() * rand() * rand() * rand() * rand();
    int n;cin >> n;
    for(int i = 1; i <= n; i++)
    	g[i].clear(), sym[i] = 0;
    for(int i = 1; i < n; i++){
    	int x, y;
    	cin >> x >> y;
    	g[x].push_back(y), g[y].push_back(x);
    }
    dfs(1, 0);
    cout << (sym[1] ? "YES" : "NO") << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--)solve();
}
