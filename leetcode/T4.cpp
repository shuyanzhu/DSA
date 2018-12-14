#include <vector>
#include <algorithm>
using namespace std;


class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int m = nums1.size(); int n = nums2.size();
		int lo = 0, hi = min(n, m);
		while (1 < hi - lo) {
			int i = (lo + hi) >> 1;
			int j = (m + n) / 2 - i;
			if (nums1[i - 1] <= nums2[j])  lo = i; 
			else { hi = i; continue; }
		}
		int j = (m + n) / 2 - lo;;
		if ((m + n) % 2 == 0)
			return (min(nums1[lo - 1], nums2[j - 1]) + max(nums1[lo], nums2[j])) / 2.0;
		else
			return min(nums1[lo], nums2[j]);
	}
};