#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long 
#define ls k<<1
#define rs k<<1|1
const int N = 1e5 + 50, MOD = 1e9 + 7, inf = 0x3f3f3f3f;

struct node{
	int nxt, v;
}edge[N * 2];
int head[N * 2],Tot;

void addedge(int u, int v){
	edge[++Tot].v = v;
	edge[Tot].nxt = head[u];
	head[u] = Tot;
}


int deep[N];//节点的深度 
int fa[N];//节点的父亲 
int son[N];//节点的重儿子 
int tot[N];//节点子树的大小

int dfs1(int now, int f, int dep) {
    deep[now] = dep;
    tot[now] = 1;
    int maxson = -1;
    for (int i = head[now]; i != -1; i = edge[i].nxt) {
        if (edge[i].v == f) continue;
        tot[now] += dfs1(edge[i].v, now, dep + 1);
        if (tot[edge[i].v] > maxson) maxson = tot[edge[i].v], son[now] = edge[i].v;
    }
    return tot[now];
}

int idx[N], top[N], cnt, eid[N];
int a[N], b[N];
void dfs2(int now, int topf) {
    idx[now] = ++cnt;
    a[cnt] = b[now];
    top[now] = topf;
    if (!son[now]) return ;
    dfs2(son[now], topf);
    for (int i = head[now]; i != -1; i = edge[i].nxt)
        if (!idx[edge[i].v])
            dfs2(edge[i].v, edge[i].v);
   // eid[now] = cnt; 
}

struct Tree {
    int l, r, w, siz, f;
} T[N * 4];

void update(int k) { //更新
    T[k].w = T[ls].w + T[rs].w;
}

void Build(int k, int ll, int rr) {
    T[k].l = ll; T[k].r = rr; T[k].siz = rr - ll + 1;
    if (ll == rr) {
        T[k].w = a[ll];
        return ;
    }
    int mid = (ll + rr) >> 1;
    Build(ls, ll, mid);
    Build(rs, mid + 1, rr);
    update(k);
}

void pushdown(int k) { //下传标记
    if (!T[k].f) return ;
    T[ls].w = T[ls].w + T[ls].siz * T[k].f;
    T[rs].w = T[rs].w + T[rs].siz * T[k].f;
    T[ls].f = T[ls].f + T[k].f;
    T[rs].f = T[rs].f + T[k].f;
    T[k].f = 0;
}

void IntervalAdd(int k, int ll, int rr, int val) { //区间加
    if (ll <= T[k].l && T[k].r <= rr) {
        T[k].w += T[k].siz * val;
        T[k].f += val;
        return ;
    }
    pushdown(k);
    int mid = (T[k].l + T[k].r) >> 1;
    if (ll <= mid)    IntervalAdd(ls, ll, rr, val);
    if (rr > mid)    IntervalAdd(rs, ll, rr, val);
    update(k);
}
int IntervalSum(int k, int ll, int rr) { //区间求和
    int ans = 0;
    if (ll <= T[k].l && T[k].r <= rr)
        return T[k].w;
    pushdown(k);
    int mid = (T[k].l + T[k].r) >> 1;
    if (ll <= mid) ans = ans + IntervalSum(ls, ll, rr);
    if (rr > mid)  ans = ans + IntervalSum(rs, ll, rr);
    return ans;
}

void TreeSum(int x, int y) { //x与y路径上的和
    int ans = 0;
    while (top[x] != top[y]) {
        if (deep[top[x]] < deep[top[y]]) swap(x, y);
        ans = ans + IntervalSum(1, idx[ top[x] ], idx[x]);
        x = fa[ top[x] ];
    }
    if (deep[x] > deep[y]) swap(x, y);
    ans = ans + IntervalSum(1, idx[x], idx[y]);
    printf("%d\n", ans);
}
void TreeAdd(int x, int y, int val) { //对于x,y路径上的点加val的权值
    while (top[x] != top[y]) {
        if (deep[top[x]] < deep[top[y]]) swap(x, y);
        IntervalAdd(1, idx[ top[x] ], idx[x], val);
        x = fa[ top[x] ];
    }
    if (deep[x] > deep[y])    swap(x, y);
    IntervalAdd(1, idx[x], idx[y], val);
}

void solve(){
    int n, m;
    cin >> n >> m;
    memset(head,-1, sizeof(head));
    
    for(int i = 1; i < n; i++){
        int x;cin >> fa[i] >> b[i];
        addedge(i, fa[i]);
        addedge(fa[i], i);
    }
    dfs1(0, -1, 0);
    dfs2(0, 0);
    Build(1, 1, n);

    while(m--){
        char c;cin >> c;
        int x, y, z;
        cin >> x >> y >> z;
        if(c == 'S'){
            ll now = IntervalSum(1, idx[x], idx[x]);
            if( now < y)
                IntervalAdd(1, idx[x], idx[x], z);
        }else {
            
            ll now = IntervalSum(1, idx[x], idx[x] + tot[x] - 1);
            
            if(now < (ll)y * tot[x])
                IntervalAdd(1, idx[x], idx[x] + tot[x] - 1, z);
        }

    }

    for(int i = 0; i < n; i++){
        cout << IntervalSum(1, idx[i], idx[i]) << '\n';
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
