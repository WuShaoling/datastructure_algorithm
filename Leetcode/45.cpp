#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int ret = 0;//��ǰ����
        int last = 0;//��һ���ɴ���Զ����
        int cur = 0;//��ǰһ���ɴ���Զ��
        for (int i = 0; i < nums.size(); ++i) {
            //��Ҫ�����´���Ծ�������last�͵�ִ�е�����ret
            if (i > last) {
                last = cur;
                ++ret;
            }
            //��¼��ǰ�ɴ����Զ��
            cur = max(cur, i+nums[i]);
        }
        return ret;
    }
};

int main() {
    Solution s;
    vector<int> vv;
    vv.push_back(2);
    vv.push_back(3);
    vv.push_back(1);
    vv.push_back(1);
    vv.push_back(4);
    cout << s.jump(vv);
}

