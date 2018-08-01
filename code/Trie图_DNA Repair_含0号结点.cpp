#include <bits/stdc++.h>

using namespace std;


const int BRANCH = 4;
const int inf = 0x3f3f3f3f;

struct Node{
	Node * childs[BRANCH];
	Node * prev; // 前缀指针 
	bool bad; // 危险结点 
	int level; // 用于广搜的时候dp 
};

Node tree[2000]; // N * L <= 50 * 20 = 1000
int nodeCount; // 初始化为2，0号结点和1号结点单独初始化 

/*
 状态：dp[i][j]表示母串长度为i的前缀，遍历到达节点j（安全节点），需要修改的最少次数
       0<=i<=len(str), 1<=j<nodeCount，min(dp[len][j])就是答案 
 条件：dp[0][1] = 0; 表示母串长度为0的前缀只需修改0次就能到达1号结点（根节点）
       其他的dp[i][j] = inf; 
 转移：dp[i+1][son(j)] = min(dp[i+1][son(j)], dp[i][j] + Char(j, son(j)) != str[i]) 
       Char(j, son(j)) != str[i] 表示母串的第i+1个字符是否和j到达son(j)所需的字符相同，即母串是否需要再修改一个字符才能到达son(j) 
*/
int dp[200][2000];

inline int hash(char c){
	return 'A' == c ? 0
		: 'G' == c ? 1
		: 'C' == c ? 2
		: 3;
//	return c - 'a';
}

// 将模式串插入Trie树中 
void insertTrieTree(char * dna){
	Node * root = &tree[1];
	int c;
	for(int i = 0; dna[i]; i++){
		c = hash(dna[i]);
		if(root->childs[c] == NULL){
			root->childs[c] =  tree + nodeCount;
			nodeCount++;
		}
		root = root->childs[c];
	}
	root->bad = true;
}

// 向Trie树中添加前缀指针，构造Trie图：即为所有结点设置合适的prev和bad 
void buildTrieMap(){
	for(int i = 0; i < BRANCH; i++){
		tree[0].childs[i] = &tree[1];
	}
	tree[0].prev = NULL;
	tree[1].prev = &tree[0];
	
	// 广搜依次建立前缀指针 
	deque<Node*> q;
	tree[1].level = 0;
	q.push_back(&tree[1]);
	while(q.size()){
		Node * root = q.front(); q.pop_front();
		// 对于每一个子节点 
		for(int i = 0; i < BRANCH; i++){
			Node * child = root->childs[i];
			if(child){
				// 沿着父节点的前缀结点 
				Node * prev = root->prev;
				while(prev){
					if(prev->childs[i]){ // 匹配相同后缀 
						child->prev = prev->childs[i];
						if(child->prev->bad) child->bad = true; // 危险结点 
						break;
					}
					prev = prev->prev;
				}
				// 加入队列，从上层到下层构造前缀指针
				q.push_back(child);
			}
		}
	}
}

int searchPattern(char * dna){
	memset(dp, inf, sizeof dp);
	dp[0][1] = 0;
	
	for(int i = 0; dna[i]; i++){
		int c = hash(dna[i]);
		for(int j = 1; j < nodeCount; j++){
			Node * p = &tree[j];
			bool safe = false;
			while(p){
				if(p - tree == 0){
					dp[i+1][1] = min(dp[i+1][1], dp[i][j] + 1);
					if(!safe) return -1;
				}
				else{
					// j结点的直接子节点 
					for(int k = 0; k < BRANCH; k++){
						if(p->childs[k]){
							if(!p->childs[k]->bad){
								int sonj = p->childs[k] - tree;
								dp[i+1][sonj] = min(dp[i+1][sonj], dp[i][j] + (c != k));
								safe = true;
							}
						}
					}
				}
				// j结点前缀结点的子节点
				p = p->prev;
			}
		}
	}
	
	int len = strlen(dna);
	
//	for(int i = 0; i <= len; i++){
//		for(int j = 1; j < nodeCount; j++){
//			printf("%d ", dp[i][j] == inf ? -1 : dp[i][j]);
//		}
//		printf("\n");
//	}
	int ans = inf;
	for(int i = 1; i < nodeCount; i++){
		ans = min(ans, dp[len][i]);
	}
	if(ans == inf) ans = -1;
	return ans;
}

/*
从ROOT出发，按照当前串的下一
个字符ch来进行在树上的移动。若当前点P不存在通过ch
连接的儿子，那么考虑P的前缀指针指向的节点Q，如果还
无法找到通过ch连接的儿子节点，再考虑Q的前缀指针…
直到找到通过ch连接的儿子，再继续遍历。

如果遍历过程中经过了某个终止节点，则说明S包含该终
止节点代表的模式串.

如果遍历过程中经过了某个非终止节点的危险节点，
则可以断定S包含某个模式串。要找出是哪个，沿着危险
节点的前缀指针链走，碰到终止节点即可。
*/
bool match(char * dna){
	Node * p = &tree[1];
	int c;
	for(int i = 0; dna[i]; i++){
		c = hash(dna[i]);
		while(1){
			if(p->childs[c]){
				p = p->childs[c];
				if(p->bad) return true;
				break;
			}
			else{
				p = p->prev;
			}
		}
	}
	return false;
}

int main(){
	int n, m;
	char dna[1005];
	int t = 0;
	while(~scanf("%d", &n) && n){
		nodeCount = 2;
		memset(tree, 0, sizeof tree);
		for(int i = 0; i < n; i++){
			scanf("%s", dna);
			insertTrieTree(dna);
		}
		buildTrieMap();
		scanf("%s", dna);
		printf("Case %d: %d\n", ++t, searchPattern(dna));
	}
	return 0;
}

