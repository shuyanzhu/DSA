#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>


typedef int Rank;
void merge(int *p, Rank lo, Rank mi, Rank hi){
	int *B = new int[mi-lo];
	for(int i=0;i<mi-lo;i++)B[i]=p[lo+i];
	for(int i=0,j=0,k=0;i<mi-lo||j<hi-mi;){//判断归并是否结束，底下两行交替判断是否入栈
		if ( (i<mi - lo) && (!(j<hi - mi) || (B[i] <= p[mi + j] )))p[lo + k++] = B[i++];
		if( (j<hi-mi) && (!(i<mi-lo)||( p[mi+j] < B[i] )))p[lo+k++]=p[mi+j++];
	}
	delete []B;
}
void mergeSort(int *p, Rank lo, Rank hi){
	if(hi-lo<2)return;
	else{
		int mi = (lo+hi)>>1;
		mergeSort(p, lo, mi);
		mergeSort(p, mi, hi);
		merge(p, lo, mi, hi);
	}
}
Rank binarySearch(int *p, Rank lo, Rank hi, int e){
	while(lo<hi){
		Rank mi = (lo+hi)>>1;//
		(e<p[mi])?(hi=mi):(lo=mi+1);
	}
	return --lo;
}

int main(){
	int n = 0, m = 0,nn;
	scanf("%d%d", &n, &m);
	int * p = new int[n]; 
	nn = n;
	while (nn--)scanf("%d", &p[nn]);
	mergeSort(p, 0, n);
	//std::sort(p, p + n);

	int query[2];
	for (int i = 0; i < m; i++) {
		int cnt = 0, lo = 0, hi = 0;
		scanf("%d%d", &query[0], &query[1]);
		hi = binarySearch(p, 0, n, query[1]);
		lo = binarySearch(p, 0, n, query[0]);
		cnt = hi - lo;
		if(lo>=0&&p[lo] == query[0])cnt++;
		printf("%d\n", cnt);
	}
	delete[] p;
    return 0;
}

