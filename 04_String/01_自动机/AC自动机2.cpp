#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 50, SZ = 156 * 80;
const ll mod = 1e9 + 7, inf = 0x3f3f3f3f3f3f3f3f;
const double pi = acos(-1), eps = 1e-8;

struct AC{

	int tr[SZ][26], tot;
	int fail[SZ];
	int idx[SZ], val[SZ];
	int cnt[N];

	void init(){
		memset(fail, 0, sizeof fail);
		memset(tr, 0, sizeof tr);
		memset(val, 0, sizeof val);
		memset(cnt, 0, sizeof cnt);
		memset(idx, 0, sizeof idx);
		tot = 0;
	}

	void insert(string s, int id){
		int u = 0;
		for(auto c : s){
			if(!tr[u][c - 'a']) 
				tr[u][c - 'a'] = ++tot;
			u = tr[u][c - 'a'];
		}
		idx[u] = id;	
	}
	
	void build(){
		queue<int> q;
		for(int i = 0; i < 26; i++)
			if(tr[0][i])q.push(tr[0][i]);
		while(!q.empty()){
			int u = q.front();q.pop();
			for(int i = 0; i < 26; i++){
				if(tr[u][i]) {
					fail[tr[u][i]] = tr[fail[u]][i];
					q.push(tr[u][i]);
				}else 
					tr[u][i] = tr[fail[u]][i];
			}
		}
	}

	int query(string t){
		int u = 0, res = 0;
		for(auto c : t){
			u = tr[u][c - 'a'];
			for(int j = u; j; j = fail[j])
				val[j]++;
		}
		for(int i = 0; i <= tot; i++)
			if(idx[i]) 
				res = max(res, val[i]), cnt[idx[i]] = val[i];
		
		return res;
	}
}AC;

void solve(int n){
	AC.init();
    vector<string> s(n + 1);
    for(int i = 1; i <= n; i++){
    	cin >> s[i];
    	AC.insert(s[i], i);
    }
    string t;
    cin >> t;
    AC.build();
   	int x = AC.query(t);
   	cout << x << '\n';
   	for(int i = 1; i <= n; i++){
   		if(AC.cnt[i] == x)
   			cout << s[i] << '\n';
   	}

}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;

    while(cin >> t, t)solve(t);
    
}
