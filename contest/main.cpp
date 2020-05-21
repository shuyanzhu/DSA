#include <functional>
#include <iostream>
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

struct Solution{
    static void AplusB(){
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", a+b);
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
                    break;
                default: // a-z
                    if(j < pNum - 1 && p[j+1] == '*'){
                        if(s[i] == p[j])
                            for(int k = 0; i + k <= sNum; k++){
                                if(i+k < sNum && s[i+k] !=s[i]) {
                                    matchArray[i][j] = matchArray[i+k][j+2];
                                    break;
                                }
                                if(matchArray[i+k][j+2] == 1){
                                    matchArray[i][j] = matchArray[i+k][j+2];
                                    break;
                                }
                            }
                        else{
                            matchArray[i][j] = matchArray[i][j+2];
                        }
                    } else{
                        if(s[i] == p[j]){
                            matchArray[i][j] = matchArray[i+1][j+1];
                        }
                        // else, remain 0
                    }
                    break;
                }
            }
        int ret = matchArray[0][0];
        // for(int i = 0; i <= sNum; i++)
        //     delete[] matchArray[i];
        // delete[] matchArray;
        return ret;
    }
    bool brutalIsMatch(std::string s, std::string p, int sPtr, int pPtr){
        if(sPtr == s.size()){
            if(pPtr == p.size()) return true;
            if(pPtr + 1 == p.size()) return false;
            while(pPtr + 1 < p.size()){}
        }
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
    Solution solution;

    std::cout << solution.isMatch("aaikgh", "b*a*a*ikghb*c*d*") <<std::endl;
    return 0;
}