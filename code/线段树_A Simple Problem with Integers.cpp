#include <bits/stdc++.h>

using namespace std;

const int MAX = 100005;

int n, q;

// + 优先级高于 <<
// l << 1 + 1 其实是 l << (1 + 1)，是错的 
inline int L(int l){
	return (l << 1) + 1;
}

inline int R(int r){
	return (r << 1) + 2;
}

struct node{
	int l;
	int r;
	long long sum;
	long long lazy;
	
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
node tree[MAX*3+1];

void sync(int v){
	tree[v].sum += tree[v].lazy * (tree[v].r-tree[v].l+1);
	if(!tree[v].single()){
		tree[L(v)].lazy += tree[v].lazy;
		tree[R(v)].lazy += tree[v].lazy;
	}
	tree[v].lazy = 0;
}

// 结点v对应的区间为[l,r] 
// build(0, 0, n-1) -> long long a[n];
void build(int v, int l, int r){
	tree[v].l = l;
	tree[v].r = r;
	tree[v].sum = 0;
	tree[v].lazy = 0;
	if(!tree[v].single()){
		build(L(v), l, (l+r)/2);
		build(R(v), (l+r)/2+1, r);
	}
}

// 根节点v开始查找第i个值，将其设为val
// insert(0, i, val) -> a[i] = val; 
void insert(int v, int i, long long val){
	if(tree[v].is(i, i)){
		tree[v].sum = val;
		return;
	}
	
	tree[v].sum += val;
	
	if(i <= tree[v].mid()){
		insert(L(v), i, val);
	}
	else{
		insert(R(v), i, val);
	}
}

// a[i:j] += val;
// 更新归根结底也还是查询
// 对n个数进行更新，但最后实际上只是更新了查询出来的logn个分解区间
// 不过是把logn个区间查询出来，然后把lazy值加上val 
// 这种lazy的想法很常见，比如虚拟内存的lazy page fault 
void add(int v, int l, int r, long long val){
	if(tree[v].is(l, r)){ // [l, r] = [tree[v].l, tree[v].r]
		tree[v].lazy += val;
		return;
	}
	
	tree[v].sum += val * (r-l+1); //!  [l, r] 是 [tree[v].l, tree[v].r]的真子集
	
	int mid = tree[v].mid();
	if(r <= mid){
		add(L(v), l, r, val);
	}
	else if(l > mid){
		add(R(v), l, r, val);
	}
	else{
		add(L(v), l, mid, val);
		add(R(v), mid+1, r, val);
	}
}

// 状态：(l, r), 0<=l<=r<=n-1 
// 状态值：(sum, lazy) 
// 初始：(tree[v].l, tree[v].r)  终止(l, r), l >= tree[v].l, r <= tree[v].r 
long long query(int v, int l, int r){
	// 终止状态 
	if(tree[v].is(l, r)){
		sync(v);
		return tree[v].sum;
	}
	
	// 查询的时候再同步lazy 
	sync(v);
	
	// 分治查询 
	int mid = tree[v].mid();
	if(r <= mid){
		return query(L(v), l, r);
	}
	else if(l > mid){
		return query(R(v), l, r);
	}
	else{
		return query(L(v), l, mid) + query(R(v), mid+1, r);
	}
} 


// 线段树（区间树）就是把对n个数的操作转化为对logn个区间的操作。比如区间查询、区间更新 
int main(){
	freopen("in.txt", "r", stdin);
	long long val;
	scanf("%d%d", &n, &q);
	build(0, 0, n-1);
	for(int i = 0; i < n; i++){
		scanf("%lld", &val);
		insert(0, i, val);
	}
	char cmd[2];
	int a, b;
	long long c;
	for(int i = 0; i < q; i++){
		scanf("%s%d%d", cmd, &a, &b);
		if('C' == cmd[0]){
			scanf("%lld", &c);
			add(0, a-1, b-1, c);
		}
		else{
			long long res = query(0, a-1, b-1);
			printf("%lld\n", res);
		}
	}
	return 0;
}

