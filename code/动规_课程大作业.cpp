#include <bits/stdc++.h>

using namespace std;

struct homework{
	char name[51];
	int d; // deadline
	int c; // 完成所需时间 
};

// Q: 如果只需要计算最低扣分，哪些状态值是必要的？
// Q: 为什么要添加其他状态值，有什么用？ 
struct state{
	int score; // 完成该状态中所有作业后的分数 
	int finishDay; // 完成该状态中所有作业的时间 
	int pre; // 达到该状态的上一个状态 
	int last; // 达到该状态完成的最后一项作业 
};

const int inf = 1 << 30;

int N;
homework h[17];
state dp[1<<15];

// 借助pre和last，获取到完成某个状态的路径 
vector<int> getPath(int state){
	vector<int> path;
	while(state != 0){
		path.push_back(dp[state].last);
		state = dp[state].pre;
	}
	reverse(path.begin(), path.end());
	return path; 
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &N);
		for(int i = 0; i < N; i++){
			scanf("%s%d%d", h[i].name, &h[i].d, &h[i].c);
		}
		
		dp[0].score = 0;
		dp[0].finishDay = 0;
		int n = 1 << N;
		for(int i = 1; i < n; i++){ // 求解dp[i]
			dp[i].score = inf;
			for(int k = 0; k < N; k++){ 
				if(i & (1 << k)){
					int pre = i & ~(1<<k); // Q: i & ~(1<<k) 的含义是什么？ 
					int finish = dp[pre].finishDay + h[k].c;
					int score = max(finish - h[k].d, 0) + dp[pre].score;
					// 当前状态分数更小
					if(score < dp[i].score){  
						dp[i] = state{score, finish, pre, k};
					}
					// 当前状态虽然分数相同，但是字典序更小 
					else if(score == dp[i].score && getPath(pre) < getPath(dp[i].pre)){ 
						dp[i] = state{score, finish, pre, k};
					}
				}
			}
		}
		
		vector<int> path = getPath(n-1);
		printf("%d\n", dp[n-1].score);
		int S = path.size();
		for(int i = 0; i < S; i++){
			printf("%s\n", h[path[i]].name);
		}
	}
	return 0;
} 

