#include<iostream>
using namespace std;

int nc = 0;//ͳ�ƺ������ô���
int n;//n�ʺ�
int *C;
int tot = 0;//��ĸ���

void m_search(int cur) {
    nc++;
    if(cur == n)
        tot++;
    else {
        for(int i = 0; i < n; i++) {
            int ok = 1;
            C[cur] = i;
            for(int j = 0; j < cur; j++) {
                if(C[cur] == C[j] || cur - C[cur] == j - C[j] || cur + C[cur] == j + C[j]) {
                    ok = 0;
                    break;
                }
            }
            if(ok)
                m_search(cur + 1);
        }
    }
}

int main() {
    while(cin >> n) {
        tot = 0;
        nc = 0;
        C = new int[n];
        m_search(0);
        delete C;
        cout << nc << endl << tot << endl;
    }
}
