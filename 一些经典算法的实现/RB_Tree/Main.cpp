#include"RBTree.h"
#include<iostream>

using namespace std;

int main(){
	vector<int> A = {9, 0, 7, 8, 3, 6, 4, 2, 1, 5};
	RBNode *root = new RBNode(A[0]);
	RB_Tree tree =  RB_Tree(root);
	for (int i = 1; i < A.size(); i++){
		RBNode *temp = new RBNode(A[i]);
		tree.RBTInsert(temp);
	}
	cout << "�������ʼ��Ϊ��";
	tree.InOrderTraverse();
	cout << endl;
	int input;
	while (1){
		input = 0;
		cout << "����Ҫ���������Ĺؼ��ֵ�ֵ������-1��ʾ�������룺";
		cin >> input;
		if (input == -1)
			break;
		else{
			RBNode *temp = new RBNode(input);
			if (tree.RBTInsert(temp))
				cout << "�ڵ�" << input << "����ɹ�" << endl;
		}
	}
	cout << endl;
	cout << "��������������";
	tree.InOrderTraverse(); cout << endl;
	while (1){
		input = 0;
		cout << "����Ҫɾ��������Ĺؼ��ֵ�ֵ������-1��ʾ�������룺";
		cin >> input;
		if (input == -1)
			break;
		else{
			if (tree.RBTDelete(input))
				cout << "�ڵ�" << input << "ɾ���ɹ�" << endl;
		}
	}
	cout << "��������������";
	tree.InOrderTraverse(); cout << endl;
	system("pause");
	return 0;
}