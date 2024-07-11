template<class T>
struct Matrix {
    vector<vector<T>> a;
    Matrix() {}
    Matrix(const vector<vector<T>> &a) : a(a) {}
    vector<T> operator[](int idx) const {
        return a[idx];
    }
    vector<T> &operator[](int idx) {
        return a[idx];
    }
    friend Matrix operator*(const Matrix &a, const Matrix &b) {
        int n1 = a.a.size();
        int m1 = a[0].size();
        int n2 = b.a.size();
        int m2 = b[0].size();
        assert(m1 == n2);
        vector<vector<T>> c(n1, vector<T> (m2));
        for (int i = 0; i < n1; i++)
        for (int j = 0; j < m2; j++)
        for (int k = 0; k < m1; k++)
            c[i][j] += a[i][k] * b[k][j];
        return Matrix(c);
    }
    void matrix_pow(Matrix c, i64 k) {
        while (k) {
            if (k & 1) *this = *this * c;
            c = c * c;
            k >>= 1;
        }
    }
    void print() {
        for (auto x : a) {
            for (auto y : x) cout << y << ' ';
            cout << '\n';
        }
        cout << '\n';
    }
};