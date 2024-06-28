const db PI = acos(-1);
int n, m;
int res, ans[N];
int limit = 1; //补齐的2的整数幂N
int L;//二进制的位数
int R[N]; //二进制翻转
struct Complex {
    db x, y;
    Complex (db x = 0, db y = 0) : x(x), y(y) {}
    //复数乘法： 模长相乘，幅角相加
    Complex operator * (Complex J) {
        return Complex(x * J.x - y * J.y, x * J.y + y * J.x);
    }
    Complex operator - (Complex J) {
        return Complex(x - J.x, y - J.y);
    }
    Complex operator + (Complex J) {
        return Complex(x + J.x, y + J.y);
    }
}a[N];
void FFT(Complex *A, int type) {
    for (int i = 0; i < limit; ++i) if (i < R[i]) swap(A[i], A[R[i]]);

    for (int mid = 1; mid < limit; mid <<= 1) {
        Complex wn(cos(PI / mid), type * sin(PI / mid));

        for (int len = mid << 1, pos = 0; pos < limit; pos += len) {
            Complex w(1, 0);

            for (int k = 0; k < mid; k++, w = w * wn) {
                Complex x = A[pos + k];
                Complex y = w * A[pos + mid + k];
                A[pos + k] = x + y;
                A[pos + mid + k] = x - y;
            }
        }
    }
    if(type == 1) return;
    for (int i = 0; i <= limit; i++) 
        A[i].x /= limit, A[i].y /= limit;
}

void solve(){
    cin >> n >> m;
    for (int i = 0; i <= n; i++)
        cin >> a[i].x;
    for (int i = 0; i <= m; i++)
        cin >> a[i].y;
    while(limit <= n + m)
        limit <<= 1, L++;
    for (int i = 0; i < limit; i++)
        R[i] = (R[i >> 1] >> 1 | ((i & 1) << (L - 1)));
    FFT(a, 1);
    for (int i = 0; i <= limit; i++)
        a[i] = a[i] * a[i];
    FFT(a, -1);
    for (int i = 0; i <= n + m; i++) {
        cout << int(a[i].y / 2 + 0.5) << ' ';
    }
}