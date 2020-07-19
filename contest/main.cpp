#include <functional>
#include <iostream>
#include <algorithm>
#include <exception>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <mutex>
#include <thread>
#include <chrono>
#include <ratio>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>

class Ticker{
public:
    Ticker(): lastTime_(std::chrono::steady_clock::now()){}
    void setNow(){ lastTime_ = std::chrono::steady_clock::now(); }
    std::chrono::milliseconds elapsedTime(){
        auto now = std::chrono::steady_clock::now();
        std::chrono::milliseconds ret = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime_);
        lastTime_ = now;
        return ret;
    }
private:
    decltype(std::chrono::steady_clock::now()) lastTime_;
};
struct Solution{
    static void AplusB(){
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", a+b);
    }
    void removalGame(){
        int n;
        int data[200];
        int gcds[1001][1001];
        for(int i = 1; i <= 1000; i++)
            for(int j = i; j <= 1000; j++){
                gcds[i][j] = gcds[j][i] = gcd(i, j); 
            }
        while(scanf("%d", &n) != EOF){
            if(n == 0) break;
            for(int i = 0; i < n; i++){
                int input;
                scanf("%d", &input);
                data[i] = data[i+n] = input;
            }
            for(int i = 0; i < 2 * n; i++){
                for(int j = 0; j < 2 * n; j++){
                    dp300_[i][j] = 1000000;
                }
                dp300_[i][i] = 0;
                if(i != 2*n-1)dp300_[i][i+1] = 0;
            }

            for(int i = 2 * n - 1; i >= 0; i --)
                for(int j = i; j < 2 * n; j++){
                    for(int k = i + 1; k < j; k++){
                        dp300_[i][j] = std::min(dp300_[i][j], dp300_[i][k] + dp300_[k][j] + gcds[data[i]][data[j]]);
                    }
                }
            
            // for(int i = 0; i < 2*n; i++){
            //     for(int j = 0; j < 2 * n; j++){
            //         if(dp300_[i][j] != 1000000)std::cout << dp300_[i][j] << " ";
            //         else std::cout << "* ";
            //     }
            //     std::cout << std::endl;
            // }
            int ans = 1000000;
            for(int i = 0; i < n; i++)
                for(int j = i + 1; j < i + n; j++){
                    ans = std::min(ans, dp300_[i][j] + dp300_[j][i+n] + gcds[data[i]][data[j]]);
                    // std::cout << i << " " << j << " " << ans << std::endl;
                }

            std::cout << ans << std::endl;
        }
    }
    int gcd(int a, int b){ return b ? gcd(b, a % b) : a; }
    void aliceMatrix(){
        int T, a, n, caseCnt = 1;;
        scanf("%d", &T);
        while(T--){
            scanf("%d%d", &a, &n);
            std::vector<int> Fi1(n, 0);
            std::vector<int> F1j(n, 0);
            for(int i = 0; i < n; i++)
                scanf("%d", &Fi1[i]);
            for(int i = 0; i < n; i++)
                scanf("%d", &F1j[i]);
            
            std::vector<int> dp;
            dp.swap(Fi1);
            for(int i = 1; i < n; i++){
                dp[0] = F1j[i];
                for(int j = 1; j < n; j++){
                    long long plus1 = static_cast<long long>(a) * dp[j-1] % static_cast<long long>(1e9 + 7);
                    long long plus2 = static_cast<long long>(a) * dp[j] % static_cast<long long>(1e9 + 7);
                    dp[j] = static_cast<int>((plus1 + plus2) % static_cast<long long>(1e9+7));
                }
            }
            printf("case %d: %d\n", caseCnt++, dp[n-1]);
        }
    }
    bool isMatch(std::string s, std::string p){ // leetcode10
        // empty?
        // non empty
        int sPtr = 0, pPtr = 0;
        auto sNum = s.size(), pNum = p.size();
        int **matchArray = (int **)new int*[sNum+1];
        for(int i = 0; i <= sNum; i++){
            matchArray[i] = new int[pNum+1];
            memset(matchArray[i], 0, sizeof(int)*(pNum+1));
        }
        for(int j = 0; j < pNum; j++){ // 局部性不好
            if(p[j] == '*'){
                for(int i = 0; i <= sNum; i++){
                    matchArray[i][j] = -1;
                }
            }
        }
        // for(int i = sNum - 1; i >= 0; i--){
            // matchArray[i][pNum] = 0;
        // }
        for(int j = pNum - 1; j>=0;){
            if(p[j] != '*'){
                break;
            } else{
                matchArray[sNum][j-1] = 1;
                j = j - 2;
            }
        }
        matchArray[sNum][pNum] = 1;

        for(int i = sNum - 1; i >=0; i--)
            for(int j = pNum - 1; j >= 0; j--){
                switch (p[j])
                {
                case '*':
                    /* code */
                    break;
                case '.':
                    if(j < pNum - 1 && p[j+1] == '*'){
                        for(int k = 0; i + k <= sNum; k++){
                            if(matchArray[i+k][j+2] == 1){
                                matchArray[i][j] = matchArray[i+k][j+2];
                                break;
                            }
                        }
                    } else {
                        matchArray[i][j] = matchArray[i+1][j+1];
                    }
                    break;
                default: // a-z
                    if(j < pNum - 1 && p[j+1] == '*'){
                        if(s[i] == p[j])
                            for(int k = 0; i + k <= sNum; k++){
                                if(i+k < sNum && s[i+k] !=s[i] || matchArray[i+k][j+2] == 1) {
                                    matchArray[i][j] = matchArray[i+k][j+2];
                                    break;
                                }
                            }
                        else{
                            matchArray[i][j] = matchArray[i][j+2];
                        }
                    } else {
                        if(s[i] == p[j]){
                            matchArray[i][j] = matchArray[i+1][j+1];
                        }
                        // else, remain 0
                    }
                    break;
                }
            }
        int ret = matchArray[0][0];
        for(int i = 0; i <= sNum; i++)
            delete[] matchArray[i];
        delete[] matchArray;
        return ret;
    }
    int primePalindrome(int N){ // leetcode866
        if(N <= 2) return 2;
        if(N == 3) return 3;
        if(N <= 5) return 5;
        if(N <= 7) return 7;
        if(N <= 11) return 11;
        int ret = N;
        while(true){
            int digitCount = 0;
            int digitRet = ret;
            while(digitRet){
                digitRet /= 10;
                digitCount ++;
            }
            if(digitCount % 2 == 0) // 偶数位回文数是11的倍数
                ret = pow(10, digitCount);
            if(isPalindrome(ret)){
                if(isPrime(ret)){
                    return ret;
                }    
            }
            ret ++;
        }
    }
    bool isPalindrome(int N){
        // std::string strN = std::to_string(N);
        // int cursor = 0, mid = strN.size() / 2, size = strN.size();
        // while(cursor != mid){
        //     if(strN[cursor] != strN[size - 1 - cursor])
        //         return false;
        //     cursor++;
        // }
        // if(strN[cursor] == strN[size - 1 - cursor])
        //     return true;
        // return false;
        int reverse = 0;
        int oldN = N;
        while(N){
            int lowest = N % 10;
            reverse = reverse * 10 + lowest;
            N /= 10;
        }
        if(reverse == oldN) return true;
        return false;
    }
    bool isPrime(int N){ // 2 <= N <= INT32MAX
        if(N == 2) return true;
        int mid = static_cast<int>(floor(sqrt(N)));
        for(int i = 2; i <= mid; i++){
            if(N % i == 0)
                return false;
        }
        return true;
    }

