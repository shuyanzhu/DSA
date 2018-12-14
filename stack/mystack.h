#ifndef MYSTACK
#define MYSTACK
#include<vector>
template<T>
class mystack :public std::vector<T> {
public:
	void push(const T &e) {
		insert(size(), e);
	}
	T pop() { return remove(e); }
	T &top() { return (*this)[size() - 1]; }
};
#endif;

