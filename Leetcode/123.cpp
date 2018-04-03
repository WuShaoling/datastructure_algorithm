#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        vector<int> f1(n);  // ��ʾ��[0,i]�ڽ��������������ܻ�õ����profit
        vector<int> f2(n);  // ��ʾ��[i, n-1]�ڽ��������������ܻ�õ����profit  �����Ϊmax(f1[i]+f2[i])

        int minPrice = prices[0];

        for(int i = 1; i < n; i++) {
            minPrice = min(minPrice, prices[i]);
            f1[i] = max(f1[i-1], prices[i]- minPrice);
        }

        int maxPrice = prices[n-1];
        for(int i = n-2; i >=0; i--) {    // ����Ҫ�Ӻ���ǰ����
            maxPrice = max(maxPrice, prices[i]);
            f2[i] = max(f2[i+1], maxPrice - prices[i]);
        }
        int maxResult = 0;
        for(int i = 0; i < n; i++)
            maxResult = max(maxResult, f1[i]+f2[i]);
        return maxResult;
    }
};

int main() {
    return 0;
}


