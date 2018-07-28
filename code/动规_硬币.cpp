// http://icpcsummer.openjudge.cn/2018hw1/19/
/*
状态：dp[i][j] 表示前i个数里挑凑成j必须使用的硬币集合(vector)，1<=i<=n，1<=j<=x，求dp[n][x]
条件：dp[0][j] = U (0<=j<=x), U为全集 
方程：dp[i][j] = dp[i-1][j] ∩dp[i-1][j-a[i]] ∪{a[i]}), 1<=i<=n, 1<=j<=x (j-a[i] >= 0)
复杂度：O(nx)*O(n)=O(xn^2)  空间复杂度：O(nx)

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
int dp[MAXN][MAXX];

void print(char * s, vector<int> & v){
	printf("%s: ", s);
	for(int i = 0; i < v.size(); i++){
		printf("%d ", v[i]);
	}
	printf("\n");
}

int main(){
	freopen("in.txt", "r", stdin);
	int n, x;
	scanf("%d%d", &n, &x);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]); 
	}
	// 条件：dp[0][j] = U (0<=j<=x), U为全集 
	for(int j = 0; j <= x; j++){
		if(a[1] == j) dp[1][j].push_back(a[1]);
		//dp[j].assign(a+1, a+n+1);
	}
	// 方程：dp[i][j] = dp[i-1][j] ∩(dp[i-1][j-a[i]] ∪{a[i]}), 1<=i<=n, x>=j>=1 (j-a[i] >= 0)
	vector<int> tmp, tmp2;
	vector<int>::iterator end;
	tmp2.resize(n);
	for(int i = 2; i <= n; i++){
		for(int j = 1; j < a[i]; j++) dp[i][j] = dp[i-1][j];
		for(int j = a[i]; j <= x; j++){ // i = 2, j = 3
			if(dp[i-1][j].size() == 0){
				if(can[i-1][j]){ // 不存在 
					can[i][j] = 1;
					continue;
				}
				if(a[i] == j){
					dp[i][j].assign(dp[i-1][j-a[i]].begin(), dp[i-1][j-a[i]].end());
					dp[i][j].push_back(a[i]);
					continue;
				}
			}
			tmp.assign(dp[i-1][j-a[i]].begin(), dp[i-1][j-a[i]].end());
			tmp.push_back(a[i]);
			end = set_intersection(dp[i-1][j].begin(), dp[i-1][j].end(), tmp.begin(), tmp.end(), tmp2.begin());
			dp[i][j].assign(tmp2.begin(), end);
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= x; j++){
			printf("dp[%d][%d]", i, j);
			print("", dp[i][j]);
		}
	}
	
	int S = dp[n][x].size();
	printf("%d\n", S);
	for(int i = 0; i < S; i++){
		if(i != 0) printf(" ");
		printf("%d", dp[n][x][i]);
	}
	return 0;
}
