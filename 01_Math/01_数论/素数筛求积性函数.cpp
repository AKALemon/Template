//f积性函数， p最小的素数, pe最小的素数的幂次, pr素数
int f[N], p[N], pe[N];
vector<int> pr;
void compute(int n, function<void(int)> calcpe) {
	f[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (i == pe[i]) calcpe(i);
		else f[i] = f[pe[i]] * f[i / pe[i]];
	}
}
void init(int n) {
	p[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!p[i]) p[i] = i, pe[i] = i, pr.push_back(i);
		for (auto j : pr) {
			if (i * j > n) break;
			p[i * j] = j;
			if (p[i] == j) {
				pe[i * j] = pe[i] * j;
				break;
			} else {
				pe[i * j] = j;
			}
		}
	}
	compute(n, [&](int x){
		f[x] = f[x / p[x]] + 1;
	});
}	