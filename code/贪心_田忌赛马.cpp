#include <bits/stdc++.h>

using namespace std;

const int MAX = 1005;

int n;
int a[MAX];
int b[MAX];

bool cmp(int x, int y){
	return x > y;
}

int main(){
	while(~scanf("%d", &n) && n){
		for(int i = 0; i < n; i++){
			scanf("%d", &a[i]);
		}
		for(int i = 0; i < n; i++){
			scanf("%d", &b[i]);
		}
		
		sort(a, a+n, cmp);
		sort(b, b+n, cmp);
		
		int res = 0;
		for(int i = 0, j = 0, k = n-1, l = n-1; i <= k; ){
			if(a[i] > b[j]){
				i++; j++; res++;
			}
			else if(a[k] > b[l]){
				k--; l--; res++;
			}
			else{
				if(a[k] < b[j]) res--;
				k--; j++;
			}
		}
		printf("%d\n", res*200);
	}
	return 0;
}
