// http://icpcsummer.openjudge.cn/2018hw1/22/
#include <bits/stdc++.h>

using namespace std;

const int MAX = 105;

int A, B, C;

bool flag[MAX][MAX];

struct state{
	int a; // A罐中的水 
	int b; // B罐中的水 
	vector<int> steps; // 路径 
	state(state & s, int op){
		a = s.a;
		b = s.b;
		steps = s.steps;
		steps.push_back(op);
		int x;
		switch(op){
			case 1:
				a = A;
				break;
			case 2:
				b = B;
				break;
			case 3:
				a = 0;
				break;
			case 4:
				b = 0;
				break;
			case 5:
				x = min(a, B-b);
				a -= x;
				b += x;
				break;
			case 6:
				x = min(b, A-a);
				a += x;
				b -= x;
				break;
		}
		flag[a][b] = 1;
	}
	state(int aa, int bb){
		a = aa;
		b = bb;
	}
};
/*
 状态：state(a, b, steps), 0<=a<=A, 0<=b<=B (flag用于状态判重)
 转移：(a, b, steps) -> (A, b, steps+1), a < A, flag[A][b] = 0
       (a, b, steps) -> (a, B, steps+2), b < B, flag[a][B] = 0
       (a, b, steps) -> (0, b, steps+3), a > 0, flag[0][b] = 0
       (a, b, steps) -> (a, 0, steps+4), b > 0, flag[a][0] = 0
       (a, b, steps) -> (a-x, b+x, steps+5), a > 0, b < B, flag[a-x][b+x] = 0, 其中x = min(a,B-b) 
       (a, b, steps) -> (a+x, b-x, steps+6), b > 0, a < A, flag[a+x][b-x] = 0, 其中x = min(b,A-a) 
 初始：(0, 0, [])
 终止：(C, b, steps) or (a, C, steps), steps即为答案 
*/
vector<int> res;
bool bfs(){
	queue<state> q;
	q.push(state(0, 0));
	flag[0][0] = 1;
	while(q.size()){
		state s = q.front(); q.pop();
		if(s.a == C or s.b == C){
			res = s.steps;
			return 1;
		}
		int a = s.a, b = s.b;
		if(a < A && flag[A][b] == 0){
			q.push(state(s, 1));
		}
		if(b < B && flag[a][B] == 0){
			q.push(state(s, 2));
		}
		if(a > 0 && flag[0][b] == 0){
			q.push(state(s, 3));
		}
		if(b > 0 && flag[a][0] == 0){
			q.push(state(s, 4));
		}
		int x = min(a, B-b);
		if(a > 0 && b < B && flag[a-x][b+x] == 0){
			q.push(state(s, 5));
		}
		x = min(b, A-a);
		if(b > 0 && a < A && flag[a+x][b-x] == 0){
			q.push(state(s, 6));
		}
	}
	return 0;
}

int main(){
//	freopen("in.txt", "r", stdin);
	scanf("%d%d%d", &A, &B, &C);
	
	if(!bfs()){
		printf("impossible");
		return 0;
	}
	int S = res.size();
	printf("%d\n", S);
	for(int i = 0; i < S; i++){
		switch(res[i]){
			case 1:
				printf("FILL(1)\n");
				break;
			case 2:
				printf("FILL(2)\n");
				break;
			case 3:
				printf("DROP(1)\n");
				break;
			case 4:
				printf("DROP(2)\n");
				break;
			case 5:
				printf("POUR(1,2)\n");
				break;
			case 6:
				printf("POUR(2,1)\n");
				break;
		}
	}
	return 0;
}
