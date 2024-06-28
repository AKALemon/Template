int root[N], cnt = 0;
struct node {
    int l, r, val;
}p[N * 40];

void update(int l, int r, int pre, int &now, int k) {
    p[now = ++cnt] = p[pre];
    p[now].val++;
    if (l == r) return;
    int mid = l + r >> 1;
    if (k <= mid) update(l, mid, p[pre].l, p[now].l, k);
    else update(mid + 1, r, p[pre].r, p[now].r, k);
}

int query(int l, int r, int ql, int qr, int k) {
    if (l == r) return l;
    int mid = l + r >> 1;
    int tmp = p[p[qr].l].val - p[p[ql].l].val;
    if (k <= tmp) return query(l, mid, p[ql].l, p[qr].l, k);
    else return query(mid + 1, r, p[ql].r, p[qr].r, k - tmp); 
}