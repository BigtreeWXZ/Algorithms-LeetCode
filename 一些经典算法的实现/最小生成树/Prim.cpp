#include<iostream>
#include<vector>
#include<queue>
using namespace std;

//������ڽӱ��еĽڵ�
struct Node{
	int id;//��ǰ��ı��
	int key;//�ߵ�Ȩֵ
	//���췽��
	Node(int x, int k) :id(x), key(k){}
};

//Prim�㷨ʵ��,startΪ��ʼ�ڵ���
int Prim(vector<vector<Node>>& edges, int start){
	int n = edges.size();//�ڵ���
	vector<bool> visited(n, false);//�ڵ���ʱ�ʶ
	vector<int> path;//�Ѿ�������Ľڵ�
	path.push_back(start);
	visited[start] = true;
	int nodeSum = 1, keySum = 0;
	int end = -1;
	while (nodeSum < n){
		int minKey = INT_MAX;
		//�����Ѿ�������Ľڵ�
		for (int now : path){
			//������û�д���Ľڵ�
			for (auto next : edges[now]){
				//ѡ������path��path֮�����е�����б���Ȩֵ��С��һ��
				if (!visited[next.id] && next.key < minKey){
					minKey = next.key;
					start = now;
					end = next.id;
				}
			}
		}
		nodeSum++;
		visited[end] = true;
		path.push_back(end);
		cout << start << "----" << end << " " << minKey << endl;
		keySum += minKey;
	}
	return keySum;
}
int main(){
	int n, m;//����,����
	cout << "����������ͱ�����";
	cin >> n >> m;
	vector<vector<Node>> edges(n);//�ڽӱ�
	cout << "������ߵ������˵�(��Ŵ�0��ʼ)��Ȩֵ:" << endl;
	for (int i = 0; i < m; i++){
		int a, b, c;
		cin >> a >> b >> c;
		Node tmp = Node(b, c);
		edges[a].push_back(tmp);
		tmp = Node(a, c);
		edges[b].push_back(tmp);
	}
	cout << "���뿪ʼ�ڵ㣺";
	int start; cin >> start;
	int res = Prim(edges, start);
	cout << "��СȨֵ��Ϊ��" << res << endl;
	system("pause");
	return 0;
}