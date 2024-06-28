#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 50;
const ll mod = 1e9 + 7, inf = 0x3f3f3f3f3f3f3f3f;
const double pi = acos(-1), eps = 1e-8;

struct AC{
	int tr[N][26], tot;
	int e[N], fail[N];
	void insert(string s){
		int u = 0;
		for(auto c : s){
			if(!tr[u][c - 'a']) 
				tr[u][c - 'a'] = ++tot;
			u = tr[u][c - 'a'];
		}
		e[u]++;
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
			for(int j = u; j && e[j] != -1; j = fail[j])
				res += e[j], e[j] = -1;
		}
		return res;
	}
}AC;

void solve(){
    int n;cin >> n;
    string s;
    for(int i = 0; i < n; i++){
    	cin >> s;
    	AC.insert(s);
    }

    cin >> s;
    AC.build();
    cout << AC.query(s) << '\n';

}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--)solve();
}
