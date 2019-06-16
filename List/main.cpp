#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include "mylist.h"

int main(){
    auto a = List<int>();
    return 0;
}
//int main() {
//	char c; int n = 0;
//	Rank r; char in;
//	List<char> L;
//	for (;;) {
//		c = getchar();
//		if (c == '\n')break;
//		L.insertAsLast(c);
//	}
//	scanf("%d", &n);
//
//	// n次插入,主循环
//	for (int i = 0; i < n; i++) {
//		scanf("%d %c", &r, &in);
//		Nchar *p= L.insert(r, in);;
//
//		// 重复检测是否满足删除条件，轮数未知，两种停止条件
//		for (;;) {
//			if (L.size() < 3)break;
//			p = L.check(p);
//			if (!p)break;
//			char e = p->data;
//			// 删除本轮检测到的待删节点
//			for (Nchar *next = p->succ;p!=L.last()->succ; next = next->succ) {
//				if (p->data == e) {
//					L.remove(p);
//					p = next;
//					continue;
//				}
//				break;
//			}
//		}
//		// 本次插入和删除后的结果
//		PrintChar visit;
//		if (L.empty()){
//			printf("-");
//			if (i != n - 1)printf("\n");
//		}
//		if (!L.empty()) {
//			L.traverse<PrintChar>(visit);
//			if(i!=n-1)printf("\n");
//		}
//
//
//
//	}
//
//	return 0;
//}