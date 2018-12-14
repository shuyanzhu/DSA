#pragma once
#include "BinTree.h"
template <typename T>
class BinTree
{
protected:
	int _size;
	BinNode<T> *_root;
	virtual int updateHeight(BinNode<T> *x)
	{ // 更新节点x的高度
		return max(stature(x->left, stature(x->right)));
	}
	void updateHeightAbove(BinNode<T> *x)
	{
		while (x) {
			updateHeight(x);
			x = x->parent;
		}
	}

public:
	int size() { return _size; }
	bool empty() { return !_root; }
	BinNode<T> *root() const { return _root; }
	BinNode<T> *insertAsLC(BinNode<T> *x, const T &e)
	{
		_size++;
		x->insertAsLC(e);
		updateHeightAbove(x);
		return x->left;
	}
	BinNode<T> *insertAsRC(BinNode<T> *x, const T &e)
	{
		_size++;
		x->insertAsRC(e);
		updateHeightAbove(x);
		return x->right;
	}
	template <typename VST>
	void traPost(VST &visit) const
	{
		_root->traPost(visit);
	}
};

