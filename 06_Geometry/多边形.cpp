//正序的时候取反
//多边形面积
db area(vector<P> ps){
	db ret = 0; for(int i = 0; i < ps.size(); i++) ret += ps[i].det(ps[(i + 1) % ps.size()]);
	return ret / 2;
}
//点包含
int contain(vector<P> ps, P p){ // 2: inside, 1: on_set, 0: outside
	int n = ps.size(), ret = 0;
	for(int i = 0; i < n; i++){
		P u = ps[i], v = ps[(i + 1) % n];
		if(onSeg(u, v, p)) return 1;
		if(cmp(u.y, v.y) <= 0) swap(u, v);
		if(cmp(p.y, u.y) > 0 || cmp(p.y, v.y) <= 0)continue;
		ret ^= crossOp(p, u, v) > 0;
	}
	return ret * 2;
}

//严格凸包
vector<P> convexHull(vector<P> ps){
	int n = ps.size(); if(n <= 1) return ps;
	sort(ps.begin(), ps.end());
	vector<P> qs(n * 2);int k = 0;
	for(int i = 0; i < n; qs[k++] = ps[i++])
		while(k > 1 && crossOp(qs[k - 2], qs[k - 1], ps[i]) <= 0) --k;
	for(int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
		while(k > t && crossOp(qs[k - 2], qs[k - 1], ps[i]) <= 0) --k;
	qs.resize(k - 1); 
	return qs;
}

//不严格凸包，存在三点共线， 要先去重
vector<P> convexHullNonStrict(vector<P> ps){
	int n = ps.size(); if(n <= 1) return ps;
	sort(ps.begin(), ps.end());
	vector<P> qs(n * 2);int k = 0;
	for(int i = 0; i < n; qs[k++] = ps[i++])
		while(k > 1 && crossOp(qs[k - 2], qs[k - 1], ps[i]) < 0) --k;
	for(int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
		while(k > t && crossOp(qs[k - 2], qs[k - 1], ps[i]) < 0) --k;
	qs.resize(k - 1);
	return qs;
}

//旋转卡壳
db convecDiameter(vector<P> ps){
	int n = ps.size(); if(n <= 1) return 0;
	int is = 0, js = 0;
	for(int k = 0; k < n; k++) 
		is = ps[k] < ps[is] ? k : is, 
		js = ps[js] < ps[k] ? k : js;
	int i = is, j = js;
	db ret = ps[i].distTo(ps[j]);
	do{
		if((ps[(i + 1) % n] - ps[i]).det(ps[(j + 1) % n] - ps[j]) >= 0)
			(++j) %= n;
		else 
			(++i) %= n;
		ret = max(ret, ps[i].distTo(ps[j]));
	}while(i != is || j != js);
	return ret;
}


//直线分割多边形 取一半
vector<P> convexCut(const vector<P> &ps, P q1, P q2){
	vector<P> qs;
	int n = ps.size();
	for(int i = 0; i < n; i++){
		P p1 = ps[i], p2 = ps[(i + 1) % n];
		int d1 = crossOp(q1, q2, p1), d2 = crossOp(q1, q2, p2);
		if(d1 >= 0) qs.push_back(p1);
		if(d1 * d2 < 0) qs.push_back(isLL(p1, p2, q1, q2));
	}
	return qs;
}

//动态凸包(点)
struct PointContainer : multiset<P> {
    bool inside(iterator p) {
    	auto t2 = next(p);
    	if (t2 == end()) return false;
    	if (p == begin()) return t2->x > p->x && t2->y > p->y;
    	auto t1 = prev(p);
    	return (*t1 - *p).det(*t2 - *p) < 0;
    }
    void ins(P p) {
    	auto t = insert(p);
    	if (inside(t)) {erase(t); return;}
    	while (t != begin() && inside(prev(t))) erase(prev(t));
    	while (next(t) != end() && inside(next(t))) erase(next(t));
    }
};

//动态凸包(直线)
struct Line {
    mutable db k, m, p;
    bool operator<(const Line &o) const { return k < o.k; }
    bool operator<(db x) const { return p < x; }
    db intersect_x(const Line &o) const {
        assert(o.k != k);
        return (o.m - m) / (k - o.k);
    }
};

struct LineContainer : multiset<Line, less<>> {
    const db inf = 1.0 / 0.0;
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, false;
        if (x->k == y->k) x->p = (x->m > y->m) ? inf : -inf;
        else              x->p = x->intersect_x(*y);
        return x->p >= y->p;
    }
    void add(db k, db m) {
        auto nxt = insert({k, m, 0}), cur = nxt++, pre = cur;
        while (isect(cur, nxt)) nxt = erase(nxt);
        if (pre != begin() && isect(--pre, cur)) cur = erase(cur), isect(pre, cur);
        while ((cur = pre) != begin() && (--pre)->p >= cur->p) isect(pre, erase(cur));
    }
    db qry(db x) {
        assert(!empty());
        auto &l = *lower_bound(x);
        return l.k * x + l.m;
    }
};
