#include <bits/stdc++.h>

/*
使用线段树模拟贴海报的过程，贴海报=区间更新，查询某个区间有没有海报=区间查询 
线段树的区间存储该区间是否被全部覆盖(cover)，贴海报后该区间cover=1
还有一个问题是区间范围太大(1<=l<=r<=10000000)，但其实实际海报不超过10000张
可以进行离散化预处理，压缩区间。预处理和线段树的实现是独立的，只不过是对区间进行了一次转换。 
*/

using namespace std;

const int MAX = 10005;

int n;
int ll[MAX];
int rr[MAX];

struct node{
	int l;
	int r;
	bool cover;
	
	int mid(){
		return (l+r) / 2;
	}
	
	bool single(){
		return l == r;
	}
	
	bool is(int a, int b){
		return l == a && r == b;
	}
};
node tree[1000000];

// + 优先级高于 <<
// l << 1 + 1 其实是 l << (1 + 1)，是错的 
inline int L(int l){
	return (l << 1) + 1;
}

inline int R(int r){
	return (r << 1) + 2;
}

void down(int v){
	if(!tree[v].single() && tree[v].cover){
		tree[L(v)].cover = 1;
		tree[R(v)].cover = 1;
	}
}

void up(int v){
	if(tree[L(v)].cover && tree[R(v)].cover)
		tree[v].cover = 1;
}

// 结点v对应的区间为[l,r] 
// build(0, 0, n-1) -> long long a[n];
void build(int v, int l, int r){
	tree[v].l = l;
	tree[v].r = r;
	tree[v].cover = 0;
	if(!tree[v].single()){
		build(L(v), l, (l+r)/2);
		build(R(v), (l+r)/2+1, r);
	}
}

// 根节点v开始查找第i个值，将其设为val
// insert(0, i, val) -> a[i] = val; 
void insert(int v, int l, int r){
	if(tree[v].is(l, r)){
		tree[v].cover = 1;
		return;
	}
	
	int mid = tree[v].mid();
	if(r <= mid){
		insert(L(v), l, r);
	}
	else if(l > mid){
		insert(R(v), l, r);
	}
	else{
		insert(L(v), l, mid);
		insert(R(v), mid+1, r);
	}
	// 子区间值的变化可能引起该区间的变化，因此根据子区间的值更新该区间 
	// 这个更新必须要即时完成，不能延迟到query的时候再做 
	// 因为这个更新要逐层向上传播。爸爸区间不即时更新，爷爷区间的值就会出错 
	up(v);
}

// 状态：(l, r), 0<=l<=r<=n-1 
// 状态值：(cover) 
// 初始：(tree[v].l, tree[v].r)  终止(l, r), l >= tree[v].l, r <= tree[v].r 
bool query(int v, int l, int r){
	// 终止状态 
	if(tree[v].is(l, r)){
		return tree[v].cover;
	}
	
	// 先用该区间的值更新子区间的值，将区间更新时的lazy值下放 
	down(v);
	// 分治查询 
	int mid = tree[v].mid();
	bool res;
	if(r <= mid){
		res = query(L(v), l, r);
	}
	else if(l > mid){
		res = query(R(v), l, r);
	}
	else{
		// 用子区间的值更新该区间 
		res = query(L(v), l, mid) & query(R(v), mid+1, r);
	}
	// 子区间值的变化可能引起该区间的变化，因此根据子区间的值更新该区间 
	up(v);
	return res;
} 

// 用于区间离散化 
set<int> a;
map<int, int> fix;

int discretize(){
	int i = 0;
	int last = 0;
	for(set<int>::iterator it = a.begin(); it != a.end(); it++){
		fix[*it] = i;
		if(*it - last == 1){
			i++;
		}
		else{
			i+=2;
		}
		last = * it;
	}
	return i;
}

// 线段树（区间树）就是把对n个数的操作转化为对logn个区间的操作。比如区间查询、区间更新 
int main(){
//	freopen("in.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			scanf("%d%d", &ll[i], &rr[i]);
			a.insert(ll[i]);
			a.insert(rr[i]); 
		}
		
		// 将区间离散化，把[0,10000000]压缩到[0,40000]，再构建线段树 
		int i = discretize();
		build(0, 0, i + 100);
		
		int res = 0, l, r;
		// 倒着贴海报，贴的时候同时查询出[l,r]是否完全被海报覆盖 
		for(int i = n-1; i >= 0; i--){
			l = fix[ll[i]];
			r = fix[rr[i]];
			bool cover = query(0, l, r);
			if(!cover){
				insert(0, l, r);
				res++;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}