    int dp300_[300][300];

};
struct SolutionIEEE{
    void ieee3(){
        long long L;
        int i = 1;
        memset(dp_, -1, sizeof(dp_));
        while(std::cin >> L){
            if(L == 0) break;
            printf("Case %d:%lld\n", i++, solve3(L));
        }
    }
    long long solve3(long long R){
        int pos = 0;
        while(R){
            digit_[pos++] = R % 10;
            R /= 10;
        }
        return dfs3(pos -1, 0, 0, true);
    }
    long long dfs3(int pos, int mod, int state, bool limit){
        if(pos == -1){
            if(state == 2 && mod == 0){
                return 1;
            } else {
                return 0;
            }
        }
        if(!limit && dp_[pos][mod][state] != -1) return dp_[pos][mod][state];

        int len = limit ? digit_[pos] : 9;
        long long sum = 0;
        for(int i = 0; i < len; i++){
            sum += dfs3(pos - 1, (mod * 10 + i) % 8, state == 2 ? 2 : 1, limit && i == digit_[pos]);
        }
    }
    int digit_[20];
    long long dp_[20][20][3];

    void ieee4(){
        int N, k;
        std::cin >> N;
        std::cin >> k;
        std::array<std::array<int, 200>, 200> shelf;
        std::vector<std::tuple<int, int>> reversePair;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < k; j++){
                std::cin >> shelf[i][j];
            }
            int cnt = 0;
            Merge(shelf[i], 0, k, cnt);
            reversePair.emplace_back(i, cnt);
        }
        std::stable_sort(reversePair.begin(), reversePair.end(), [](const std::tuple<int, int> &rp1, const std::tuple<int, int> &rp2){
            return std::get<1>(rp1) < std::get<1>(rp2);
        });
        std::cout << "[";
        for(int i = 0; i < N; i++){
            if(i != 0)std::cout << ", [";
            else std::cout << "[";
            for(int j = 0; j < k; j++){
                if(j != 0)std::cout << ", ";
                std::cout << shelf[std::get<0>(reversePair[i])][j];
                // std::cout << std::get<0>(reversePair[i]);
            }
            std::cout << "]";
        }
        std::cout << "]";
    }
    void Merge(std::array<int, 200> shelfi, int lo, int hi, int &cnt){
        if (lo + 1 < hi){
            std::array<int, 200> mergeArray;
            int mid = (lo + hi) / 2;
            Merge(shelfi, lo, mid, cnt);
            Merge(shelfi, mid, hi, cnt);
            int i = lo, j = mid, k = lo;
            while(i < mid || j < hi){
                if((i < mid && shelfi[i] < shelfi[j]) || hi <= j){
                    mergeArray[k++] = shelfi[i++];
                } else {
                    mergeArray[k++] = shelfi[j++];
                    cnt += (mid - i);
                }
            }
            for(int i = lo; i < hi; i++){
                shelfi[i] = mergeArray[i];
            }
        }
    }
};

