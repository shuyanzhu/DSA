#include <iostream>
#include <stdlib.h>
#include <utility>
#include "../_share/utils.h"
#include <type_traits>
#include "./mylist.h"
#include <map>
#include <utility>
#include <vector>

extern template class List<int>;
using namespace std;
class Foo1{
public:
    int a_;
private:
    Foo1() = default;

public:
    virtual ~Foo1() = default;

    virtual void dn(){
        cout << "Foo1 donothong" << endl;
    }
};
class Foo2: public Foo1{
    using Foo1::Foo1;
    ~Foo2()= default;
//    void dn();
    void dn(){
        cout << "Foo2 donothong" << endl;
    }
};
class Base1{
public:
    int base(){ return 1; }
};
class Base2{
public:
    int base(){ return 2; }
};
class A{
public:
    A() = default;
    A(const A &from){
        mem_ = from.mem_;
        cout << "left" << endl;
    }
    A(const A &&from){
        mem_ = from.mem_;
        cout << "right" << endl;
    }

    int mem_;
};
int main(){
    using vstring = vector<string>;
    map<int, vstring> a;
//    auto aa = map<int, vstring>::value_type(1, vstring(10, string("aaa")));
    a.emplace(make_pair(1, vstring(10, string("aaa"))));
    for(auto &&kv  : a){
        cout << kv.first << endl;
    }
//    map<string, int> word_cnt{{"hello", 1}, {"world", 1}};
//    auto a = new pair<const string, int>{"hello", 1};
//    std::pair<string, int> kv1 = *a;
//    cout << &kv1 << endl;
//    cout << a << endl;
//    cout << "**************" << endl;
//    const std::pair<string, int> &kv2 = word_cnt.begin().operator*();
//    cout << &kv2 << endl;
//    cout << &(*word_cnt.begin()) << endl;
//    cout << "**************" << endl;
//    for(const std::pair<std::string, int>& kv : word_cnt){
//        cout << &kv << endl;
//    }
//    cout << "**************" << endl;
//    for(auto &&kv : word_cnt){
//        cout << &kv << endl;
//    }
    return 0;
}

