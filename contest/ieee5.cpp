#include <functional>
#include <set>
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

struct SolutionIEEE{
    int cnt = 0;
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
            auto tmp = shelf[i];
            std::array<int, 200> mergeArray;
            cnt = 0;
            Merge(tmp, 0, k, mergeArray);
            reversePair.emplace_back(i, cnt);
        }
        std::stable_sort(reversePair.begin(), reversePair.end(), [](const std::tuple<int, int> &rp1, const std::tuple<int, int> &rp2){
            return std::get<1>(rp1) < std::get<1>(rp2); // <= !!!
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
        std::cout << "]\n";
    }
    void Merge(std::array<int, 200> &shelfi, int lo, int hi, std::array<int, 200> &mergeArray){
        if (lo + 1 < hi){
            int mid = (lo + hi) / 2;
            Merge(shelfi, lo, mid, mergeArray);
            Merge(shelfi, mid, hi, mergeArray);
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
    void ieee5(){
        int N, p[50], d[50];
        std::cin >> N;
        for(int i = 0; i < N; i++)
            std::cin >> d[i];
        for(int i = 0; i < N; i++)
            std::cin >> p[i];
        
        int needStrengh, currentStrength, currentForce = 0;
        needStrengh = p[0]; 
        while(true){
            currentStrength = needStrengh;
            currentForce = 0;
            bool finish = true;
            for(int i = 0; i < N; i++){
                if(currentStrength >= p[i]){
                    currentForce += d[i];
                    currentStrength -= p[i];
                } else if(currentForce >= d[i]){
                    currentForce -= d[i];
                } else {
                    needStrengh += 1;
                    finish = false;
                    break;
                }
            }
            if(finish) break;
        }
        std::cout << needStrengh << std::endl;
    }
    void ieee11(){
        int T, N;
        std::cin >> T;
        while(T--){
            std::cin >> N;
            std::multiset<int> people;
            for(int i = 0; i < N; i++){
                int person;
                std::cin >> person;
                people.insert(person);
            }
            
            int sum = 0;
            if(N <= 3){
                sum += *(people.rbegin());
            } else{
                auto first = people.begin();
                auto firstNum = *first;
                people.erase(first);
                auto second = people.begin();
                auto secondNum = *second;
                people.erase(second);
                for(auto &&it : people){
                    sum += it;
                    sum += secondNum;
                }
                sum -= secondNum;
            }
            std::cout << sum << std::endl;
        }
    }
};

int main(){

    assert(NULL != freopen("data", "r+", stdin));
    SolutionIEEE().ieee4();
    return 0;
}
