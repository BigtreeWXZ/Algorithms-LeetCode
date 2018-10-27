#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Edge{
	int u, v;//·��������
	int w;//·����Ȩ��
	Edge(int a, int b, int c) : u(a), v(b), w(c){}
};

//��Ȩ�ش�С����Ա����� 
bool cmp(const Edge& a, const Edge& b){
	return a.w < b.w;
}

//Ϊ�㴴�첻�ཻ����
//��������vector<pair<int, int>> parent, parent[i].first��ʾ��i�����Ƚڵ�,parent[i].second��ʾ��isuoz���ϵĴ�С
vector<pair<int, int>> MakeSet(int n){
	vector<pair<int, int>> parent;
	for (int i = 0; i < n; i++){
		parent.push_back(make_pair(i, 1));
	}
	return parent;
}

//����x���ڼ��ϵ�����
int FindParent(vector<pair<int, int>>& parent, int x){
	while (x != parent[x].first)
		x = parent[x].first;
	return x;
}

//��������ͬ���ȵ����ϲ�Ϊͬһ������
void Union(vector<pair<int, int>>& parent, int x, int y){
	//�Ѽ���С�Ĺ鵽�������,������ѯʱ���Լ��ٲ�ѯ����
	if (parent[x].second > parent[y].second){
		parent[y].first = x;
		parent[x].second += parent[y].second;
	}
	else{
		parent[x].first = y;
		parent[y].second += parent[x].second;
	}
}

//kruskal�㷨
vector<Edge> Kruskal(vector<Edge>& edges, int n){
	vector<Edge> res;
	vector<pair<int, int>> parent = MakeSet(n);
	for (auto e : edges){
		int x = FindParent(parent, e.u), y = FindParent(parent, e.v);
		//��ǰ�ߵļ��벻�ṹ�ɻ�·
		if (x != y){
			res.push_back(e);
			Union(parent, x, y);
			if (res.size() == n - 1)
				break;
		}
	}
	return res;
}

int main(){
	int n, m;
	cout << "����������ͱ�����";
	cin >> n >> m;
	vector<Edge> edges, res;
	cout << "������ߵ������˵�(�˵��Ŵ�0��ʼ)��Ȩֵ��" << endl;
	for (int i = 0; i < m; i++){
		int a, b, c;
		cin >> a >> b >> c;
		Edge e = Edge(a, b, c);
		edges.push_back(e);
	}
	sort(edges.begin(), edges.end(), cmp);
	res = Kruskal(edges, n);
	cout << "���Ϊ��" << endl;
	int sum = 0;
	for (auto e : res){
		cout << e.u << " " << e.v <<" "<< e.w << endl;
		sum += e.w;
	}
	cout << "��СȨֵ��Ϊ��" << sum << endl;
	system("pause");
	return 0;
}