//第二类斯特林数
vector<vector<ll>> S(n + 1, vector<ll> (n + 1));
for (int i = 0; i <= n; i++) {
	S[i][0] = !i;
	for (int j = 1; j <= i; j++) {
		S[i][j] = (S[i - 1][j - 1] + S[i - 1][j] * j % mod) % mod;
	}
}

//贝尔数
vector<vector<ll>> B(n + 1, vector<ll> (n + 1));
for (int i = 0; i <= n; i++) {
	B[i][0] = 1;
	for (int j = 1; j <= i; j++) {
		B[i][j] = (B[i - 1][j - 1] + B[i - 1][j]) % mod;
	}
}

//卡特兰数
vector<ll> C(n + 1);
C[0] = 1;
for (int i = 1; i <= n; i++) C[i] = C[i - 1] * (4 * i - 2) / (i + 1);

//分拆数
vector<ll> p(n + 1), a(2 * n + 2);
p[0] = 1, p[1] = 1, p[2] = 2;
for (int i = 1; i <= n; i++) {
    a[2 * i] = i * (i * 3 - 1) / 2;
    a[2 * i + 1] = i * (i * 3 + 1) / 2;
}    
for (int i = 3; i <= n; i++) {
    for (int j = 2; a[j] <= i; j++) {
        if (j & 2) p[i] = (p[i] + p[i - a[j]] + mod) % mod;
        else p[i] = (p[i] - p[i - a[j]] + mod) % mod;
    }
}