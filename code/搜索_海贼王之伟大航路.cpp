// http://icpcsummer.openjudge.cn/2018hw1/23/
#include <bits/stdc++.h>

using namespace std;

const int MAX = 18;

int n;
int d[MAX][MAX];
int t;
int mint = 1 << 30;

int dp[1<<15][20]; // dp[i][j]表示在i状态下最后经过j的最短距离，用于剪枝 
bool visit[MAX]; 
int state;
// i表示当前去过的岛的数量， k表示最后去的岛 
void dfs(int i, int k){
	// 终止状态 
	if(i == n-1){
		t += d[k][n-1];
		if(t < mint) mint = t;
		t -= d[k][n-1];
		return;
	}
	visit[k] = 1;
	for(int j = 0; j < n-1; j++){
		// 遍历所有可达状态 
		if(!visit[j]){ 
			// 状态转移：移动到下一个点，时间增加，state变化 
			t += d[k][j];
			state |= 1<<k;
			if(t < mint && t < dp[state][j]){ // 最优化剪枝 
				dp[state][j] = t;
				dfs(i+1, j);
			}
			state &= ~(1<<k);
			t -= d[k][j];
		}
	}
	visit[k] = 0;
}

int main(){
//	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			scanf("%d", &d[i][j]);
		}
	}
	memset(dp, 0x3f3f3f3f, sizeof dp); 
	dfs(1, 0);
	printf("%d", mint);
	return 0;
}
