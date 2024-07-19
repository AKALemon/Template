namespace RMQ{
    i64 sum[N], table[N][LOGN], log[N];
    void init(int n){
        for(int i = 1; i <= n; i++) table[i][0] = i;
        for(int j = 1; (1 << j) <= n; j++)
            for(int i = 1; i + (1 << j) - 1 <= n; i++){
                int x = table[i][j - 1], y = table[i + (1 << (j - 1))][j - 1];
                table[i][j] = sum[x] > sum[y] ? x : y;
            }
        log[1] = 0;
        for (int i = 2; i <= n; i++) log[i] = log[i / 2] + 1;
    }
    int query(int l, int r){
        int k = log[r - l + 1];
        int x = table[l][k], y = table[r - (1 << k) + 1][k];
        return sum[x] > sum[y] ? x : y;
    }
}