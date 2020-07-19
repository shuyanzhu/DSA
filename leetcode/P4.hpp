#pragma once
#include <vector>
#include <algorithm>

class Solution4 {
public:
	double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
		int m = nums1.size(); int n = nums2.size();
		int lo = 0, hi = std::min(n, m);
		while (1 < hi - lo) {
			int i = (lo + hi) >> 1;
			int j = (m + n) / 2 - i;
			if (nums1[i - 1] <= nums2[j])  lo = i; 
			else { hi = i; continue; }
		}
		int j = (m + n) / 2 - lo;;
		if ((m + n) % 2 == 0)
			return (std::min(nums1[lo - 1], nums2[j - 1]) + std::max(nums1[lo], nums2[j])) / 2.0;
		else
			return std::min(nums1[lo], nums2[j]);
	}
};
