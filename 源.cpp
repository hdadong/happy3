#include"БъЭЗ.h"
template<class T>
void visit2(ThreadNode<T>*p)
{
	cout << p->data << " ";
}
int main()
{
	ThreadTree<char> sb('#');
	cin >> sb;
	sb.createInThread();
	sb.Inorder(visit2);
	getchar();
	getchar();
	getchar();
	return 0;

}