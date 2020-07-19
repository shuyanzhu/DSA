#pragma once
#include <string>
#include <iostream>

class Solution43{
public:
    void simpleTest(){
        std::cout << multiply("123", "4567") << std::endl;    
    }
    std::string multiply(std::string num1, std::string num2) { // 123 x 4567
        if(num1 == "0" || num2 == "0") return "0";
        std::string result = std::string(num1.size() + num2.size(), '0');
        for(int i = 0; i < num1.size(); i++){ // 4567
            for(int j = 0; j < num2.size(); j++){ // 123
                int tmp = (num1[i] - '0') * (num2[j] - '0');
                addTmp(result, i + j + 1, tmp);
            }
        }
        if(result[0] == '0') result = result.substr(1);
        return result;
    }
private:
    void addTmp(std::string &result, size_t index, int tmp){
        int sum = result[index] - '0' + tmp;
        result[index] = sum % 10 + '0';
        if(sum / 10)
            addTmp(result, index - 1, sum / 10);
    }
};