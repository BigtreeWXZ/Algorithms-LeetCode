#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

vector<int> Compute_Prefix(string& P){
	int m = P.size();
	//ǰ׺����,P[q] = k��ʾPq�����׺������ǰ׺Pk
	vector<int> next(m);
	next[0] = 0;
	int k = 0;//��ʼ��0
	for (int q = 1; q < m; q++){
		//���Ƽ���next[q]
		while (k > 0 && P[q] != P[k])
			k = next[k-1];
		//Pk��չ��Pk+1���õ�Pq�����׺
		if (P[q] == P[k])
			k++;
		next[q] = k;
	}
	return next;
}

void KMP_Matcher(string& T, string& P){
	int n = T.size();
	int m = P.size();
	vector<int> next = Compute_Prefix(P);
	//��ӡnext
	for (int i = 0; i < m; i++)
		cout << next[i] << " ";
	cout << endl;
	int q = 0;//�Ѿ�ƥ����ַ���
	for (int i = 0; i < n; i++){
		//���ֲ�ƥ��,�ص�֮ǰ��q
		while (q > 0 && P[q] != T[i])
			q = next[q-1];
		//ƥ�����µ��ַ�
		if (P[q] == T[i])
			q ++;
		if (q == m){
			cout << "Pattern occurs with shift: " << i - m + 1 << endl;
			//����q
			q = next[m-1];
		}
	}
}

int main(){
	string P = "ababaca", T = "bacbababacaababcababacaaba";
	vector<int> test = Compute_Prefix(P);
	KMP_Matcher(T, P);
	system("pause");
}