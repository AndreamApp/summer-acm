// http://icpcsummer.openjudge.cn/2018hw1/09/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>

using namespace std;

const int MAX = 100005;

int N;
int a[MAX];
int minn[MAX];
int maxn[MAX];
int dp[MAX];
int pd[MAX];

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &N);
		int mn = 2000000;
		for(int i = 0; i < N; i++){
			scanf("%d", &a[i]);
			if(a[i] < mn){
				mn = a[i];
			}
			minn[i] = mn;
		}
		mn = -2000000;
		for(int i = N-1; i >= 0; i--){
			if(a[i] > mn){
				mn = a[i];
			}
			maxn[i] = mn;
		}
		
		dp[0] = 0;
		for(int i = 1; i < N; i++){
			dp[i] = max(dp[i-1], a[i] - minn[i]);
		}
		pd[N] = 0;
		for(int i = N-1; i >= 0; i--){
			pd[i] = max(pd[i+1], maxn[i] - a[i]);
		}
		
		int res = 0;
		for(int i = 0; i < N; i++){
			res = max(dp[i] + pd[i+1], res);
		}
		
		printf("%d\n", res);
	}
	return 0;
}
