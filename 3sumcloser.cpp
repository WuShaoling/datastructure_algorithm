#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n=nums.size(), close=0x7fffffff;
		for(int k=0; k<n; k++){
			while(k>0 && k<n && nums[k] == nums[k-1])
				k++;
			int i=k+1, j=n-1;
			while(i < j){
				int sum = nums[i] + nums[j] + nums[k];
				if(abs(sum - target) < close)
					close = abs(sum - target);
				if(sum == target){//��ȣ�i��jΪһ��⣬����±� 
					while(i<j && nums[i] == nums[i-1])
						i++;
					while(i<j && nums[j] == nums[j+1])
						j--;
				}else if(sum > 0){//����target��j���� 
					j--;
				}
				else{//С��target��i���� 
					i++;
				}
			}
		}
		return close;
    }
};

int main(){
}
