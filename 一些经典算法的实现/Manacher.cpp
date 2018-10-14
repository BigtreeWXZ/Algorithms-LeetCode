#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

//����������Ӵ�
string longestPalindrome(string s) {
	//Manacher�㷨
	if (s.size() == 0 || s.size() == 1)
		return s;
	//�ֽ�s��Ϊ����Ϊ�����Ĵ�
	string news = "&#";
	for (int i = 0; i<s.size(); i++)
	{
		news += s[i];
		news += '#';
	}
	news += '\0';
	int len = news.size();   //�´��ĳ���
	int maxlen = -1;  //��¼������Ӵ��ĳ���
	int maxid = 0; //��¼������Ӵ�������
	vector<int> p(len);  //p[i]��¼��iΪ���ĵ�������Ӵ��İ뾶����maxlen = p[i] - 1
	int id = 0; //��ǰȷ����������
	int mx = 0;  //��ǰ���������ܵ�����ұ߽��±�
	for (int i = 1; i<len; i++)
	{
		if (i < mx)  //i�ڵ�ǰ�Ļ����Ӵ��У�ȷ����iΪ���ĵĹ��ɵ���Ļ��İ뾶
			p[i] = min(mx - i, p[2 * id - i]);  //i����id�ĶԳ��±�Ϊ2*id-1��p[2*id-1]����뾶�Ѿ�ȷ�������ݶԳƣ�p[i]Ӧ��ȡ��С��һ��
		else
			p[i] = 1;  //��������Ϊ�����Ӵ�
		while (news[i - p[i]] == news[i + p[i]])  //ȷ����iΪ���ĵ�����İ뾶
			p[i]++;
		if (i + p[i] > mx)  //������mx�ķ�Χ��Ӧ�ø���mx�ͶԳ�����
		{
			id = i;
			mx = i + p[i];
		}
		if (maxlen < p[i] - 1)
		{
			maxlen = p[i] - 1;
			maxid = i;
		}
	}
	string result = "";
	for (int i = maxid - maxlen; i <= maxid + maxlen; i++)
		if (news[i] != '#')
			result += news[i];
	return result;
}

int main(){
	string str;
	cin >> str;
	cout << longestPalindrome(str) << endl;
	system("pause");
	return 0;
}