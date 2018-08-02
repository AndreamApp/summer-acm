// http://icpcsummer.openjudge.cn/2018hw1/26/
#include <bits/stdc++.h>
#include <map>
#include <cctype>

using namespace std;

const int MAX = 100005;
const int inf = 0x3f3f3f3f;

struct state{
	string s;
	char op2;
	char op3;
	int step;
};

int res[MAX];
int dp[MAX][4][3];

void tryPush(queue<state> & q, state s){
	int num = atoi(s.s.c_str());
	if(s.step < dp[num][s.op2][s.op3]){
		res[num] = min(res[num], s.step);
		dp[num][s.op2][s.op3] = s.step;
		q.push(s);
	}
} 

void bfs(string s, char op2, char op3){
	queue<state> q;
	tryPush(q, state{s, op2, op3, 0}); 
	
	while(q.size()){
		state st = q.front(); q.pop();
		for(int i = 0; i < 4; i++){
			state ns = st;
			swap(ns.s[i], ns.s[i+1]);
			ns.step++;
			tryPush(q, ns);
		}
		if(st.op2 > 0){
			for(int i = 0; i < 5; i++){
				state ns = st;
				ns.s[i] = ((ns.s[i] - '0') + 1) % 10 + '0';
				ns.op2--;
				ns.step++;
				tryPush(q, ns);
			}
		}
		if(st.op3 > 0){
			for(int i = 0; i < 5; i++){
				state ns = st;
				ns.s[i] = ((ns.s[i] - '0') * 2) % 10 + '0';
				ns.op3--;
				ns.step++;
				tryPush(q, ns);
			}
		}
	}
}

int main(){
	memset(dp, inf, sizeof dp);
	memset(res, inf, sizeof res);
	bfs("12345", 3, 2);
	int x;
	while(~scanf("%d", &x)){
		printf("%d\n", res[x] == inf ? -1 : res[x]);
	}
	return 0;
}
