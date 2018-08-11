// http://icpcsummer.openjudge.cn/2018hw1/19/
/*
状态：dp[j] 表示前i个数里挑凑成j的方案数，1<=i<=n，1<=j<=x
条件：dp[0] = 1 
方程：dp[j] = dp[j] + dp[j-a[i]], 1<=i<=n, x>=j>=a[i] (j-a[i] >= 0)
复杂度：O(nx)  空间复杂度：O(x)

注意：
1. 确定每个下标的取值范围，即循环范围 
2. 每一个下标都应该>=0（确定自然定义域） 
3. 不要重复计算初始条件。
   初始条件为i=0的情况，就从i=1开始计算； 
   初始条件为i=1的情况，就从i=2开始计算； 
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector> 

using namespace std;

const int MAXN = 205;
const int MAXX = 10005;

int a[MAXN];
int dp[MAXX];
int kind[MAXX];

int main(){
//	freopen("in.txt", "r", stdin);
	int n, x;
	scanf("%d%d", &n, &x);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]); 
	}
	dp[0] = 1;
	for(int i = 1; i <= n; i++){
		for(int j = x; j >= a[i]; j--){
			dp[j] = dp[j] + dp[j - a[i]];
		}
	}
	vector<int> res;
	for(int i = 1; i <= n; i++){
		// kind[j] 表示没有第i个数字时组成j的方案数 
		kind[0] = 1;
		for(int j = 1; j <= x; j++){
			if(j >= a[i])
				kind[j] = dp[j] - kind[j - a[i]];
			else
				kind[j] = dp[j];
		}
		if(kind[x] == 0){
			res.push_back(a[i]);
		}
	}
	
	int S = res.size();
	printf("%d\n", S);
	for(int i = 0; i < S; i++){
		if(i != 0) printf(" ");
		printf("%d", res[i]);
	}
	return 0;
}
