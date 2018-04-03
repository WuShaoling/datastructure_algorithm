#include<iostream>
#include<vector>

using namespace std;

vector<vector<char> > res;///�������ս��
vector<char> ans;///�����м���

void show() {
    for(int i=0; i<res.size(); i++) {
        for(int j=0; j<res[i].size(); j++)
            cout << res[i][j] << " ";
        cout << endl;
    }
}

void dfs(int step, vector<char> &vv) {
    res.push_back(ans);
    for(int i = step; i < vv.size(); i++) {
        ans.push_back(vv[i]);
        dfs(i + 1, vv);
        ans.pop_back();
    }
}

int main() {
    vector<char> vv;
    for(int i=0; i<5; i++)
        vv.push_back('a' + i);
    dfs(0, vv);
    show();
    return 0;
}

