#include <string>
#include <algorithm>
using namespace std;
class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		int n = s.length();
		int ans = 0;
		for (int i = 0; i<n; i++)
			for (int j = i + 1; j < n; j++) {
				if (valid(s.substr(i, j - i), s[j]))ans = max(ans, j - i + 1);
				else break;
			}
		if (!ans && !s.empty())ans = 1;
		return ans;
	}
	bool valid(const string &s, char &ch) {
		return s.find(ch) == string::npos;
	}
};