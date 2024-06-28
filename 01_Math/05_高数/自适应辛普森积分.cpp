db simpson(db l, db r) {
    db mid = (l + r) / 2;
    return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6;  // 辛普森公式
}

db asr(db l, db r, db eps, db ans, int step) {
    db mid = (l + r) / 2;
    db fl = simpson(l, mid), fr = simpson(mid, r);
    if (abs(fl + fr - ans) <= 15 * eps && step < 0)
        return fl + fr + (fl + fr - ans) / 15;  // 足够相似的话就直接返回
    return  asr(l, mid, eps / 2, fl, step - 1) +
            asr(mid, r, eps / 2, fr, step - 1);  // 否则分割成两段递归求解
}

db calc(db l, db r, db eps) {
    return asr(l, r, eps, simpson(l, r), 12);
}