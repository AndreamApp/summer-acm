// (POJ 3691 (DNA Repair))[http://poj.org/problem?id=3691]
#include <queue>
#include <cstring>
#include <cstdio>

using namespace std;

const int BRANCH = 4;
const int MAX = 1005;
const int inf = 0x3f3f3f3f;

class TrieMap{
private:
	struct Node{
		Node * childs[BRANCH];
		Node * prev; // 前缀指针 
		bool bad; // 危险结点 
	};
	
	Node tree[MAX]; // N * L <= 50 * 20 = 1000
	int nodeCount; // 初始化为1，0号结点单独初始化 
	
	/*
	 状态：dp[i][j]表示母串长度为i的前缀，遍历到达节点j（安全节点），需要修改的最少次数。如果j是危险结点，那dp[i][j]就是无穷大 
	       0<=i<=len(str), 0<=j<nodeCount，min(dp[len][j])就是答案 
	 条件：dp[0][0] = 0; 表示母串长度为0的前缀只需修改0次就能到达0号结点（根节点）
	       其他的dp[i][j] = inf; 
	 转移：dp[i+1][son(j)] = min(dp[i+1][son(j)], dp[i][j] + Char(j, son(j)) != str[i]) 
	       son(j)是j结点可达的安全子节点 
	       Char(j, son(j)) != str[i] 表示母串的第i+1个字符是否和j到达son(j)所需的字符相同
		   即母串是否需要再修改一个字符才能到达son(j) 
	*/
	int dp[MAX][MAX];
	
	int hash[256];
	
public:
	void init(){
		nodeCount = 1;
		memset(tree, 0, sizeof tree);
		hash['A'] = 0; hash['G'] = 1;
		hash['C'] = 2; hash['T'] = 3;
	}
	
	//inline int hash(char c){
	//	return 'A' == c ? 0
	//		: 'G' == c ? 1
	//		: 'C' == c ? 2
	//		: 3;
	//}
	
	// 将模式串插入Trie树中 
	void insertTrieTree(char * dna){
		Node * root = &tree[0];
		int c;
		for(int i = 0; dna[i]; i++){
			c = hash[dna[i]];
			if(root->childs[c] == NULL){
				root->childs[c] = tree + nodeCount;
				nodeCount++;
			}
			root = root->childs[c];
		}
		root->bad = true;
	}
	
	// 向Trie树中添加前缀指针，构造Trie图：即为所有结点设置合适的prev和bad 
	void buildTrieMap(){
		queue<Node*> q;
		Node * root = &tree[0];
		for(int i = 0; i < BRANCH; i++){
			if(root->childs[i]){
				root->childs[i]->prev = root;
				q.push(root->childs[i]);
			}
			else{
				root->childs[i] = root;
			}
		}
		root->prev = NULL;
		
		while(q.size()){
			Node * p = q.front(); q.pop();
			for(int i = 0; i < BRANCH; i++){
				if(p->childs[i]){
					p->childs[i]->prev = p->prev->childs[i];
					p->childs[i]->bad |= p->prev->childs[i]->bad;
					q.push(p->childs[i]);
				}
				else{
					p->childs[i] = p->prev->childs[i];
				}
			}
		}
	}
	
	int minimumModify(char * dna){
		memset(dp, inf, sizeof dp);
		dp[0][0] = 0;
		
		int now = 0, pre = 1;
		// 母串的前i个字符 
		for(int i = 0; dna[i]; i++){
			now ^= 1, pre ^= 1;
			memset(dp[now], inf, sizeof dp[now]); // 滚动数组必备 
			int c = hash[dna[i]];
			// 到达安全结点j 
			for(int j = 0; j < nodeCount; j++){
				if(dp[pre][j] == inf) continue; // 母串i不可达结点j -> 母串i+1不可达sonj 
				Node * p = &tree[j];
				// 最少修改次数dp[i+1][sonj] = min(dp[i][j] + (c != k));
				// “我为人人”型动规 
				for(int k = 0; k < BRANCH; k++){
					if(!p->childs[k]->bad){
						int sonj = p->childs[k] - tree;
						dp[now][sonj] = min(dp[now][sonj], dp[pre][j] + (c != k));
					}
				}
			}
		}
		// min(dp[len][j]) 即为答案 
		int ans = inf;
		for(int j = 0; j < nodeCount; j++){
			ans = min(ans, dp[now][j]);
		}
		if(ans == inf) ans = -1;
		return ans;
	}

};

TrieMap trie;
char dna[1005];

int main(){
	int n, m;
	int t = 0;
	while(~scanf("%d", &n) && n){
		trie.init();
		for(int i = 0; i < n; i++){
			scanf("%s", dna);
			trie.insertTrieTree(dna);
		}
		trie.buildTrieMap();
		scanf("%s", dna);
		printf("Case %d: %d\n", ++t, trie.minimumModify(dna));
	}
	return 0;
}