struct Brutal{
    static void AplusB(){
        int a, b;
        scanf("%d%d", &a, &b);
        while(b--)a++;
        printf("%d\n", a);
    }
};
struct Generator{
    static void AplusB(){
        srand(time(0));
        int a, b;
        a = rand() % 10000 / 2; b = rand() % 10000 / 2;
        printf("%d %d\n", a, b);
    }
};
struct Counterpoint{
    static void AplusB(){
        int t = 10;
        while(t--){
            freopen("data", "w+", stdout);
            Generator::AplusB();
            fclose(stdout);

            assert(NULL != freopen("data", "r+", stdin));
            freopen("AC.out", "w+", stdout);
            Solution::AplusB();
            fclose(stdout);
            fclose(stdin);

            assert(NULL != freopen("data", "r+", stdin));
            freopen("BL.out", "w+", stdout);
            Brutal::AplusB();
            fclose(stdout);
            fclose(stdin);

            freopen("/dev/tty", "w", stdout); 
            freopen("/dev/tty", "r", stdin); 
            system("diff AC.out BL.out");
        }
    }
};
int main(){
    // Solution solution;
    // solution.aliceMatrix();
    // Ticker ticker;
    // int num = 10e4, ans;
    // for(int i = 0; i < num; i++)
    //     for(int j = 0; j < num; j++){
    //         ans += i * j;
    //     }
    // std::cout << ticker.elapsedTime().count() << "ms" << std::endl;
    // Solution().removalGame();
    // assert(NULL != freopen("data", "r+", stdin));
    SolutionIEEE().ieee4();
    return 0;
}
// import java.util.Scanner;

// public class Main {
//     public static void main(String[] args)
//     {
//         Scanner sc=new Scanner(System.in);
//         int n=sc.nextInt();
//         int[] A=new int[n];
//         for(int i=0;i<n;i++)
//             A[i]=sc.nextInt();
//         int[][] B=new int[n-1][2];
//         for(int i=1;i<n;i++)
//         {
//             int value=Math.abs(A[i]-A[0]);
//             B[i-1][0]=value;
//             B[i-1][1]=1;
//             for(int j=1;j<i;j++)
//             {
//                 if(Math.abs(A[i]-A[j])<B[i-1][0])
//                 {
//                     B[i-1][0]=Math.abs(A[i]-A[j]);
//                     B[i-1][1]=j+1;
//                 }
//                 else if(Math.abs(A[i]-A[j])==B[i-1][0])
//                 {
//                     if(A[j]<A[B[i-1][1]-1])
//                         B[i-1][1]=j+1;
//                 }
//             }
//         }
//         for(int[] temp:B)
//         {
//             System.out.println(temp[0]+" "+temp[1]);
//         }
//     }

// }