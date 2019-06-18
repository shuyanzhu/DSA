#ifndef MYSTACK
#define MYSTACK
#include "../vector/vector.h"
template<typename T> class Stack : protected Vector<T> {
public:
	void push(const T &e) {
		this->insert(e);
	}
	T pop() { return this->remove(this->_size-1); }
	T &top() { return (*this)[Vector<T>::size() - 1]; }
	bool empty(){ return this->_size == 0;}
    int size(){ return this->_size; }
};
#endif

