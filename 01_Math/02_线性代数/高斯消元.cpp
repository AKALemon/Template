int sgn(db &x) {
    if (x < -eps) return -1;
    else return x > eps;
}
 
string gauss(vector<vector<db>> &a) { // 传入增广矩阵
    int n = a.size();
    int c = 0, r = 0;
    for (c = 0, r = 0; c < n; c++) { // c列r行，遍历列
        int tmp = r;
        for (int i = r; i < n; i++) // 寻找列主元
            if (sgn(a[i][c]))
                tmp = i;
        if (sgn(a[tmp][c]) == 0) // 当前列全为0
            continue;
 
        swap(a[tmp], a[r]); // 交换列主元
 
        for (int i = n; i >= c; i--) // 倒序处理
            a[r][i] /= a[r][c];
 
        for (int i = r + 1; i < n; i++)
            if (sgn(a[i][c]))
                for (int j = n; j >= c; j--)
                    a[i][j] -= a[r][j] * a[i][c];
        r++;
    }
    if (r < n) {
        for (int i = r; i < n; i++)
            if (sgn(a[i][n]))
                return "NoSolution";
        return "InfSolution";
    }
 
    // 解放在 a[i][n]  (0<= i < n)
    for (int i = n - 1; i >= 0; i--)
        for (int j = i + 1; j < n; j++)
            a[i][n] -= a[j][n] * a[i][j];
    return "OK";
}


//取模 0无解 1有解 2无穷解
int modinv(int a) {
    return qpow(a, mod - 2);
}
int gauss(vector<vector<int>> a, vector<int> &ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i) {
            if (a[i][col] > a[sel][col]) {
                sel = i;
            }
        }
        if (a[sel][col] == 0) continue;
        for (int i = col; i <= m; ++i) {
            swap(a[sel][i], a[row][i]);
        }
        where[col] = row;
        for (int i = 0; i < n; ++i) {
            if (i != row) {
                int c = a[i][col] * modinv(a[row][col]) % mod;
                for (int j = col; j <= m; ++j) {
                    a[i][j] -= a[row][j] * c % mod;
                    a[i][j] = (a[i][j] % mod + mod) % mod;
                }
            }
        }
        ++row;
    }

    ans.assign(m, 0);
    for (int i = 0; i < m; ++i) {
        if (where[i] != -1) {
            ans[i] = a[where[i]][m] * modinv(a[where[i]][i]) % mod;
        }
    }
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < m; ++j) {
            sum += ans[j] * a[i][j] % mod;
            sum %= mod;
        }
        if (sum != a[i][m]) {
            return 0;
        }
    }

    for (int i = 0; i < m; ++i) {
        if (where[i] == -1) {
            return 2;
        }
    }
    return 1;
}

//异或
const int maxn = 1e3 + 50, maxm = 2e3 + 50;
bitset<maxn> a[maxm];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            char c; cin >> c;
            a[i][j] = c-'0';
        }
        int x;cin >> x;
        a[i][n + 1] = x;
    }

    int now, ans = 0;
    for(int i = 1; i <= n; i++) {
        now = i;
        while(now <= m && !a[now][i])
            now++;
        if(now == m + 1){
            cout << "Cannot Determine\n";
            return 0;
        }

        ans = max(ans, now);
        swap(a[now], a[i]);
        for(int j = 1; j <= m; j++) {
            if(j == i || !a[j][i])continue;
            a[j] ^= a[i];
        }
    }
    cout << ans << '\n';
    for(int i = 1; i <= n; i++) {
        if(a[i][n + 1]){
            cout << "?y7M#\n";
        }else {
            cout << "Earth\n";
        }
    }
}