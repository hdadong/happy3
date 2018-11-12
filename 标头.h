#pragma once
#ifndef Thread
#define Thread
#include<iostream>
#include<stack>
#include<cstring>
#include<string>
#include<ifstream>

using namespace std;
template<class T>
struct ThreadNode
{
	int ltag, rtag;
	ThreadNode<T> *leftChild, *rightChild;
	T data;
	ThreadNode(const T item) :data(item), leftChild(NULL), rightChild(NULL), ltag(0), rtag(0) {}

};

template<class T>
class ThreadTree
{
	
protected:
	ThreadNode<T>*root;
	T RefValue;
	void createInThread(ThreadNode<T>*current, ThreadNode<T>*&pre);
	//ThreadNode<T>*parent(ThreadNode<T>*t);
	
	
public:
	void CreateBinTree(istream&in, ThreadNode<T> *&BT);
	ThreadTree() : root(NULL) {}
	ThreadTree(T value) :RefValue(value),root(NULL) {}
	void createInThread();
	ThreadNode<T>*First(ThreadNode<T>*current);//寻找中序下的第一个节点
	ThreadNode<T>*Last(ThreadNode<T>*current);//寻找中序下最后一个节点
	ThreadNode<T>*Next(ThreadNode<T>*current);//寻找节点在中序下的后继节点
	ThreadNode<T>*Prior(ThreadNode<T>*current);//寻找节点中序下的前驱节点

	
	void Inorder(void(*visit)(ThreadNode<T>*p));
	//void preorder(void(*visit)(ThreadNode<T>*p));
//	void postorder(void(*visit)(ThreadNode<T>*p));
	
	template<class U>
	friend istream&operator>>(istream&in, ThreadTree<U>&Tree);
	
};
template<class U>
istream& operator>>(istream&in, ThreadTree<U>&Tree)
{
	cout << "输入一个广义表:";
	Tree.CreateBinTree(in, Tree.root);//建立二叉树
	return in;
}
template<class T>
void ThreadTree<T>::CreateBinTree(istream&in, ThreadNode<T> *&BT)
{
	stack<ThreadNode<char>* > s;
	BT = NULL;
	ThreadNode<char>*p, *t; int k = 0;
	char ch;
	in >> ch;
	while (ch != RefValue)
	{
		switch (ch)
		{
		case'(':s.push(p); k = 1; break;//进入子树
		case')':t = s.top(); s.pop(); break;//退出子树
		case',':k = 2; break;
		default:
			p = new ThreadNode<T>(ch);
			if (BT == NULL)BT = p;
			else if (k == 1)
			{
				t = s.top(); t->leftChild = p;//链入左子女
			}
			else if (k == 2)
			{
				t = s.top(); t->rightChild = p;
			}
		}
		in >> ch;
	}
}
template<class T>
ThreadNode<T>*ThreadTree<T>::First(ThreadNode<T>*current)
{
	//函数返回以*current为跟的中序二叉树中中序序列下的第一个节点
	ThreadNode<T>*p = current;
	
	while (p->ltag == 0)p = p->leftChild;//最左下节点
	return p;
}

template<class T>
ThreadNode<T>* ThreadTree<T>::Next(ThreadNode<T>*current)
{
	//函数返回在中序线索二叉树中节点current在中序下的后继节点
	ThreadNode<T>*p = current->rightChild;
	if (current->rtag ==0 )return First(p);
	else return p;//rtag==1直接返回后继线索

}

template<class T>
ThreadNode<T>*ThreadTree<T>::Last(ThreadNode<T>*current)
{
	//函数返回以current为跟的中序线索二叉树中序序列下的最后一个节点
	ThreadNode<T>*p = current;
	while (p->rtag == 0)p = p->rightChild;//最右下节点
	return p;
}

template<class T>
ThreadNode<T>*ThreadTree<T>::Prior(ThreadNode<T>*current)
{
	//函数返回在中序线索二叉树中节点current在中序下的前驱节点
	ThreadNode<T>*p = current->leftChild;
	if (current->ltag == 0)return Last(p);//在左子树中找中序最后一个节点
	else return p;
}

template<class T>//中序遍历
void ThreadTree<T>::Inorder(void(*visit)(ThreadNode<T>*p))
{
	ThreadNode<T>*p;
	cout << "中序遍历二叉树:";
	for (p = First(root); p != NULL; p = Next(p))visit(p);
	cout << endl;
}

template<class T>
void ThreadTree<T>::createInThread()
{
	cout << "成功创建中序二叉树：" << endl;
	ThreadNode<T>*pre = NULL;
	if (root != NULL)
	{
		createInThread(root, pre);
		pre->rightChild = NULL; pre->rtag = 1;

	}
}

template<class T>
void ThreadTree<T>::createInThread(ThreadNode<T>*current, ThreadNode<T>*&pre)
{
	if (current == NULL)return;
	createInThread(current->leftChild, pre);//递归，左子树线索化
	if (current->leftChild == NULL)
	{//a
		current->leftChild = pre; current->ltag = 1;
	}
	if (pre != NULL && pre->rightChild == NULL)
	{
		pre->rightChild = current; pre->rtag = 1;

	}
	pre = current;
	createInThread(current->rightChild, pre);
}

#endif