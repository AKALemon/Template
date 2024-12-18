#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 50, mod = 1e9 + 7, inf = 0x3f3f3f3f;
const int maxn = 5e4 + 10;

int a[maxn], rt[maxn], n;

struct Trie
{
	int tot;
	int child[maxn * 32][2], sum[maxn *32];
	int insert(int x, int val)
	{
		int tmp, y;
		tmp = y = ++tot;
		for(int i = 30; i >= 0; --i)
		{
			child[y][0] = child[x][0];
			child[y][1] = child[x][1];
			sum[y] = sum[x] + 1;
			int t = val >> i & 1;
			x = child[x][t];
			child[y][t] = ++tot;
			y = child[y][t];
		}
		sum[y] = sum[x] + 1;
		return tmp;
	}
	int query(int l, int r, int val)
	{
		int tmp = 0;
		for(int i =30; i >= 0; --i)
		{
			int t = val >> i & 1;
			if(sum[child[r][t^1]] - sum[child[l][t^1]]) tmp += (1<<i), r = child[r][t^1], l = child[l][t ^ 1];
			else r = child[r][t], l = child[l][t];
		}
		return tmp;
	}
}trie;

void solve(){
    int n, q;cin >> n >> q;
    vector<int> root(n + 1);
    for(int i = 1; i <= n; i++){
    	int x;cin >> x;
    	root[i] = trie.insert(root[i - 1], x);
    }
    while(q--){
    	int l, r, x;cin >> x >> l >> r;
    	l++, r++;
    	cout << trie.query(root[l - 1], root[r], x) << '\n';
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--)solve();
}
