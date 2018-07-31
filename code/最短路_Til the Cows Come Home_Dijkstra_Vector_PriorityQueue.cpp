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

struct Point{
	int v;
	int dis;
	bool operator<(const Point & d) const{
		return dis > d.dis;
	}
	Point(int V, int Dis) : v(V), dis(Dis){
	}
};

vector<Edge> G[MAX];

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
	priority_queue<Point> q;
	q.push(Point(s, 0));
	while(q.size()){
		// 找到下一个不在T中的*最近*结点
		// 优先队列保证了最近 
		Point p = q.top(); q.pop();
		int u = p.v;
		if(T[u]) continue;
		T[u] = 1;
		// 更新所有id相邻，且不在T中的结点距离 
		for(int j = 0; j < G[id].size(); j++){
			int v = G[id][j].v;
			if(!T[v]){
				if(d[v] > d[u] + G[u][j].w){
					d[v] = d[u] + G[u][j].w;
					q.push(Point(v, d[v])); // 更新的同时加入队列，保证最近的结点能被找到 
				}
			}
		}
	}
	return d[n];
}

int main(){
	scanf("%d%d", &t, &n);
	int u, v, w;
	for(int i = 0; i < t; i++){
		scanf("%d%d%d", &u, &v, &w);
		// 使用邻接矩阵则不需判重边，在计算时自然会考虑所有重边 
		G[u].push_back(Edge{v, w});
		G[v].push_back(Edge{u, w});
	}
	printf("%d", dijkstra(1));
	return 0; 
} 
