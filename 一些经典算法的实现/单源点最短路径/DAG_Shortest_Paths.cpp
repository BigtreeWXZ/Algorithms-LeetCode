#include<iostream>
#include<vector>
#include<stack>
using namespace std;

const int MAXDISTANCE = 100000;

//��Ķ���
struct Node{
	int parent;//ǰ���ڵ�
	int  d;//���·������
	Node() :parent(-1), d(MAXDISTANCE){}
};

//���������㷨
vector<int> Topological_Sort(vector<vector<pair<int, int>>>& Adj, vector<int>& InDegree){
	stack<int> S;
	vector<int> res;
	//�����Ϊ0�Ľڵ���ջ
	for (int i = 0; i < InDegree.size(); i++){
		if (InDegree[i] == 0)
			S.push(i);
	}
	//�������,��������
	while (!S.empty()){
		int node = S.top();
		S.pop();
		//������ڵ������ĵ�
		for (auto i : Adj[node]){
			InDegree[i.first]--;//���½ڵ�������Ϣ
			//���Ϊ0��,����������
			if (InDegree[i.first] == 0)
				S.push(i.first);
		}
		//node��Ϊ�����ڵ�
		res.push_back(node);
	}
	return res;
}

//��ʼ�����·����
//n�ǽڵ���,s��Դ��
vector<Node> InitializeSingleSource(int n, int s){
	vector<Node> res(n);
	res[s].d = 0;
	return res;
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
		cout << "-->" << v;
	}
}

//�ɳڲ���
//�������·����, �����<u, v>������Ȩֵ
void RELAX(vector<Node>& SPT, int u, int v, int w){
	if (SPT[v].d > SPT[u].d + w){
		SPT[v].d = SPT[u].d + w;
		SPT[v].parent = u;
	}
}

//DAG�㷨
//SortRes����������֮��Ľڵ�����, Adj���ڽӱ�, SPT�����·����, s��Դ��
void DAG_Shortest_Paths(vector<int>& SortRes, vector<vector<pair<int, int>>>& Adj, vector<Node> SPT, int s){
	for (int u : SortRes){
		for (auto v : Adj[u]){
			RELAX(SPT, u, v.first, v.second);
		}
	}
	cout << "�������·��Ϊ��" << endl;
	for (int i = 0; i < SPT.size(); i++){
		if (i != s){
			Print_Path(SPT, s, i);
			cout << " ���·��ȨֵΪ:" << SPT[i].d << endl;
		}
	}
}

int main(){
	cout << "����ڵ���������ߵĸ�����";
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int, int>>> Adj(n);//�ڽӱ�
	vector<int> InDegree(n, 0);//����ڵ�����
	cout << "��������ߵ����,�յ�,Ȩֵ(ÿ����Ȩֵ��Ҫ����100,·�����Ȳ�Ҫ����100000,�ڵ��Ŵ�0��ʼ)��" << endl;
	int input1, input2, input3;
	for (int i = 0; i < m; i++){
		cin >> input1 >> input2 >> input3;
		Adj[input1].push_back(make_pair(input2, input3));
		InDegree[input2]++;
	}
	vector<int> SortRes = Topological_Sort(Adj, InDegree);
	cout << "����Դ�㣺";
	int s; cin >> s;
	vector<Node> SPT = InitializeSingleSource(n, s);
	DAG_Shortest_Paths(SortRes, Adj, SPT, s);
	system("pause");
	return 0;
}