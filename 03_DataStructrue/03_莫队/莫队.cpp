#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 50;
const ll mod = 1e9 + 7, inf = 0x3f3f3f3f3f3f3f3f;

int mp[N];

void solve(){
	int n;cin >> n;
	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++)cin >> a[i];
	int m;cin >> m;
	vector<array<int,3>> ask(m);    
	for(int i = 0; i < m; i++){
		int l, r;cin >> l >> r;
		ask[i] = {l, r, i};
	}
	int M = 1775;
	sort(ask.begin(), ask.end(), [&](array<int,3> &a, array<int,3> & b){
		if(a[0] / M != b[0] / M) return a[0] < b[0];
		if((a[0] / M) & 1) return a[1] < b[1];
		return a[1] > b[1];
	});
	int l = 1, r = 0;
	int ans = 0;

	auto add = [&](int x){
		if(!mp[a[x]]) ans++;
		mp[a[x]]++;
	};

	auto del = [&](int x){
		mp[a[x]]--;
		if(!mp[a[x]])ans--;
	};
	vector<int> res(m);
	for(int i = 0; i < m; i++){
		while(l > ask[i][0]) l--, add(l);
		while(r < ask[i][1]) r++, add(r);
		while(l < ask[i][0]) del(l), l++;
		while(r > ask[i][1]) del(r), r--;
		res[ask[i][2]] = ans;
	}
	for(int i = 0; i < m; i++){
		cout << res[i] << '\n';
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
