template<class T>
T gauss(vector<vector<T>> a) {
    int n = (int)a.size();
    int sgn = 1;
    for (int k = 0; k < n; ++k) {

        int sel = -1;
        for (int i = k; i < n; ++i) {
            if (a[i][k].val()) {
                sel = i;
                break;
            }
        }
        if (sel == -1) return 0;
        if (k != sel) {
            swap(a[sel], a[k]);
            sgn *= -1;
        }
        T inv = a[k][k].inv();
        for (int i = k + 1; i < n; ++i) {
            if (a[i][k].val()) {
                T c = a[i][k] * inv;
                for (int j = k; j < n; ++j) {
                    a[i][j] -= a[k][j] * c;
                }    
            }
        }
    }
    T ans = 1;
    for (int i = 0; i < n; i++) {
        ans *= a[i][i];
    }
    return ans * sgn;
}