//
// Created by zhuhu on 2019/7/17.
//

#ifndef DSA_UTILS_H
#define DSA_UTILS_H

#define ceil(x, y) (int((double)(x) / (y) + 1))
#define round(x, y) (int((double(x) / (y)) + 0.5))
#define floor(x, y) (int((double(x) / (y))))
template <typename T>
void swap(T &a, T &b){
    auto tmp = a;
    a = b;
    b = tmp;
}
#endif //DSA_UTILS_H
