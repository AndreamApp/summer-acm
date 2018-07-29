#include <bits/stdc++.h>

using namespace std;

/*
状态：g(i, j, k) 表示当前在第i个岛，每5分钟可捕获j条鱼，剩余时间为k 的 能捕获的最大鱼数, 1<=i<=n, 0<=j, 0<=k<=12*h
初始：g(1, f[1], h*12)
边界：g(n, f[n], k) = (2*f[n] - N*d[n]) * N / 2, d[n] != 0. 其中项数 N = min(k, f[n]/d[n])
                      k*f[n], d[n] = 0.                     # 等差数列求和 
转移：g(i, j, k) = max( g(i, j-d[i], k-1) + j, g(i+1, f[i+1], k-t[i]) ) , 1<=i<=n-1 
		# g(i, j-d[i], k-1) + j 表示下五分钟继续在i岛捕鱼的收益 
		# g(i+1, f[i+1], k-t[i]) 表示下五分钟前去i+1到捕鱼的收益 
*/

const int MAX = 27;

int n, h;
int f[MAX];
int d[MAX];
int t[MAX];

int stay[MAX];
int fish;

int g(int i, int j, int k, int curr){
	if(k <= 0) return curr;
	if(i == n && j == f[n]) {
		if(d[n] == 0) return k * f[n];
		int N = min(k, f[n]/d[n]+(f[n]%d[n]!=0));
		int res = (2*f[n] - (N-1)*d[n]) * N / 2;
//		printf("g(%d, %d, %d) = %d\n", i, j, k, res + curr);
		return res+curr;
	}
	int res;
	if(j <= 0) {
		res = g(i+1, f[i+1], k-t[i], curr);
		stay[i] += t[i];
	}
	else{
		int r1 = g(i, max(0,j-d[i]), k-1, curr+j);
		int r2 = g(i+1, f[i+1], k-t[i], curr);
		if(r1 >= r2){
			stay[i]++;
			res = r1;
		}
		else{
			stay[i]+=t[i];
			res = r2;
		}
	}
//	printf("g(%d, %d, %d) = %d\n", i, j, k, res);
	return res;
}

int main(){
	while(~scanf("%d", &n) && n){
		scanf("%d", &h);
		for(int i = 1; i <= n; i++){
			scanf("%d", &f[i]);
		}
		for(int i = 1; i <= n; i++){
			scanf("%d", &d[i]);
		}
		for(int i = 1; i <= n-1; i++){
			scanf("%d", &t[i]);
		}
		memset(stay, 0, sizeof stay);
		int res = g(1, f[1], h*12, 0);
		for(int i = 1; i <= n; i++){
			printf("%d, ", stay[i]);
		}
		printf("\nNumber of fish expected: %d\n", res);
	}
	return 0;
}
