int p[N];
vector<int> pr;
void init(int n) {
	p[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!p[i]) p[i] = i, pr.push_back(i);
		for (auto j : pr) {
			if (i * j > n) break;
			p[i * j] = j;
			if (p[i] == j) {
				break;
			}
		}
	}
}
