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
		return cmp(y, p.y) == -1;
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
