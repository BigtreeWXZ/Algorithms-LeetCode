#include<iostream>
#include<vector>
#include<queue>
using namespace std;

enum color {white, gray, black};

struct Node{
	int d;//����
	int p;//ǰ���ڵ�
	color c;//��ɫ
	Node() :d(INT_MAX), p(-1), c(white){}
};

//ͨ�����ʹ����������ӡ��s��v�����·��
void PrintPath(vector<Node>& BFT, int s, int v){
	if (v == s){
		cout << s;
	}
	else if (BFT[v].d == INT_MAX){
		cout << "�����ڴӵ�" << s << "����" << v << "�����·��" << endl;
	}
	else{
		PrintPath(BFT, s, BFT[v].p);
		cout << "-->" << v;
	}
}

//������ȱ���
//Adj��������ڽӱ�, s��Դ��
void BFS(vector<vector<int>>& Adj, int s){
	//�������г�ʼ�����������
	vector<Node> BFT(Adj.size());
	BFT[s].d = 0;
	BFT[s].c = gray;
	queue<int> Q;
	Q.push(s);
	while (!Q.empty()){
		int u = Q.front();//ȡ��ͷ
		Q.pop();
		//������u���ӵ����е�
		for (int v : Adj[u]){
			//vû�б�����
			if (BFT[v].c == white){
				//���������޸�v��ǰ������
				BFT[v].c = gray;
				BFT[v].d = BFT[u].d + 1;
				BFT[v].p = u;
				Q.push(v);
			}
		}
		BFT[u].c = black;
	}
	//��ʼ��ӡ
	for (int i = 0; i < Adj.size(); i++){
		if (i != s){
			PrintPath(BFT, s, i);
			if (BFT[i].d != INT_MAX)
				cout << "·������Ϊ:" << BFT[i].d << endl;
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
	int s;
	cout << "����Դ�㣺";
	cin >> s;
	BFS(Adj, s);
	system("pause");
	return 0;
}