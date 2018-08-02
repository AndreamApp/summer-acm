// (POJ 3691 (DNA Repair))[http://poj.org/problem?id=3691]
#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;

const int BRANCH = 26;
const int MAX = 260000;
const int inf = 0x3f3f3f3f;

bool visit[MAX];

class TrieMap {
private:
	struct Node {
		Node * childs[BRANCH];
		Node * prev; // 前缀指针 
		int bad; // 危险结点 
	};

	Node tree[MAX]; // N * L <= 250 * 1000 = 250000
	int nodeCount; // 初始化为1，0号结点单独初始化 

public:
	void init() {
		nodeCount = 1;
		memset(tree, 0, sizeof tree);
		memset(visit, 0, sizeof visit);
	}

	inline int hash(char c) {
		return c - 'A';
	}

	// 将模式串插入Trie树中 
	void insertTrieTree(char * dna) {
		Node * root = &tree[0];
		int c;
		for (int i = 0; dna[i]; i++) {
			c = hash(dna[i]);
			if (root->childs[c] == NULL) {
				root->childs[c] = tree + nodeCount;
				nodeCount++;
			}
			root = root->childs[c];
		}
		root->bad = true;
	}

	// 向Trie树中添加前缀指针，构造Trie图：即为所有结点设置合适的prev和bad 
	void buildTrieMap() {
		queue<Node*> q;
		Node * root = &tree[0];
		for (int i = 0; i < BRANCH; i++) {
			if (root->childs[i]) {
				root->childs[i]->prev = root;
				q.push(root->childs[i]);
			}
			else {
				root->childs[i] = root;
			}
		}
		root->prev = NULL;

		while (q.size()) {
			Node * p = q.front(); q.pop();
			for (int i = 0; i < BRANCH; i++) {
				if (p->childs[i]) {
					p->childs[i]->prev = p->prev->childs[i];
					p->childs[i]->bad += p->prev->childs[i]->bad;
					q.push(p->childs[i]);
				}
				else {
					p->childs[i] = p->prev->childs[i];
				}
			}
		}
	}

	int match(char * dna, int begin, int end, int delta) {
		Node * p = &tree[0];
		int res = 0;
		int c;
		for (int i = begin; i != end; i += delta) {
			c = hash(dna[i]);
			while (1) {
				if (p->childs[c]) {
					// 子节点找不到，去前缀指针找 
					//					if(p->childs[c] == tree){
					//						p = p->prev;
					//					}
					// 匹配到一个危险结点 
					if (p->childs[c]->bad) {
						p = p->childs[c];
						if(!visit[p - tree]){
							visit[p - tree] = 1;
							res += p->bad;
						}
						break;
					}
					// 子节点是安全结点 
					else {
						p = p->childs[c];
						break;
					}
				}
				else {
					break;
				}
			}
		}
		return res;
	}

};

int decimal(int n) {
	int cnt = 0;
	while (n) {
		n /= 10;
		cnt++;
	}
	return cnt;
}

TrieMap trie;
char dna[5100050];
char rna[5100050];

int main() {
	int n, m;
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		trie.init();
		for (int i = 0; i < n; i++) {
			scanf("%s", dna);
			trie.insertTrieTree(dna);
		}
		trie.buildTrieMap();
		scanf("%s", dna);
		int i = 0, q;
		char c;
		for (int j = 0; dna[j]; j++) {
			if ('[' == dna[j]) {
				sscanf(dna + j, "[%d%c]", &q, &c);
				j += decimal(q) + 2;
				for (int k = 0; k < q; k++) {
					rna[i] = c;
					i++;
				}
			}
			else {
				rna[i] = dna[j];
				i++;
			}
		}
		printf("%d\n", trie.match(rna, 0, strlen(rna), 1) + trie.match(rna, strlen(rna) - 1, -1, -1));
	}
	return 0;
}

