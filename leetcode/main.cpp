#include <cstdio>
#include "T4.cpp"

int main() {
	Solution x;
	vector<int> A{1, 3};
	vector<int> B{ 2, 4};
	printf("%f\n", x.findMedianSortedArrays(A, B));
}