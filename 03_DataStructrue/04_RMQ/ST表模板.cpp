namespace RMQ{
    ll sum[N], table[N][LOGN];
    void init(int n){
        for(int i = 1; i <= n; i++)table[i][0] = i;
        for(int j = 1; (1 << j) <= n; j++)
            for(int i = 1; i + (1 << j) - 1 <= n; i++){
                int x = table[i][j - 1], y = table[i + (1 << (j - 1))][j - 1];
                table[i][j] = sum[x] > sum[y] ? x : y;
            }
    }
    int query(int l, int r){
        int k = log2(r - l + 1);
        int x = table[l][k], y = table[r - (1 << k) + 1][k];
        return sum[x] > sum[y] ? x : y;
    }
}