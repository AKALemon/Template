namespace PolyBase {
    using Poly = std::vector<int>;
    constexpr int P(1e9 + 7);
    void inc(int &x, int y) { (x += y) >= P ? x -= P : 0; }
    int sum(int x, int y) { return x + y >= P ? x + y - P : x + y; }
    int sub(int x, int y) { return x - y < 0 ? x - y + P : x - y; }
    int fpow(int x, int k = P - 2) {
        int r = 1;
        for (; k; k >>= 1, x = 1LL * x * x % P)
            if (k & 1)
                r = 1LL * r * x % P;
        return r;
    }
    namespace FFTComplex {
        const double PI = acos(-1.0);
        struct C{
            double x, y;
            C(double x = 0, double y = 0) : x(x), y(y) {}
            C operator!() const { return C(x, -y); }
        };
        inline C operator*(C a, C b) {
            return C(a.x * b.x - a.y * b.y, a.y * b.x + b.y * a.x);
        }
        inline C operator+(C a, C b) {
            return C(a.x + b.x, a.y + b.y);
        }
        inline C operator-(C a, C b) {
            return C(a.x - b.x, a.y - b.y);
        }
        constexpr int L(1 << 18);
        C w[L];
        int r[L << 1], _ = [] {
            for (int i = 0; i < L / 2; i++)
                w[i + L / 2] = C(cos(2 * PI * i / L), sin(2 * PI * i / L));
            for (int i = L / 2 - 1; i; i--)
                w[i] = w[i << 1];
            for (int i = 1; i <= L; i <<= 1)
            {
                for (int j = 0; j < i; j++)
                {
                    r[i + j] = r[i + j >> 1] | (i >> 1) * (j & 1);
                }
            }
            return 0;
        }();
        void dft(C *a, int n) {
            for (int k = n >> 1; k; k >>= 1) {
                for (int i = 0; i < n; i += k << 1) {
                    for (int j = 0; j < k; j++) {
                        C x = a[i + j], y = a[i + j + k];
                        a[i + j + k] = (x - y) * w[k + j];
                        a[i + j] = x + y;
                    }
                }
            }
        }
        void idft(C *a, int n) {
            for (int k = 1; k < n; k <<= 1) {
                for (int i = 0; i < n; i += k << 1) {
                    for (int j = 0; j < k; j++) {
                        C &x = a[i + j], y = a[i + j + k] * w[k + j];
                        a[i + j + k] = x - y, x = x + y;
                    }
                }
            }
            for (int i = 0; i < n; i++)
                a[i].x /= n, a[i].y /= n;
            std::reverse(a + 1, a + n);
        }
    } // namespace FFTComplex
    using namespace FFTComplex;
    int norm(int n) { return 1 << std::__lg(n * 2 - 1); }
    void norm(Poly &a) {
        if (a.size()) a.resize(norm(a.size()));
    }
    Poly conv(Poly a, Poly b) {
        int n = a.size();
        assert((n & n - 1) == 0);
        std::vector<C> f(n), g(n), p(n), q(n);
        for (int i = 0; i < n; i++) {
            f[i] = C(a[i] >> 15, a[i] & 0x7fff);
        }
        for (int i = 0; i < n; i++) {
            g[i] = C(b[i] >> 15, b[i] & 0x7fff);
        }
        dft(f.data(), n), dft(g.data(), n);
        for (int k = 1, i = 0, j; k < n; k <<= 1) {
            for (; i < k * 2; i++) {
                j = i ^ k - 1;
                p[i] = C(0.5, 0) * g[i] * (f[i] + !f[j]);
                q[i] = C(0, -0.5) * g[i] * (f[i] - !f[j]);
            }
        }
        idft(p.data(), n), idft(q.data(), n);
        for (int i = 0; i < n; i++) {
            ll x, y, z, w;
            x = p[i].x + 0.5;
            y = p[i].y + 0.5;
            z = q[i].x + 0.5;
            w = q[i].y + 0.5;
            a[i] = ((x % P << 30) + ((y + z) % P << 15) + w) % P;
        }
        return a;
    }
    Poly operator*(Poly a, Poly b) {
        int len = a.size() + b.size() - 1, n = norm(len);
        std::vector<C> f(n), g(n), p(n), q(n);
        for (int i = 0; i < a.size(); i++) {
            f[i] = C(a[i] >> 15, a[i] & 0x7fff);
        }
        for (int i = 0; i < b.size(); i++) {
            g[i] = C(b[i] >> 15, b[i] & 0x7fff);
        }
        dft(f.data(), n), dft(g.data(), n);
        for (int k = 1, i = 0, j; k < n; k <<= 1) {
            for (; i < k * 2; i++) {
                j = i ^ k - 1;
                p[i] = C(0.5, 0) * g[i] * (f[i] + !f[j]);
                q[i] = C(0, -0.5) * g[i] * (f[i] - !f[j]);
            }
        }
        idft(p.data(), n), idft(q.data(), n);
        a.resize(len);
        for (int i = 0; i < len; i++)
        {
            ll x, y, z, w;
            x = p[i].x + 0.5;
            y = p[i].y + 0.5;
            z = q[i].x + 0.5;
            w = q[i].y + 0.5;
            a[i] = ((x % P << 30) + ((y + z) % P << 15) + w) % P;
        }
        return a;
    }
} // namespace PolyBase
using namespace PolyBase;