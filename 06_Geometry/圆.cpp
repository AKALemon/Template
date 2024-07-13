//判断圆和圆的关系
int type(P o1, db r1, P o2, db r2) {
	db d = o1.distTo(o2);
	if (cmp(d, r1 + r2) == 1) return 4;
	if (cmp(d, r1 + r2) == 0) return 3;
	if (cmp(d, abs(r1 - r2)) == 1) return 2;
	if (cmp(d, abs(r1 - r2)) == 0) return 1;
	return 0; 
}

//圆和直线相交
vector<P> isCL(P o, db r, P p1, P p2) {
	if (cmp(abs((o - p1).det(p2 - p1) / p1.distTo(p2)), r) > 0) return {};
	db x = (p1 - o).dot(p2 - p1), y = (p2 - p1).abs2(), d = x * x - y * ((p1 - o).abs2() - r * r);
	d = max(d, (db)0.0);
	P m = p1 - (p2 - p1) * (x / y), dr = (p2 - p1) * (sqrt(d) / y);
	return {m - dr, m + dr};
}

//圆和圆相交，需要先判圆是否完全相同
vector<P> isCC(P o1, db r1, P o2, db r2) {
	db d = o1.distTo(o2);
	if (cmp(d, r1 + r2) == 1) return {};
	if (cmp(d, abs(r1 - r2)) == -1) return {};
	d = min(d, r1 + r2);
	db y = (r1 * r1 + d * d - r2 * r2) / (2 * d), x = sqrt(r1 * r1 - y * y);
	P dr = (o2 - o1).unit();
	P q1 = o1 + dr * y, q2 = dr.rot90() * x;
	return {q1 - q2, q1 + q2};
}
//两个圆的切线，默认求外公切线，如果求内公切线 r2 = -r2，求点到圆的切线 r2 = 0
vector<pair<P, P>> tanCC(P o1, db r1, P o2, db r2) {
	P d = o2 - o1;
	db dr = r1 - r2, d2 = d.abs2(), h2 = d2 - dr * dr;
	if (sign(d2) == 0 || sign(h2) < 0) return {};
	h2 = max((db)0.0, h2);
	vector<pair<P, P>> ret;
	for (db sign : {-1, 1}) {
		P v = (d * dr + d.rot90() * sqrt(h2) * sign) / d2;
		ret.push_back({o1 + v * r1, o2 + v * r2});
	}
	if (sign(h2) == 0) ret.pop_back();
	return ret;
}
db rad(P p1, P p2) {
	return atan2l(p1.det(p2), p1.dot(p2));
}
//求三角形和圆的相交面积
db areaCT(db r, P p1, P p2) {
	vector<P> is = isCL(P(0, 0), r, p1, p2);
	if (is.empty()) return r * r *rad(p1, p2) / 2;
	bool b1 = cmp(p1.abs2(), r * r) == 1, b2 = cmp(p2.abs2(), r * r) == 1;
	if (b1 && b2) {
		if (sign((p1 - is[0]).dot(p2 - is[0])) <= 0 ||
			sign((p1 - is[1]).dot(p2 - is[1])) <= 0)
			return r * r * (rad(p1, is[0]) + rad(is[1], p2)) / 2;
		else return r * r * rad(p1, p2) / 2;
	}
	if (b1) return r * r * rad(p1, is[0]) / 2;
	if (b2) return r * r * rad(is[1], p2) / 2;
	return p1.det(p2) / 2;
}

//内心
P inCenter(P A, P B, P C) {
	db a = (B - C).abs(), b = (C - A).abs(), c = (A - B).abs();
	return (A * a + B * b + C * c) / (a + b + c);
}
//外心
P circumCenter(P a, P b, P c) {
	P bb = b - a, cc = c - a;
	db eb = bb.abs2(), ec = cc.abs2(), e = 2 * bb.det(cc);
	return a - P(bb.y * ec - cc.y * eb, cc.x * eb - bb.x * ec) / e;  
}
//垂心
P othroCenter(P a, P b, P c) {
	P ba = b - a, ca = c - a, bc = b - c;
	db Y = ba.y * ca.y * bc.y, 
	A = ca.x * ba.y - ba.x * ca.y,
	x0 = (Y + ca.x * ba.y * b.x - ba.x * ca.y * c.x) / A,
	y0 = -ba.x * (x0 - c.x) / ba.y + ca.y;
	return {x0, y0};
}

//最小圆覆盖
pair<P, db> min_circle(vector<P> ps) {
	random_shuffle(ps.begin(), ps.end());
	int n = ps.size();
	P o = ps[0]; db r = 0;
	for (int i = 1; i < n; i++) if (o.distTo(ps[i]) > r + eps) {
		o = ps[i], r = 0;
		for (int j = 0; j < i; j++) if (o.distTo(ps[j]) > r + eps) {
			o = (ps[i] + ps[j]) / 2;
			r = o.distTo(ps[i]);
			for (int k = 0; k < j; k++) if (o.distTo(ps[k]) > r + eps) {
				o = circumCenter(ps[i], ps[j], ps[k]);
				r = o.distTo(ps[i]);
			}
		}
	}
	return {o, r};
}