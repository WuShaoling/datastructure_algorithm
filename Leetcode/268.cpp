#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    ///����1,�������
    int missingNumber(vector<int>& nums) {
        int result = 0;
        for(int i=0; i<nums.size(); i++) {
            result ^= (i+1)^nums[i];
        }
        return result;
    }

    ///����2�����
    int missingNumber2(vector<int>& nums) {
        int result = 0;
        for(int i=0; i<nums.size(); i++)
            result += nums[i];
        int n = nums.size();
        int sum = n*(n+1)/2;
        return sum - result;
    }

    ///����3�����ַ�
    int missingNumber3(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int begin = 0, end = nums.size();
        while(begin != end) {
            int mid = begin+(end-begin)/2;
            if(mid < nums[mid])
                end = mid;
            else
                begin = mid+1;
        }
        return end;
    }
};

int main() {
    Solution s;
    return 0;
}

