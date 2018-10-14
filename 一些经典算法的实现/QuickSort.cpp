#include<iostream>
#include<vector>
#include<stack>

using namespace std;

//���������ԭַ����,ѡ��һ������Ϊ��׼,ǰ�벿�ֶ�С�ڵ�����,��벿�� ������.��󷵻ػ�׼���±�
int Partition(vector<int>& nums, int left, int right){
	int mid = nums[right];
	int i = left - 1;
	for (int j = left; j < right; j++){
		//�ҵ�С�ڵ���mid����
		if (nums[j] <= mid){
			i++;
			//��С�ڵ���mid��������ǰ��
			swap(nums[i], nums[j]);
		}
	}
	//�ѻ�׼ֵ����ǰ�벿��֮��
	swap(nums[i+1], nums[right]);
	return i + 1;
}

//�ݹ�ʵ�ֿ�������
void QuickSort1(vector<int>& nums, int left, int right){
	if (left < right){
		int mid = Partition(nums, left, right);
		//�ݹ�ǰ�벿��
		QuickSort1(nums, left, mid-1);
		//�ݹ��벿��
		QuickSort1(nums, mid+1, right);
	}
}

//�ǵݹ�ʵ��
void QuickSort2(vector<int>& nums, int left, int right){
	if (left < right){
		stack<int> s;
		s.push(left);
		s.push(right);
		while (!s.empty()){
			int r = s.top();
			s.pop();
			int l = s.top();
			s.pop();
			int mid = Partition(nums, l, r);
			//ǰ�벿��
			if (l < mid - 1){
				s.push(l);
				s.push(mid-1);
			}
			//��벿��
			if (r > mid + 1){
				s.push(mid+1);
				s.push(r);
			}
		}
	}
}

int main(){
	vector<int> nums1, nums2;
	cout << "ԭ���飺" << endl;
	for (int i = 0; i < 200; i++){
		int num = rand() % 200;
		cout << num << " ";
		nums1.push_back(num);
		nums2.push_back(num);
	}
	cout << endl;
	cout << "�ݹ�ʵ�֣�" << endl;
	QuickSort1(nums1, 0, nums1.size()-1);
	for (int i = 0; i < 200; i++)
		cout << nums1[i] << " ";
	cout << endl;
	cout << "�ǵݹ�ʵ�֣�" << endl;
	QuickSort2(nums2, 0, nums2.size() - 1);
	for (int i = 0; i < 200; i++)
		cout << nums2[i] << " ";
	cout << endl;
	while (1);
	return 0;
}