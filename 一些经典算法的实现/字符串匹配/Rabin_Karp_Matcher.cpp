#include<iostream>
#include<string>

using namespace std;

//�ж�P��T�Ƿ����,��Ⱦͷ���true
bool isSame(string P, string T){
	for (int i = 0; i < P.size(); i++){
		if (P[i] != T[i])
			return false;
	}
	return true;
}

//T���ı�, P��ģʽ��, d���ֵ�Ĵ�С, q������
void Rabin_Karp_Matcher(string T, string P, int d, int q){
	int n = T.size();
	int m = P.size();
	//����h
	int h = 1;
	for (int i = 0; i < m - 1; i++)
		h = (h * d) % q;
	int p = 0, t = 0;
	//���û��ɷ������P��T��Ӧ��d����ֵ
	for (int i = 0; i < m; i++){
		p = (d * p + (P[i] - 'a')) % q;
		t = (d * t + (T[i] - 'a')) % q;
	}
	//��ʼƥ��
	for (int s = 0; s <= n - m; s++){
		//����ʽ����
		if (p == t){
			//�ж�s�������Ч����һ��α���е�
			if (isSame(P, T.substr(s, m)))
				cout << "Pattern occurs with shift " << s << endl;
		}
		//������һ��t
		if (s < n - m){
			t = (d * (t - (T[s] - 'a') * h) + (T[s + m] - 'a')) % q;
			//��С��0�������������
			if (t < 0)
				t += q;
		}
	}
}

int main(){
	string T = "fdstabcdesgdyfgabdfgsabcdehfd";
	string P = "abcde";
	Rabin_Karp_Matcher(T, P, 26, 29);
	system("pause");
}