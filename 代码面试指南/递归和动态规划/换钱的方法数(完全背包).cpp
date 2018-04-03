#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

///��ͨ��ʽ
int coinsCount(vector<int> arr, int aim){
    if(0==arr.size() || aim<0)
        return 0;
    int n = arr.size();
    int dp[n][aim+1];
    memset(dp, 0, sizeof(dp));
    for(int i=0; i<n; i++)///aim=0ʱ����Ǯ�ķ���ֻ��1�֣�������
        dp[i][0] = 1;
    for(int i=1; arr[0]*i<=aim; i++)
        dp[0][arr[0]*i]=1;
    for(int i=1; i<n; i++){
        for(int j=1; j<=aim; j++){
            dp[i][j] = dp[i-1][j];
            if(arr[i] <= j)
                dp[i][j] += dp[i][j-arr[i]];
        }
    }
    return dp[n-1][aim];
}

///�ڴ��Ż�
int coinsCount1(vector<int> arr, int aim){
    if(0==arr.size() || aim<0)
        return 0;
    int n = arr.size();
    int dp[aim+1];
    memset(dp, 0, sizeof(dp));
    for(int i=0; arr[0]*i<=aim; i++)
        dp[arr[0]*i]=1;
    for(int i=1; i<n; i++){
        for(int j=1; j<=aim; j++){
            if(arr[i] <= j)
                dp[j] += dp[j-arr[i]];
        }
    }
    return dp[aim];
}

int main(){
    int n;
    while(cin >> n){
        vector<int> arr;
        for(int i=1; i<=n; i++){
            arr.push_back(i);
        }
        cout << coinsCount(arr, n) << endl;
    }
    return 0;
}
