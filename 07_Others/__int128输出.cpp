void print(__int128 x){
    if (x < 0) {
        cout << "-";
        x = -x;
    }
    if (x > 9) print(x / 10);
    cout << (int)(x % 10);
}