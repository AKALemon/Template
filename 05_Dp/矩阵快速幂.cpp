struct Matrix {
    vector<vector<i64>> a;
    Matrix() {}
    Matrix(int n) {resize(n);}
    Matrix(const vector<vector<i64>> &a) : a(a) {}
    int size() const { return a.size(); }
    void resize(int n) {
        a.resize(n);
        for (int i = 0; i < n; i++) {
            a[i].assign(n, 0);
            a[i][i] = 1;
        }
    }
    vector<i64> operator[](int idx) const {
        return a[idx];
    }
    vector<i64> &operator[](int idx) {
        return a[idx];
    }
    friend Matrix operator*(const Matrix &a, const Matrix &b) {
        int n = a.size();
        vector<vector<i64>> c(n, vector<i64> (n));
        for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        for (int k = 0; k < n; k++)
            c[i][j] = (c[i][j] + a[i][k] * b[k][j] % mod) % mod;
        return Matrix(c);
    }
};
Matrix matrix_pow(Matrix c, i64 k) {
    Matrix b(c.size());
    while (k) {
        if (k & 1) b = b * c;
        c = c * c;
        k >>= 1;
    }
    return b;
}
