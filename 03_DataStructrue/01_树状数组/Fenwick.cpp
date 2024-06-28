template<class T>
struct Fenwick{
    int sz;
    vector<T> c;
    Fenwick(){sz = N - 1;c.resize(sz + 1);}
    Fenwick(int x){sz = x;c.resize(sz + 1);}
    void resize(int s) {sz = s;}
    void modify(int x, T s){
        for(int i = x; i <= sz; i += i & (-i))
            c[i] += s;
    }
    T query(int x){
        T res = 0;
        for(int i = x; i; i -= i & (-i))
            res += c[i];
        return res;
    }
    T search(T s){ //树状数组上二分
        int pos = 0;
        for(int j = 18; j >= 0; j --){
            if(pos + (1 << j) <= sz && c[pos + (1 << j)] <= s){
                pos += (1 << j);
                s -= c[pos];
            }
        }
        return pos;
    }
    T sum(int l, int r){
        return query(r) - query(l - 1);
    }
};

