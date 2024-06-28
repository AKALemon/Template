// 快速幂求逆元， O(log2(p))
ll n,mod;
ll fastpow(ll val,ll p)
{
    ll base=1;
    while(p)
    {
        if(p&1)    base=(base*val)%mod;
        val=(val*val)%mod;
        p>>=1;
    }
    return base;
}
int main()
{
    scanf("%lld%lld",&n,&mod);
    for(ll i=1;i<=n;i++)
        printf("%lld\n",fastpow(i,mod-2)%mod);
    return 0;
}

// 扩展欧几里得求逆元， O(log2(n))

int n,mod;
int x,y;
int exgcd(int a,int b,int &x,int &y)
{
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    int r=exgcd(b,a%b,x,y);
    int tmp=x;x=y;y=tmp-(a/b)*y;
    return r;
}
int main()
{
    cin >> n >> mod;
    for(int i=1;i<=n;i++)
    {
        int g=exgcd(i,mod,x,y);
        while(x<0) x+=mod;
        printf("%d\n",x);
    }
    return 0;
}

// p为质数， O(n)递推逆元，求多个逆元

ll inv[N];
ll n,p;
int main()
{
    cin >> n >> p;
    inv[1]=1;
    printf("1\n");
    for(int i=2;i<=n;i++)
    {
        inv[i]=(p-p/i)*inv[p%i]%p;
        printf("%d\n",inv[i]);
    }
    return 0;
}