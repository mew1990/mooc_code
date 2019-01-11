/***
描述
数轴上有n个点，对于任一闭区间 [a, b]，试计算落在其内的点数。

输入
第一行包括两个整数：点的总数n，查询的次数m。

第二行包含n个数，为各个点的坐标。

以下m行，各包含两个整数：查询区间的左、右边界a和b。

输出
对每次查询，输出落在闭区间[a, b]内点的个数。
***/

#include<cstdio>
using namespace std;

void print(int *s, int p, int n) {
	for (int i = 0; i < n; ++i) {
		printf("%d ", s[p + i]);
	}
	printf("\n");
}

void merge_sort(int *s, int p, int n){
	if (n < 2) return;
	int mi = n >> 1;
	int *temp = new int[mi];
	for (int i = 0; i < mi; ++i) {
		temp[i] = s[p+i];
	}
	merge_sort(temp, 0, mi);
	merge_sort(s, p+mi, n-mi);
	int i = 0, j = p+mi, t = p;
	while (i < mi) {  // till temp[] is empty.
		s[t++] = (j == p + n || temp[i] < s[j]) ? temp[i++] : s[j++];
	}
	delete [] temp;
}

int bin_search(int *s, int tar, int lo, int hi) { 
	while (lo < hi) {
		int mi = (lo + hi) >> 1;
		(tar < s[mi]) ? hi = mi : lo = mi + 1;
	}
	return --lo;  // return the index: s[index] <= tar < s[index + 1]
}

int main() {
	int n, m, a, b;
	scanf("%d %d", &n, &m);
	// n = 10; m = 2;
	int *s = new int[n];
	for (int i = 0; i < n; scanf("%d", &s[i++]));
	// for (int i = 0; i < n; s[i++] = 100 - i*2);
	merge_sort(s, 0, n);
	// print(s, 0, 10);
	for (int i = 0; i < m; ++i) {
		scanf("%d %d", &a, &b);
		printf("%d\n", bin_search(s, b, 0, n) - bin_search(s, a-1, 0, n));  // interval[a,b] ==> (,b] - (,a-1]
	}
	delete[] s;
	return 0;
}