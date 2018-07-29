#include <bits/stdc++.h>
#include <set>

/*
使用线段树模拟贴海报的过程，贴海报=区间更新，查询某个区间有没有海报=区间查询 
线段树的区间存储该区间是否被全部覆盖(cover)，贴海报后该区间cover=1
还有一个问题是区间范围太大(1<=l<=r<=10000000)，但其实实际海报不超过10000张
可以进行离散化预处理，压缩区间。预处理和线段树的实现是独立的，只不过是对区间进行了一次转换。 
*/

using namespace std;

const int MAX = 100005;

int n;
int ll[MAX];
int rr[MAX];
int discreteArr[MAX<<2];

set<int> a;
map<int, int> fix;
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
node tree[MAX*15+1];

void sync(int v){
	if(!tree[v].single() && tree[v].cover){
		tree[L(v)].cover = 1;
		tree[R(v)].cover = 1;
	}
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
	if(l == tree[v].l && r == tree[v].r){
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
}

// 状态：(l, r), 0<=l<=r<=n-1 
// 状态值：(sum, lazy) 
// 初始：(tree[v].l, tree[v].r)  终止(l, r), l >= tree[v].l, r <= tree[v].r 
bool query(int v, int l, int r){
	// 终止状态 
	if(l == tree[v].l && r == tree[v].r){
		sync(v);
		return tree[v].cover;
	}
	
	// 查询的时候再同步lazy 
	sync(v);
	
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
	tree[v].cover = tree[L(v)].cover & tree[R(v)].cover;
	return res;
} 

int input(){
	int disN = 1;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &ll[i], &rr[i]);
		discreteArr[disN++] = ll[i];
		discreteArr[disN++] = rr[i];
	}
	sort(discreteArr+1, discreteArr+disN);

	int j = 2;
	for (int i = 2; i < disN; i++)
	{
		if (discreteArr[i] != discreteArr[i-1]) 
			discreteArr[j++] = discreteArr[i];
	}
	for (int i = j-1; i > 1; i--)
	{
		if (discreteArr[i] != discreteArr[i-1] + 1)
			discreteArr[j++] = discreteArr[i-1] + 1;
	}
	sort(discreteArr + 1, discreteArr + j);
	return j;
}

int biSearch(int arr[], int key, int n)
{
	int l = 1, r = n-1, m = -1;
	while (l <= r)
	{
		m = l + ((r-l)>>1);
		if (arr[m] < key) l = m+1;
		else if (key < arr[m]) r = m-1;
		else break;
	}
	return m;
}

// 线段树（区间树）就是把对n个数的操作转化为对logn个区间的操作。比如区间查询、区间更新 
int main(){
//	freopen("in.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
//		for(int i = 0; i < n; i++){
//			scanf("%d%d", &ll[i], &rr[i]);
//			a.insert(ll[i]);
//			a.insert(rr[i]); 
//		}
//		
//		int i = 0;
//		for(set<int>::iterator it = a.begin(); it != a.end(); it++){
//			fix[*it] = i;
//			i++;
//		}
//		printf("n=%d\n", a.size());
		int j = input();
		build(0, 0, j + 100);
		
		int res = 0, l, r;
		for(int i = n-1; i >= 0; i--){
//			l = fix[ll[i]];
//			r = fix[rr[i]];
			int ql = biSearch(discreteArr, ll[i], j);
			int qr = biSearch(discreteArr, rr[i], j);
			bool cover = query(0, ql, qr);
//			printf("[%d, %d] cover=%d\n", l, r, cover);
			if(!cover){
				insert(0, ql, qr);
				res++;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}

