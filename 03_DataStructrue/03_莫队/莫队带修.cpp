#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 50, M = 500;
const ll mod = 1e9 + 7, inf = 0x3f3f3f3f3f3f3f3f;


int cnt[N];
void solve(){
    int n, m;cin >> n >> m;
    vector<int> col(n + 1);
    for(int i = 1; i <= n; i++)cin >> col[i];
    vector<array<int, 4>> ask;
	vector<array<int, 2>> c;
	
	c.push_back({0, 0});
	for(int i = 0; i < m; i++){
		char op;cin >> op;
		if(op == 'Q'){
			int l, r;cin >> l >> r;
			ask.push_back({l, r, (int)c.size() - 1,(int)ask.size()});
		}else {
			int x, y;cin >> x >> y;
			c.push_back({x, y});
		}
	}

	sort(ask.begin(), ask.end(), [&](array<int, 4> &a, array<int, 4> &b){
		if(a[0] / M != b[0] / M)return a[0] < b[0];
		if(a[1] / M != b[1] / M)return a[1] < b[1];
		return a[2] < b[2];
	});

	m = ask.size();
	int l = 1, r = 0, now = 0, ans = 0;
	auto add = [&](int x){
		if(cnt[x] == 0)ans++;
		cnt[x]++;
	};
	auto del = [&](int x){
		cnt[x]--;
		if(cnt[x] == 0)ans--;
	};
	auto modifly = [&](int i, int j){
		if(ask[i][0] <= c[j][0] && c[j][0] <= ask[i][1]){
			del(col[c[j][0]]);
			add(c[j][1]);
		}
		swap(col[c[j][0]], c[j][1]);
	};

	vector<int> out(m);
	for(int i = 0; i < m; i++){

		while(l > ask[i][0])l--, add(col[l]);
		while(l < ask[i][0])del(col[l]), l++;
		while(r < ask[i][1])r++, add(col[r]);
		while(r > ask[i][1])del(col[r]), r--;
		
		while(now < ask[i][2]) now++, modifly(i, now);
		while(now > ask[i][2]) modifly(i, now), now--;
		out[ask[i][3]] = ans;
	}
	for(int i = 0; i < m; i++){
		cout << out[i] << '\n';
	}
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--)solve();
    return 0;
}
