#include<iostream>
#include<vector>
using namespace std;
const int MAXDISTANCE = 100000;
//����߶���
struct Edge{
	int start, end;//����ߵĶ˵�
	int weight;//�ߵ�Ȩֵ
	Edge() :start(-1), end(-1), weight(0){}
};

//��Ķ���
struct Node{
	int parent;//ǰ���ڵ�
	int  d;//���·������
	Node() :parent(-1), d(MAXDISTANCE){}
};

//��ʼ�����·����
//n�ǽڵ���,s��Դ��
vector<Node> InitializeSingleSource(int n, int s){
	vector<Node> res(n);
	res[s].d = 0;
	return res;
}

//�ɳڲ���
//�������·����, �����<u, v>������Ȩֵ
void RELAX(vector<Node>& SPT, int u, int v, int w){
	if (SPT[v].d > SPT[u].d + w){
		SPT[v].d = SPT[u].d + w;
		SPT[v].parent = u;
	}
}

//Bellman-Ford�㷨
//����False��ʾ�����ͼ�а�����Դ�ڵ㵽���ȨֵΪ���Ļ�·
//SPT��ʾ���·����, edges�Ǳ߼���, n�ǵ�ĸ���
bool Bellman_Ford(vector<Node>& SPT, vector<Edge>& edges, int n){
	//��ÿ���߽���|V| - 1���ɳڲ���
	for (int i = 0; i < n - 1; i++){
		for (auto e : edges){
			RELAX(SPT, e.start, e.end, e.weight);
		}
	}
	//�ж��Ƿ����ȨֵΪ���Ļ�·
	//������ڵĻ�,ÿ����һ�λ�·ʱ���·�������С
	//���ھͷ���false, ���򷵻�true
	for (auto e : edges){
		if (SPT[e.end].d > SPT[e.start].d + e.weight)
			return false;
	}
	return true;
}

//�������·������ӡ�ӵ�v����s�����·��
void Print_Path(vector<Node>& SPT, int s, int v){
	if (v == s){
		cout << s;
	}
	else if (SPT[v].d == MAXDISTANCE){
		cout << "�����ڴӽڵ�" << s << "���ڵ�" << v << "��·��" << endl;
	}
	else{
		Print_Path(SPT, s, SPT[v].parent);
		cout << "-->" << v ;
	}
}

int main(){
	cout << "����ڵ���������ߵĸ�����";
	int n, m;
	cin >> n >> m;
	vector<Edge> edges(m);
	cout << "��������ߵ����,�յ�,Ȩֵ(ÿ����Ȩֵ��Ҫ����100,·�����Ȳ�Ҫ����100000,�ڵ��Ŵ�0��ʼ)��" << endl;
	int input1, input2, input3;
	for (int i = 0; i < m; i++){
		cin >> input1 >> input2 >> input3;
		edges[i].start = input1;
		edges[i].end = input2;
		edges[i].weight = input3;
	}
	cout << "����Դ�㣺";
	int s; cin >> s;
	vector<Node> SPT = InitializeSingleSource(n, s);
	if (!Bellman_Ford(SPT, edges, n)){
		cout << "ͼ�д���ȨֵΪ���Ļ�·" << endl;
	}
	else{
		cout << "�������·��Ϊ��" << endl;
		for (int i = 0; i < n; i++){
			if (i != s){
				Print_Path(SPT, s, i);
				cout << " ���·��ȨֵΪ:" << SPT[i].d << endl;
			}
		}
	}
	system("pause");
	return 0;
}