#include<bits/stdc++.h>
using namespace std;
const int N = 11000002;
int n, P[N<<1];
char a[N], S[N<<1];
void change() {
	n = strlen(a);
	int k = 0; S[k++] = '$'; S[k++] = '#';
	for(int i = 0; i < n; i++){
		S[k++] = a[i]; S[k++] = '#';
	}
	S[k++] = '&';
	n = k;
}
void manachar() {
	int R = 0, C;
	for(int i = 1; i < n; i++) {
		if(i < R) P[i] = min(P[(C<<1) - i], P[C] + C - i);
		else P[i] = 1;
		while(S[i + P[i]] == S[i - P[i]]) P[i] ++;
		if(P[i] + i > R) {
			R = P[i] + i;
			C =i;
		}
	}
}

int main() {
	scanf("%s", a);
	change();
	manachar();
	int ans = 1;
	for(int i = 0; i < n; i++) ans = max(ans, P[i]);
	printf("%d", ans - 1);
	return 0;
}