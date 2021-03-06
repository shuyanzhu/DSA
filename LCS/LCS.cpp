// LCS.cpp: 定义控制台应用程序的入口点。
// 计算两个字符串的最大子串

#include "stdafx.h"
#include <string.h>
#include <string>
using namespace std;

int LCS(string a, string b);
int max(int a, int b);
int main(int argc, char* argv[])
{
	string a, b;
	int c;
	if (argc == 3){
		a = argv[1];
		b = argv[2];
	}
	else{
		a = "progrhhham";
		b = "algritjjghhhm";
	}
	c = LCS(a, b);

	printf("The length of maximum substring is %d\n", c);
    return 0;
}
int LCS(string a, string b){
	int len = 0;
	int alast = a.length() - 1;
	int blast = b.length() - 1;
	if (a.begin() == a.end() || b.begin() == b.end())
		return 0;
	else if (a.substr(alast) == b.substr(blast))
		return 1 + LCS(a.substr(0, a.length() - 1), b.substr(0, b.length() - 1));
	else 
		return max(LCS(a, b.substr(0, b.length() - 1)), LCS(a.substr(0, a.length() - 1), b));
}
int max(int a, int b){
	return (a > b) ? a : b;
}
