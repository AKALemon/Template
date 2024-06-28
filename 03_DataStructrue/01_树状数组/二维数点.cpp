#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 50;


template<class T>
struct Fenwick{

    int sz;
    T c[N];
    Fenwick(){sz = N;}
    Fenwick(int x){sz = x;}
    void resize(int s) {sz = s;}
    void modify(int x, T s){
        for(int i = x; i <= sz; i += i & (-i))
            c[i] += s;
    }
    T query(int x){
        T res = 0;
        for(int i = x; i; i -= i & (-i))
            res += c[i];
        return res;
    }
    T search(T s){ //树状数组上二分
        int pos = 0;
        for(int j = 18; j >= 0; j --){
            if(pos + (1 << j) <= sz && c[pos + (1 << j)] <= s){
                pos += (1 << j);
                s -= c[pos];
            }
        }
        return pos;
    }
};


void solve(){
	int n, q;cin >> n >> q;
	vector<int> vx;
	vector<array<int,4>> event;
	for(int i = 0; i < n; i++){
		int x, y;cin >> x >> y;
		event.push_back({y, 0, x});
		vx.push_back(x);
	}
	for(int i = 0; i < q; i++){
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		event.push_back({y2, 2, x2, i});
		event.push_back({y1 - 1, 2, x1 - 1, i});
		event.push_back({y1 - 1, 1, x2, i});
		event.push_back({y2, 1, x1 - 1, i});
	}

	sort(event.begin(), event.end());
	sort(vx.begin(), vx.end());
	vx.erase(unique(vx.begin(), vx.end()), vx.end());
	int m = vx.size();
	Fenwick<int> t(m);
	vector<int> ans(q);
	for(auto evt : event){
		if(evt[1] == 0){
			int x = lower_bound(vx.begin(), vx.end(), evt[2]) - vx.begin() + 1;
			t.modify(x, 1);
		}else {
			int x = upper_bound(vx.begin(), vx.end(), evt[2]) - vx.begin();
			if(evt[1] == 1) ans[evt[3]] -= t.query(x);
			else ans[evt[3]] += t.query(x);
		}
	}
	for(int i = 0; i < q; i++){
		cout << ans[i] << '\n';
	}

}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int t = 1;//cin >> t;
	while(t--)solve();
}