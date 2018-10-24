#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

//�ж�Pk�ǲ���Pq+a�ĺ�׺(�±��1��ʼ)
bool isPostfix(string &P, int k, int q, char a){
	//�մ���ÿһ���ַ����ĺ�׺
	if (k == 0)
		return true;
	string target = P.substr(0, q) + a;
	//����Ƚ�
	for (int i = k - 1; i >= 0; i--){
		if (P[i] != target.back())
			return false;
		target.pop_back();
	}
	return true;
}

//���㲢����ת�ƺ���,P��ģʽ��,A���ַ���
vector<unordered_map<char, int>> Compute_Transition(string &P, string &A){
	int m = P.size();
	vector<unordered_map<char, int>> transition(m + 1);
	for (int q = 0; q <= m; q++){
		for (char a : A){
			int k = min(m, q + 1);// 1<= k <= m
			//��transition[q][a]��Ϊ����Pk��Pq+a��׺������k
			while (!isPostfix(P, k, q, a))
				k--;
			transition[q][a] = k;
		}
	}
	return transition;
}

//ƥ�亯��,T���ı���, transition��ת�ƺ���, m���Զ�����Ψһ����״̬
void Finite_Automaton_Matcher(string &T, vector<unordered_map<char, int>>& transition, int m){
	bool flag = false;//��־�Ƿ�ƥ��ɹ�
	int n = T.size();
	int q = 0;//q�ǳ�ʼ״̬
	for (int i = 0; i < n; i++){
		//�õ�T[i]��״̬
		q = transition[q][T[i]];
		//q�ǽ���״̬,Pƥ��ɹ�
		if (q == m){
			cout << "Pattern occurs with shift: " << i - m + 1 << endl;
			flag = true;
		}
	}
	if (!flag)
		cout << "Not Fount" << endl;
}

int main(){
	string A = "abc", P = "ababaca", T = "bacbababacaababcababacaaba";
	vector<unordered_map<char, int>> transition_map = Compute_Transition(P, A);
	cout << "ת�ƺ���Ϊ��" << endl;
	for (int i = 0; i < transition_map.size(); i++){
		for (char a : A){
			cout << transition_map[i][a] << " ";
		}
		cout << endl;
	}
	cout << endl;
	Finite_Automaton_Matcher(T, transition_map, P.size());
	system("pause");
}