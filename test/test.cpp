/*
 * @Author: 朱会茗
 * @Date: 2018-10-08 16:38:22
 * @LastEditors: OBKoro1
 * @LastEditTime: 2018-10-08 16:38:22
 * @Description:
 */
/*
 * @Author: OBKoro1
 * @Date: 2018-10-08 16:31:15
 * @LastEditors: OBKoro1
 * @LastEditTime: 2018-10-08 16:31:15
 * @Description:
 */
//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//#include<string>
// using namespace std;
// int main() {
//	//string input = ")())())(()))";
//	string input = "(())";
//	int max_begin = 0;
//	int max_length = 0;
//	int cur_begin = 0;
//	int cur_point = 0;
//	int cur_count = 0;
//	while (true) {
//		if (cur_point == input.length())break;
//		if (input[cur_point] == '(')cur_count++;
//		else if (cur_count > 0)cur_count--;
//		else {
//			if (cur_begin != cur_point && (max_length < cur_point - cur_begin + 1))
//{ 				max_begin = cur_begin; 				max_length = cur_point - cur_begin + 1;
//			}
//			cur_begin = cur_point + 1;
//			cur_count = 0;
//		}
//		cur_point++;
//	}
//	cout << max_length << endl;
//	cout << max_begin << endl;
//	return 0;
//}
//#include<iostream>
// using namespace std;
//
// void Print() {}
// int main() {
//	Print();
//}