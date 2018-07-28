// http://icpcsummer.openjudge.cn/2018hw1/02/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX = 50005;

int L, N, M;
int lt[MAX];
int rt[MAX];

struct stone{
	int id;
	bool operator<(const stone & s) const{
		if(lt[id] == lt[s.id]) return rt[id] < rt[s.id];
		return lt[id] < lt[s.id];
	}
};
priority_queue<stone> q;

int main(){
	scanf("%d%d%d", &L, &N, &M);
	int t1 = 0, t2;
	for(int i = 0; i < N; i++){
		scanf("%d", &t2);
		lt[i] = t2 - t1;
		if(i > 0){
			rt[i - 1] = lt[i];
		}
		t1 = t2;
	}
	rt[N-1] = L - t1;
	for(int i = 0; i < N; i++){
		q.push(stone{i});
		printf("left %d right %d\n", lt[i], rt[i]);
	}
	
	int cnt = N;
	while(M--){
		stone s = q.top();
		q.pop();
		if(s.id > 0){
			rt[s.id-1] += rt[s.id];
		}
		if(s.id < cnt){
			lt[s.id+1] += lt[s.id];
		}
		//lt[s.id] = rt[s.id] = -1;
		cnt--;
		printf("pop %d\n", s.id);
	}
	
	int res = 2000000000;
	for(int i = 0; i < N; i++){
		if(lt[i] != -1 && lt[i] < res) res = lt[i];
		if(rt[i] != -1 && rt[i] < res) res = rt[i];
	}
	
	printf("%d", res);
	
	return 0;
}

