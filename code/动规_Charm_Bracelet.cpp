// http://icpcsummer.openjudge.cn/2018hw1/19/
/*
状态：dp[i][j] 表示前i个数里挑出不超过j体积的物品的最大价值，1<=i<=N，1<=j<=M，求dp[N][M]
条件：dp[0][j] = 0 (1<=j<=M)
方程：dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]] + d[i]), 1<=i<=N, 1<=j<=M (j-w[i] >= 0)
复杂度：O(NM)*O(1)  空间复杂度：O(NM)

滚动数组优化空间复杂度：
状态：dp[j] 表示前i个数里挑出不超过j体积的物品的最大价值，1<=i<=N，1<=j<=M，求i=N时的dp[M] 
条件：dp[j] = 0 (1<=j<=M)
方程：dp[j] = max(dp[j], dp[j-w[i]] + d[i]), 1<=i<=N, M>=j>=1 (j-w[i] >= 0)
复杂度：O(NM)*O(1)  空间复杂度：O(M)

注意：
1. 确定每个下标的取值范围，即循环范围 
2. 每一个下标都应该>=0（确定自然定义域） 
3. 不要重复计算初始条件。
   初始条件为i=0的情况，就从i=1开始计算；（本例中这种更简单） 
   初始条件为i=1的情况，就从i=2开始计算； 
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>

using namespace std;

const int MAXN = 3410;
const int MAXM = 12890;

int w[MAXN];
int d[MAXN];
int dp[MAXM];

int main(){
	int N, M;
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; i++){
		scanf("%d%d", &w[i], &d[i]); 
	}
	// dp[j] = max(dp[j], dp[j-w[i]] + d[i]), 1<=i<=N, M>=j>=1 (j-w[i] >= 0)
	for(int i = 1; i <= N; i++){
		for(int j = M; j >= w[i]; j--){
			dp[j] = max(dp[j], dp[j-w[i]] + d[i]);
		}
	}
	printf("%d", dp[M]);
	return 0;
}


