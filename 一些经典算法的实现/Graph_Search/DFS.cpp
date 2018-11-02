#include<iostream>
#include<vector>
#include<queue>
using namespace std;

enum color {white, gray, black};
int time = -1;

struct Node{
	int s;//��ʼ����ʱ��
	int e;//��������ʱ��
	int p;//ǰ���ڵ�
	color c;//��ɫ
	Node() :p(-1), c(white){}
};

//��u��ʼ������ȱ���
//Adj��������ڽӱ�, V�ǵ㼯, u�ǿ�ʼ�ڵ�
void DFS_Visit(vector<vector<int>>& Adj, vector<Node>& V, int u){
	//��ʼ���ʽڵ�u
	time++;
	V[u].s = time;
	V[u].c = gray;
	cout << "(" << u;
	//�����������
	for (int next : Adj[u]){
		if (V[next].c == white){
			V[next].p = u;
			DFS_Visit(Adj, V, next);
		}
	}
	//�Խڵ�u���ʽ���
	V[u].c = black;
	time++;
	V[u].e = time;
	cout << ")";
}

//��DFS��ʽ��������ͼ
void DFS(vector<vector<int>>& Adj){
	vector<Node> V(Adj.size());
	for (int i = 0; i < Adj.size(); i++){
		if (V[i].c == white){
			DFS_Visit(Adj, V, i);
			cout << endl;
		}
	}
}

int main(){
	int n, m;
	cout << "��������ͱ�����";
	cin >> n >> m;
	vector<vector<int>> Adj(n);//�ڽӱ�
	int flag;
	cout << "����ͼѡ0,����ͼѡ1��";
	cin >> flag;
	cout << "����ߵ������˵�(���������ͼ�Ļ�ע��˳��)��" << endl;
	for (int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		if (flag){
			Adj[u].push_back(v);
		}
		else{
			Adj[u].push_back(v);
			Adj[v].push_back(u);
		}
	}
	cout << "����˳��Ϊ( '('��ʾ��ʼ����, ')'��ʾ���ʽ���)��" << endl;
	DFS(Adj);
	system("pause");
	return 0;
}