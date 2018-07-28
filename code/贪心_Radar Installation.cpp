// http://icpcsummer.openjudge.cn/2018hw1/06/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>

using namespace std;

const int MAX = 1005;

struct seg{
	double a, b;
	bool operator<(const seg & r) const{
		if(a == r.a) return b < r.b;
		return a < r.a;
	}
};

seg s[MAX];

int main(){
	int n, d, t = 0;
	while(~scanf("%d%d", &n, &d) && n && d){
		int cnt = 1;
		int x, y;
		for(int i = 0; i < n; i++){
			scanf("%d%d", &x, &y);
			if(y > d) cnt = -1;
			if(cnt != -1){
				double m = sqrt(d*d - y*y);
				s[i].a = x - m;
				s[i].b = x + m;
			}
		}
		
		if(cnt != -1){
			sort(s, s+n);
			
			double minb = s[0].b;
			for(int i = 1; i < n; i++){
				if(s[i].a > minb){
					cnt++;
					minb = s[i+1].b;
				}
				if(s[i].b < minb) minb = s[i].b;
			}
		}
		printf("Case %d: %d\n", ++t, cnt);
	}
	return 0;
}
