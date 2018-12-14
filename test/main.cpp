//#define _CRT_SECURE_NO_WARNINGS
//
//#include<iostream>
//#include<vector>
//#include<string>
//#include<algorithm>
//#include<queue>
//#include<stack>
//using namespace std;
//int main() {
//	int M, N;
//	cin >> M; cin >> N;
//	vector<vector<int>> NN;// 需要满足的条件数
//	for (int i = 0; i < N; i++) {
//		int k, j; vector<int> cur;
//		cin >> k; cin >> j;
//		cur.push_back(k); cur.push_back(j);
//	}
//	int **anss = new int*[M];
//	int ans = 0;
//	for (int i = 0; i < M; i++) {
//		anss[i]= new int[M];
//		memset(anss[i], -1, M * 4);
//	}
//
//	for(int i=0;i<N;i++){
//		int k = 0; int j = 0;
//		k = NN[i][0]-1; j = NN[i][1]-1;
//		if (anss[k][j] != -1)goto end;
//		else {
//			anss[k][j] = anss[j][k] = 1;
//		}
//	}
//	for (int i = 1; i <= M; i++)ans += i;
//	cout << ans << endl;
//	return ans;
//end:
//	cout << -1 << endl;
//	return 0;
//}

//#include<iostream>
//
//void dayin() {
//	std::cout << "Hello, world" << std::endl;
//}
//
//int main() {
//	dayin();
//	return 0;
//}