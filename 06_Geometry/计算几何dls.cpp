const db eps = 1e-9;

inline int sign(db a){ return a < -eps ? -1 : a > eps;}
inline int cmp(db a, db b){return sign(a - b);}

struct P {
	db x, y;
	P() {}
	P(db _x, db _y) : x(_x), y(_y) {}
	P operator+(P p) const { return {x + p.x, y + p.y}; }
	P operator-(P p) const { return {x - p.x, y - p.y}; }
	P operator*(db d) const { return {x * d, y * d}; }
	P operator/(db d) const { return {x / d, y / d};}

	bool operator<(P p) const {
		int c = cmp(x, p.x);
		if (c) return c == -1;
		return cmp(y, p.y) == 1;
	}

	bool operator==(P p) const {
		return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;
	}
	void read() { cin >> x >> y; }
	void print(){ cout << "(" << x << "," << y << ")" << " ";}
	db dot(P p) { return x * p.x + y * p.y; }
	db det(P p) { return x * p.y - y * p.x; }

	db distTo(P p) { return (*this - p).abs(); }
	db alpha() { return atan2(y, x); }
	db abs() { return sqrt(abs2()); }
	db abs2() { return x * x + y * y; }
	P rot90() { return P(-y, x); }
	P unit() { return *this/abs(); }
	int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
	P rot(db an){ return {x*cos(an) - y*sin(an), x*sin(an) + y*cos(an)}; }
};  

// p1p2 × p1p3
db cross(P p1, P p2, P p3){ return P(p2 - p1).det(P(p3 - p1)); }
db crossOp(P p1, P p2, P p3){ return sign(cross(p1, p2, p3)); }//可能有精度问题

// 直线p1p2，q1q2是否恰有一个交点
bool chkLL(P p1, P p2, P q1, P q2){
	db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return sign(a1 + a2) != 0;
}

//求直线p1p2, q1q2的交点
P isLL(P p1, P p2, P q1, P q2){
	db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	return (p1 * a2 + p2 * a1) / (a1 + a2);
}

//判断区间 [l1, r1], [l2, r2] 是否相交
bool intersect(db l1, db r1, db l2, db r2){
	if(l1 > r1) swap(l1, r1); if(l2 > r2) swap(l2, r2);
	return !( cmp(r1, l2) == -1 || cmp(r2, l1) == -1);
}

//线段p1p2, q1q2 相交
bool isSS(P p1, P p2, P q1, P q2){
	return intersect(p1.x,p2.x,q1.x,q2.x) && intersect(p1.y,p2.y,q1.y,q2.y) &&
			crossOp(p1,p2,q1) * crossOp(p1,p2,q2) <= 0 && 
			crossOp(q1,q2,p1) * crossOp(q1,q2,p2) <= 0;
}

//线段p1p2, q1q2 严格相交
bool isSS_strict(P p1, P p2, P q1, P q2) {
	return 	crossOp(p1,p2,q1) * crossOp(p1,p2,q2) < 0 && 
			crossOp(q1,q2,p1) * crossOp(q1,q2,p2) < 0;
}

//m 在 a 和 b 之间
bool isMiddle(db a, db m, db b){
	if(a > b)swap(a, b);
	return cmp(a, m) <= 0 && cmp(m, b) <= 0;
}
bool isMiddle(P a, P m, P b){
	return isMiddle(a.x, m.x, b.x) && isMiddle(a.y, m.y, b.y);
}

// 点p在线段p1p2上
bool onSeg(P p1, P p2, P q){
	return crossOp(p1, p2, q) == 0 && isMiddle(p1, q, p2);
}

// 点p严格在p1p2上
bool onSeg_strict(P p1, P p2, P q){
	return crossOp(p1, p2, q) == 0 && sign((q-p1).dot(p1-p2)) * sign((q-p2).dot(p1-p2)) < 0;
}

//求 q 到 直线p1p2 的投影（垂足） 要求p1 != p2
P proj(P p1, P p2, P q) {
	P dir = p2 - p1;
	return p1 + dir * (dir.dot(q - p1) / dir.abs2());
}


//求 q 以直线p1p2 为轴的反射
P reflect(P p1, P p2, P q){
	return proj(p1,p2,q) * 2 - q;
}


//求 q 到 线段p1p2 的最小距离
db nearest(P p1, P p2, P q) {
	if(p1 == p2) return p1.distTo(q);
	P h = proj(p1, p2, q);
	if(isMiddle(p1, h, p2))
		return q.distTo(h);
	return min(p1.distTo(q), p2.distTo(q));
}


// 求线段p1p2 与 线段q1q2的距离
db disSS(P p1, P p2, P q1, P q2){
	if(isSS(p1, p2, q1, q2)) return 0;
	return min({nearest(p1, p2, q1), nearest(p1, p2, q2), nearest(q1, q2, p1), nearest(q1, q2, p2)});
}


//以x的负半轴（包括）做起点，绕原点逆时针旋转一周
//极角排序
// sort(p, p + n, [&](P &a, P &b) {
// 	int qa = a.quad(), qb = b.quad();
// 	if(qa != qb) return qa < qb;
// 	else return sign(a.det(b)) > 0;
// });

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
	for(int k = 1; k <= n; k++) 
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