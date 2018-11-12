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
	ThreadNode<T>*First(ThreadNode<T>*current);//Ѱ�������µĵ�һ���ڵ�
	ThreadNode<T>*Last(ThreadNode<T>*current);//Ѱ�����������һ���ڵ�
	ThreadNode<T>*Next(ThreadNode<T>*current);//Ѱ�ҽڵ��������µĺ�̽ڵ�
	ThreadNode<T>*Prior(ThreadNode<T>*current);//Ѱ�ҽڵ������µ�ǰ���ڵ�

	
	void Inorder(void(*visit)(ThreadNode<T>*p));
	//void preorder(void(*visit)(ThreadNode<T>*p));
//	void postorder(void(*visit)(ThreadNode<T>*p));
	
	template<class U>
	friend istream&operator>>(istream&in, ThreadTree<U>&Tree);
	
};
template<class U>
istream& operator>>(istream&in, ThreadTree<U>&Tree)
{
	cout << "����һ�������:";
	Tree.CreateBinTree(in, Tree.root);//����������
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
		case'(':s.push(p); k = 1; break;//��������
		case')':t = s.top(); s.pop(); break;//�˳�����
		case',':k = 2; break;
		default:
			p = new ThreadNode<T>(ch);
			if (BT == NULL)BT = p;
			else if (k == 1)
			{
				t = s.top(); t->leftChild = p;//��������Ů
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
	//����������*currentΪ������������������������µĵ�һ���ڵ�
	ThreadNode<T>*p = current;
	
	while (p->ltag == 0)p = p->leftChild;//�����½ڵ�
	return p;
}

template<class T>
ThreadNode<T>* ThreadTree<T>::Next(ThreadNode<T>*current)
{
	//�������������������������нڵ�current�������µĺ�̽ڵ�
	ThreadNode<T>*p = current->rightChild;
	if (current->rtag ==0 )return First(p);
	else return p;//rtag==1ֱ�ӷ��غ������

}

template<class T>
ThreadNode<T>*ThreadTree<T>::Last(ThreadNode<T>*current)
{
	//����������currentΪ���������������������������µ����һ���ڵ�
	ThreadNode<T>*p = current;
	while (p->rtag == 0)p = p->rightChild;//�����½ڵ�
	return p;
}

template<class T>
ThreadNode<T>*ThreadTree<T>::Prior(ThreadNode<T>*current)
{
	//�������������������������нڵ�current�������µ�ǰ���ڵ�
	ThreadNode<T>*p = current->leftChild;
	if (current->ltag == 0)return Last(p);//�������������������һ���ڵ�
	else return p;
}

template<class T>//�������
void ThreadTree<T>::Inorder(void(*visit)(ThreadNode<T>*p))
{
	ThreadNode<T>*p;
	cout << "�������������:";
	for (p = First(root); p != NULL; p = Next(p))visit(p);
	cout << endl;
}

template<class T>
void ThreadTree<T>::createInThread()
{
	cout << "�ɹ����������������" << endl;
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
	createInThread(current->leftChild, pre);//�ݹ飬������������
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