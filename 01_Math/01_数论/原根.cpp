#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2e5 + 50, mod = 1e9 + 7, inf = 0x3f3f3f3f;
#define int ll
int phi[MAXN]; // 欧拉函数表
bool isnp[MAXN]; // 是否不是素数
vector<int> primes; // 质数表

void init(int n); // 欧拉筛
// 实现省略，可参照之前的笔记

int qpow(int a, int n, int p){
	int res = 1;
	while(n){
		if(n & 1)res = res * a % p;
		a = a * a % p;
		n >>= 1;
	}
	return res;
}

vector<int> get_factors(int a) // 求所有因数
{
    vector<int> v;
    for (int i = 1; i * i <= a; ++i)
        if (a % i == 0)
        {
            v.push_back(i);
            if (i * i != a) v.push_back(a / i);
        }
    return v;
}
bool exist[MAXN]; // 是否存在原根
void init_exist() // 初始化exist数组
{
    exist[2] = exist[4] = true;
    for (int i = 1; i < (int)primes.size(); ++i)
    {
        int p = primes[i];
        for (int q = p; q < MAXN; q *= p)
        {
            exist[q] = true;
            if (q * 2 < MAXN)
                exist[q * 2] = true;
        }
    }
}
vector<int> get_primative_roots(int m) // 求所有原根
{
    vector<int> v;
    if (!exist[m])
        return v;
    int phiM = phi[m], fst;
    auto factors = get_factors(phiM);
    for (int i = 1;; ++i)
    {
        if (__gcd(i, m) != 1)
            continue;
        bool ok = true;
        for (auto e : factors)
            if (e != phiM && qpow(i, e, m) == 1)
            {
                ok = false;
                break;
            }
        if (ok)
        {
            fst = i;
            break;
        }
    }
    int cur = fst;
    for (int i = 1; i <= phiM; ++i)
    {
        if (__gcd(phiM, i) == 1)
            v.push_back(cur);
        cur = cur * fst % m;
    }
    return v;
}
ll euler(ll n) {
    ll rea = n;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0) {
            rea = rea - rea / i;
            while (n % i == 0) n /= i;
        }
    if (n > 1) rea = rea - rea / n;
    return rea;
}


int get_minimum_primitive_root(int m)
{
    int phiM = euler(m);
    for (int i = 1;; ++i)
    {
        if (__gcd(i, m) != 1)
            continue;
        auto factors = get_factors(phiM);
        bool ok = true;
        for (auto e : factors)
            if (e != phiM && qpow(i, e, m) == 1)
            {
                ok = false;
                break;
            }
        if (ok)
            return i;
    }
}

void solve(){
    int p;cin >> p;
    cout << get_minimum_primitive_root(p) << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--)solve();
}
