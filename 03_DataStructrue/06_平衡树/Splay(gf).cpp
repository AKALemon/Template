struct Splay{
    int root; 
    queue<int> q;
    vector<int> w;
    struct Node {
        int s[2], v, p;
        int sum, ms, ls, rs;
        int rev, same;
        int size;
        void init(int _p, int _v) {
            p = _p, v = _v;
            s[1] = s[0] = 0;
            sum = ms = v;
            ls = rs = max(v, 0);
            rev = same = 0;
            size = 1; 
        }
    }tr[N];

    void init(vector<int> &_w) {
        for(int i = 1; i < N; i ++) q.push(i);
        tr[0].ms = -inf;
        w.clear();
        w.push_back(-inf);
        for(auto t : _w) w.push_back(t);
        w.push_back(-inf);
        root = build(0, w.size() - 1, 0);
    }

    int getsize() {
        return tr[root].size - 2;
    }

    void pushup(int x) {
        auto &u = tr[x], &l = tr[u.s[0]], &r = tr[u.s[1]];
        u.size  = l.size + r.size + 1;
        u.sum = l.sum + r.sum + u.v;
        u.ms = max({l.ms, r.ms, l.rs + r.ls + u.v});
        u.ls = max(l.ls, l.sum + u.v + r.ls);
        u.rs = max(r.rs, r.sum + u.v + l.rs);
    }

    void pushdown(int x) {
        auto &u = tr[x], &l = tr[u.s[0]], &r = tr[u.s[1]];
        if(u.same) {
            u.same = u.rev = 0;
            if(u.s[0]) l.v = u.v, l.same = 1, l.sum = l.size * l.v;
            if(u.s[1]) r.v = u.v, r.same = 1, r.sum = r.size * r.v;
            if(u.v > 0) {
                if(u.s[0])l.ls = l.rs = l.ms = l.sum;  
                if(u.s[1])r.ls = r.rs = r.ms = r.sum;  
            }
            else {
                if(u.s[0]) l.ls = l.rs = 0, l.ms = l.v;
                if(u.s[1]) r.ls = r.rs = 0, r.ms = r.v;
            }
        }
        else if (u.rev) {
            u.rev = 0;
            if(u.s[0]) reversetree(tr[u.s[0]]);
            if(u.s[1]) reversetree(tr[u.s[1]]);
        }
    }

    void rotate(int x) {
        int y = tr[x].p, z = tr[y].p;
        int k = (x == tr[y].s[1]);
        tr[x].p = z, tr[z].s[y == tr[z].s[1]] = x;
        tr[tr[x].s[k ^ 1]].p = y, tr[y].s[k] = tr[x].s[k ^ 1];
        tr[y].p = x, tr[x].s[k ^ 1] = y;
        pushup(y), pushup(x);
    }

    void splay(int x,int k) {
        while(tr[x].p != k) {
            int y = tr[x].p, z = tr[y].p;
            if(z != k) {
                if((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
        if(!k) root = x;
    }

    int build(int l,int r,int p) {
        int u = q.front(); q.pop();
        int mid = l + r >> 1;
        tr[u].init(p, w[mid]);
        if(l < mid) tr[u].s[0] = build(l, mid - 1, u);
        if(r > mid) tr[u].s[1] = build(mid + 1, r, u);
        pushup(u);
        return u;
    }

    int insert(int k, vector<int> &_w) { // 在k后面插入一个w序列
        if(_w.size() <= 0) return 0;
        swap(_w, w);
        int l = get_k(k + 1), r = get_k(k + 2);
        splay(l, 0), splay(r, l);
        tr[r].s[0] = build(0,w.size() - 1, r);
        pushup(r),pushup(l);
    }

    int get_k(int k) {
        int u = root;
        while(u) {
            pushdown(u);
            if(tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
            else if(tr[tr[u].s[0]].size + 1 == k) return u;
            else {
                k -= tr[tr[u].s[0]].size + 1;
                u = tr[u].s[1];
            }
        }
        return -1;
    }

    void dfs(int u) {
        if(tr[u].s[0]) dfs(tr[u].s[0]), tr[u].s[0] = 0;
        if(tr[u].s[1]) dfs(tr[u].s[1]), tr[u].s[1] = 0;
        q.push(u);
    }

    void zxbl() {
        debug2(root);cout << endl;
    }

    void debug(int u) {
        pushdown(u);
        if(tr[u].s[0]) debug(tr[u].s[0]);
        cout << "(" << tr[u].v << " " << u << ")\n";
        if(tr[u].s[1]) debug(tr[u].s[1]);
    }

    void debug2(int u) {
        pushdown(u);
        if(tr[u].s[0]) debug2(tr[u].s[0]);
        if(tr[u].v != -inf) cout << tr[u].v << " ";
        if(tr[u].s[1]) debug2(tr[u].s[1]);
        pushup(u);
    }

    PII getlr(int L, int R) { // 获取区间的左右两个索引,并且这段区间转到tr[r].s[0]
        int l = get_k(L), r = get_k(R + 2);
        splay(l, 0), splay(r, l);
        return {l, r};
    }

    void deletelr(int L, int R) {
        if(L > R) return ;
        auto [l, r] = getlr(L, R);
        dfs(tr[r].s[0]);
        tr[r].s[0] = 0;
        pushup(r), pushup(l);
    }

    void make_same(int L, int R, int c) {
        auto [l, r] = getlr(L, R);
        auto &son = tr[tr[r].s[0]];
        son.v = c;
        son.sum = son.size * c;
        son.same = 1;
        son.rev = 0;
        if(c > 0) son.ms = son.ls = son.rs = son.sum;
        else son.ms = c, son.ls = son.rs = 0;
        pushup(r), pushup(l);
    }

    void reversetree(Node &son){
        son.rev ^= 1;
        swap(son.ls, son.rs);
        swap(son.s[0], son.s[1]);
    }

    void reverselr(int L, int R) {
        auto [l, r] = getlr(L, R);
        reversetree(tr[tr[r].s[0]]);
        pushup(r),pushup(l);
    }

    int sumlr(int L,int R) {
        auto [l, r] = getlr(L, R);
        return tr[tr[r].s[0]].sum;
    }

    int max_sumlr(int L,int R) {
        auto [l, r] = getlr(L, R);
        return tr[root].ms;
    }

};
