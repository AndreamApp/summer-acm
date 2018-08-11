// http://icpcsummer.openjudge.cn/2018hw1/08/
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int n, k;
int a[100005];

void arrange(int I, int J, int k){
	int key = a[I];
	int i = I, j = J;
	while(i < j){
		while(a[j] > key) j--;
		while(a[i] < key) i++;
		if(i < j) swap(a[i], a[j]);
	}
	if(J - j < k){
		arrange(I, j, k - (J-j));
	}
	else if(J - j > k){
		arrange(j+1, J, k);
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	scanf("%d", &k);
	
	arrange(0, n-1, k);
	sort(&a[n-k], &a[n]);
	
	for(int i = n-1; i >= n-k; i--){
		printf("%d\n", a[i]);
	}
	
	return 0;
}

