#include <bits/stdc++.h>

using namespace std;

const int MAX = 30005;
const int inf = 0x3f3f3f3f;

int n;
int m;

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
bool used[MAX];

// 前提：求单源路径，不能有负权边 
// 起点为1，求1到所有点的距离。答案为d[n] 
int dijkstra(int s){
	for(int i = 1; i <= n; i++){
		d[i] = s == i ? 0 : inf;
	}
	Point p = Point(s, 0);
	priority_queue<Point> q;
	q.push(p);
	while(q.size()){
		// 找到下一个不在T中的*最近*结点
		// 优先队列保证了最近 
		do{
			p = q.top(); q.pop();
		} while(used[p.v] && q.size());
		int u = p.v;
		if(!used[u]) {
			used[u] = 1;
			// 更新所有id相邻，且不在T中的结点距离 
			for(int j = 0; j < G[u].size(); j++){
				int v = G[u][j].v;
				if(!used[v]){
					if(d[v] > d[u] + G[u][j].w){
						d[v] = d[u] + G[u][j].w;
						q.push(Point(v, d[v])); // 更新的同时加入队列，保证最近的结点能被找到 
					}
				}
			}
		}
	}
	return d[n];
}

int main(){
	scanf("%d%d", &n, &m);
	int u, v, w;
	for(int i = 0; i < m; i++){
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(Edge{v, w});
	}
	printf("%d", dijkstra(1));
	return 0; 
} 
