#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
	int n;
	cin >> n;
	vector<int> v(n);
	for(int i=0; i<n; i++)
		cin >> v[i];
	int target;
	cin >> target;
	sort(v.begin(), v.end());
	//������ظ�Ԫ�أ����ܻ�����ظ��⣬��Ҫȥ���ظ���Ļ�������ȥ���������ظ���Ԫ�� 
	int cur=0;
	for(int i=1; i<n; i++)
		if(v[cur] != v[i])
			v[++cur]=v[i];
	n = ++cur;
	//������������Ѿ�û���ظ���Ԫ�� 
	int temp_sum;
	for(int i=0, j=n-1; i<=j;){
		temp_sum = v[i] + v[j];
		if(temp_sum == target){//��ȣ�i��jΪһ��⣬����±� 
			cout << v[i] << " " << v[j] << endl; 
			i++, j--;
		}else if(temp_sum > target){//����target��j���� 
			j--;
		}else{//С��target��i���� 
			i++;
		}
	}
	return 0;
}
