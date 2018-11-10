#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class BSTNode{
public:
	int val;
	BSTNode* parent;
	BSTNode* left;
	BSTNode* right;
	BSTNode() :val(), parent(nullptr), left(nullptr), right(nullptr){}
	BSTNode(int v) :val(v), parent(nullptr), left(nullptr), right(nullptr){}
};

//���һ�ö���������
void InorderTreeWalk(BSTNode* x){
	if (x != nullptr){
		InorderTreeWalk(x->left);
		cout << x->val << " ";
		InorderTreeWalk(x->right);
	}
	return;
}

//��������ķǵݹ�ʵ��
void InorderUseStack(BSTNode* root){
	stack<BSTNode*> s;
	BSTNode *node = root;
	while (node != nullptr || !s.empty()){
		if (node != nullptr){
			s.push(node);
			node = node->left;
		}
		else{
			node = s.top();
			s.pop();
			cout << node->val << " ";
			node = node->right;
		}
	}
}

//��ʹ�ø���ջ���������
void InorderMorris(BSTNode* root){
	BSTNode *cur = root, *pre = nullptr;
	while (cur != nullptr){
		//��ǰ�ڵ��������������
		if (cur->left == nullptr){
			cout << cur->val << " ";
			//�ѵ�ǰ�ڵ㻻��������
			cur = cur->right;
		}
		else{
			pre = cur->left;
			//�ҵ�ǰ���ڵ�
			while (pre->right != nullptr && pre->right != cur){
				pre = pre->right;
			}
			//ǰ���ڵ�û�д����
			if (pre->right == nullptr){
				//����ǰ���ڵ�
				pre->right = cur;
				//������
				cur = cur->left;
			}
			else{
				//��ԭ��ȥ
				pre->right = nullptr;
				cout << cur->val << " ";
				//�ѵ�ǰ�ڵ㻻��������
				cur = cur->right;
			}
		}
	}
}

//���ҹؼ�ֵΪk�Ľڵ�
BSTNode* TreeSearch(BSTNode* x, int k){
	if (x == nullptr || x->val == k)//x����Ҫ�ҵĽڵ�,������Ϊ��
		return x;
	if (k < x->val)//����������
		return TreeSearch(x->left, k);
	else//����������
		return TreeSearch(x->right, k);
}

//�õ���С�ڵ�
BSTNode* GetMin(BSTNode* x){
	//�����������ڵ�
	while (x->left != nullptr)
		x = x->left;
	return x;
}

//�ҵ����ڵ�
BSTNode* GetMax(BSTNode* x){
	//�ҵ����Ҳ�ڵ�
	while (x != nullptr)
		x = x->right;
	return x;
}

//�õ���̽ڵ�
BSTNode* GetSuccessor(BSTNode* x){
	//�������е���С�ڵ�
	if (x->right != nullptr){
		return GetMin(x->right);
	}
	//��̾���x����ײ�����
	BSTNode* y = x->parent;
	while (y != nullptr && x == y->right){
		x = y;
		y = y->parent;
	}
	return y;
}

//����ڵ�
void Insert(BSTNode* T, BSTNode* z){
	BSTNode* y = nullptr;
	BSTNode* x = T;
	//�ҵ���Ҫ�����λ��
	while (x != nullptr){
		y = x;
		if (z->val < x->val)
			x = x->left;
		else
			x = x->right;
	}
	//��z�ӵ�����
	z->parent = y;
	//T�ǿ���
	if (y == nullptr)
		T = z;
	//ȷ��zӦ�����ĸ��ӽڵ�
	else if (z->val < y->val)
		y->left = z;
	else
		y->right = z;
}

//�ýڵ�vȥ�滻u
void Transplant(BSTNode* T, BSTNode* u, BSTNode* v){
	if (u->parent == nullptr)
		T = v;
	//ȷ��u�ڸ��׽ڵ���ĸ�������
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	//��v�ӵ����׽ڵ���
	if (v != nullptr)
		v->parent = u->parent;
}

//ɾ���ڵ�z
void Delete(BSTNode* T, BSTNode* z){
	//������������,�����ӽڵ������
	if (z->left == nullptr)
		Transplant(T, z, z->right);
	//����������,������������,�����ӽڵ������
	else if (z->right == nullptr)
		Transplant(T, z, z->left);
	//�����ڵ㶼����
	else{
		//y��z�ĺ�̽ڵ�
		BSTNode* y = GetMin(z->right);
		//y����z�ĺ���
		if (y->parent != z){
			//��y���Һ����滻y
			Transplant(T, y, y->right);
			//��z���Һ��ӽӵ�y��
			y->right = z->right;
			y->right->parent = y;
		}
		//�ú�̽ڵ�y���z
		Transplant(T, z, y);
		//��z���������ŵ�y�����
		y->left = z->left;
		y->left->parent = y;
	}
}
int main(){
	vector<int> num = { 9, 5, 8, 6, 4, 3, 2, 7, 1, 10 };
	BSTNode* root = new BSTNode();
	for (int i = 0; i < num.size(); i++){
		cout << "����ֵΪ" << num[i] << "�Ľڵ�" << endl;
		if (i == 0)
			root->val = num[i];
		else{
			BSTNode* in = new BSTNode(num[i]);
			Insert(root, in);
		}
	}
	cout << "����Ķ���������Ϊ��";
	InorderTreeWalk(root);
	//InorderUseStack(root);
	//InorderMorris(root);
	cout << endl;
	int input = 0;
	while (1){
		cout << "����һ������Ҫ����ڵ��ֵ��û�еĻ�����-1��";
		cin >> input;
		if (input == -1)
			break;
		else{
			BSTNode* in = new BSTNode(input);
			Insert(root, in);
		}
	}
	cout << "�µĶ���������Ϊ��";
	InorderTreeWalk(root);
	//InorderUseStack(root);
	//InorderMorris(root);
	cout << endl;
	while (1){
		cout << "����һ������Ҫɾ���ڵ��ֵ��û�еĻ�����-1��";
		cin >> input;
		if (input == -1)
			break;
		else{
			BSTNode* target = TreeSearch(root, input);
			if (target == nullptr)
				cout << "�ڵ㲻����" << endl;
			else
				Delete(root, target);
		}
	}
	cout << "�µĶ���������Ϊ��";
	InorderTreeWalk(root);
	//InorderUseStack(root);
	//InorderMorris(root);
	cout << endl;
	system("pause");
}