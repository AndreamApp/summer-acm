#include <bits/stdc++.h>

using namespace std;

const int MAX = 1005;
const int inf = 0x3f3f3f3f;

int n;
int t;

struct Edge{
	int v;
	int w;
};

int G[MAX][MAX];

int d[MAX];
bool T[MAX];
int next_i(){
	int id = 0;
	int val = inf;
	for(int i = 1; i <= n; i++){
		// 不在T中的最近结点 
		if(!T[i] && d[i] < val){
			val = d[i];
			id = i;
		}
	}
	T[id] = 1;
	return id;
}

// 前提：求单源路径，不能有负权边 
// 起点为1，求1到所有点的距离。答案为d[n] 
int dijkstra(int s){
	for(int i = 1; i <= n; i++){
		d[i] = s == i ? 0 : inf;
	}
	for(int i = 1; i <= n; i++){
		// 找到下一个不在T中的最近结点 
		int id = next_i();
		// if(id == 0) break; 不必要，因为这个循环总要执行n次 
		// 更新所有id相邻，且不在T中的结点距离 
		for(int j = 1; j <= n; j++){
			if(!T[j] && G[id][j]){
				d[j] = min(d[j], d[id] + G[id][j]);
			}
		}
	}
	return d[n];
}

int main(){
	// 为了配合判重边，一开始设为无穷大 
	memset(G, inf, sizeof G);
	scanf("%d%d", &t, &n);
	int u, v, w;
	for(int i = 0; i < t; i++){
		scanf("%d%d%d", &u, &v, &w);
		// 重边取最短边 
		if(w < G[u][v]){
			G[u][v] = w;
			G[v][u] = w;
		}
	}
	printf("%d", dijkstra(1));
	return 0; 
} 
