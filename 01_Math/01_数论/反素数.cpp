#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const int N = 2e5 + 50, mod = 1e9 + 7;
const ll inf = ~0ull;
ll ans, best, n;

int p[16] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};

void dfs(int dept, int limit, ll tmp, int num){
	if(dept >= 16)return;
	if(num > best){
		best = num;
		ans = tmp;
	}
	if(num == best && tmp < ans) ans = tmp;
	for(int i = 1; i <= limit; i++){
		double cur = (double)tmp;
		if(n  < cur * p[dept])break;
		dfs(dept + 1, i, tmp *= p[dept], num * (i + 1));
	}
}

void solve(){
	cin >> n;
    ans = inf;
    best = 0;
    dfs(0, 63, 1, 1);
    cout << ans << ' ' << best <<'\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--)solve();
}
