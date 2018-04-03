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
	int cur=0;
	for(int i=1; i<n; i++)
		if(v[cur] != v[i])
			v[++cur]=v[i];
	n = ++cur;
	//������������Ѿ�û���ظ���Ԫ�� 
	int temp_sum, i, j;
	for(int k=0; k<n-1; k++){
		i=k+1, j=n-1;
		while(i <= j){
			temp_sum = v[i] + v[j] + v[k];
			if(temp_sum == target)//��ȣ�i��jΪһ��⣬����±� 
				cout << v[k] << " " << v[i++] << " " << v[j--] << endl; 
			else if(temp_sum > target)//����target��j���� 
				j--;
			else//С��target��i���� 
				i++;
		}
	}
	return 0;
}
