#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
const int N = 2e5 + 50;
const ll mod = 1e9 + 7, inf = 0x3f3f3f3f3f3f3f3f;
const double pi = acos(-1), eps = 1e-8;

int cnt[N];

struct AhoCorasickAutomaton{
	struct node{
		int son[30];
		int val;
		int fail;
		int head;
		deque<int> index;
	}node[N];

	struct Edge{
		int head;
		int next;
	}edge[N];

	int root;
	int ncnt;
	int ecnt;

	void insert(string s, int i){
		int u = root;
		for(auto c : s){
			if( node[u].son[c - 'a' + 1] == 0)
				node[u].son[c - 'a' + 1] = ++ ncnt;
			u = node[u].son[c - 'a' + 1];
		}
		node[u].index.push_back(i);
		return;
	}

	void build(){
		deque<int> q;
		for(int i = 1; i <= 26; i++)
			if(node[root].son[i])q.push_back(node[root].son[i]);
		while(!q.empty()){
			int u = q.front();q.pop_front();
			for(int i = 1; i <= 26; i++){
				if(node[u].son[i]){
					node[node[u].son[i]].fail = node[node[u].fail].son[i];
					q.push_back(node[u].son[i]);
				}else 
					node[u].son[i] = node[node[u].fail].son[i];
			}
		}
		return;
	}

	void query(string s){
		int u = root;
		for(auto c : s){
			u = node[u].son[c - 'a' + 1];
			node[u].val++;
		}
		return;
	}
	void addEdge(int tail, int head){
		ecnt++;
		edge[ecnt].head = head;
		edge[ecnt].next = node[tail].head;
		node[tail].head = ecnt;
		return;
	}

	void DFS(int u) {
		for(int e = node[u].head;e;e = edge[e].next){
			int v = edge[e].head;
			DFS(v);
			node[u].val += node[v].val;
		}
		for(auto i : node[u].index)cnt[i] += node[u].val;
		return;
	}
	void failtree() {
		for(int u = 1; u <= ncnt; u++)
			addEdge(node[u].fail, u);
		DFS(root);
		return;
	}
}ACM;

void solve(){
    int n;cin >> n;
    for(int i = 1; i <= n; i++){
    	string s;cin >> s;
    	ACM.insert(s, i);
    }
    ACM.build();
    string t;cin >> t;
    ACM.query(t);
    ACM.failtree();
    for(int i = 1; i <= n; i++)
    	cout << cnt[i] << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--)solve();
}
