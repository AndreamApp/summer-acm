// http://icpcsummer.openjudge.cn/2018hw1/16/
/*
状态：dp[i] 表示最后地点为第i个时的最大利润，1<=i<=n，求dp[n] 
条件：dp[i] = i; 1<=i<=n
方程：dp[i] = max(dp[j]) + p[i], 1<=i<=n, 1<=j<=min(i-1, m[i]-k-1)
复杂度：O(n)*O(n) = O(n^2) 
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>

using namespace std;

const int N = 105;

int m[N];
int p[N];
int dp[N];

int main(){
	int T, n, k;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; i++){
			scanf("%d", &m[i]);
		}
		for(int i = 1; i <= n; i++){
			scanf("%d", &p[i]);
			dp[i] = p[i]; // 设置合理的初始条件，简化dp判断 
		}
		
		for(int i = 1; i <= n; i++){
			// 在一定的区间内搜索j的值 
			for(int j = i-1; j >= 1; j--){
				if(m[j] <= m[i]-k-1){
					dp[i] = max(dp[i], dp[j] + p[i]);
				}
			}
		}
		
		// 在最终结果中找最大值 
		int res = 0;
		for(int i = 1; i <= n; i++){
			if(dp[i] > res) res = dp[i];
		}
		printf("%d\n", res);
	}
	return 0;
}
