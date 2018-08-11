// http://icpcsummer.openjudge.cn/2018hw1/07/
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int n;
int a[100005];
int t[100005];

long long inverse(int l, int r){
	if(r - l + 1 <= 1) return 0;
	if(r - l + 1 == 2) {
		if(a[l] > a[r]){
			swap(a[l], a[r]);
			return 1;
		}
		return 0;
	}
	int m = (l + r) / 2;
	long long res = inverse(l, m) + inverse(m+1, r);
	int i = l, j = m+1, k = l;
	// now a[i,m] and a[j,r] are sorted
	while(i <= m && j <= r){
		if(a[i] < a[j]){ // a[i]和a[j,r]不存在逆序对 
			t[k++] = a[i++];
		}
		else if(a[i] > a[j]){ // a[i,m]和a[j]全是逆序对，每个j只处理一次 
			t[k++] = a[j++];
			res += (m - i + 1);
		}
		else{
			t[k++] = a[j++];
		}
	}
	while(i <= m) t[k++] = a[i++];
	while(j <= r) t[k++] = a[j++];
	for(int i = l; i <= r; i++){
		a[i] = t[i];
	}
	return res;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	printf("%lld", inverse(0, n-1));
	return 0;
}
