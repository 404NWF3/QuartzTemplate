#include <iostream>
using namespace std;

class KMP {
private:
    string pat;
    int **dfa;
    int M, R = 256;
public:
    KMP(const string &pat);
    ~KMP();
    int search(const string &txt);
    void showDFA() {
        for (int j = 0; j < M; ++j) {
            cout << "j=" << j << ": ";
            for (int i = 0; i < R; ++i) {
                if (dfa[i][j] != 0) {
                    cout << "'" << (char)i << "':" << dfa[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
    void searchVisualized(const string &txt) {
        int N = txt.length();
        int i, j;
        cout << "Text: " << txt << endl;
        cout << "Pattern: " << pat << endl;
        for (i = 0, j = 0; i < N && j < M; i++) {
            cout << "i=" << i << ", j=" << j << ": ";
            for (int k = 0; k < i; k++) cout << " ";
            cout << txt[i] << endl;
            j = dfa[txt[i]][j];
        }
        if (j == M) {
            cout << "Pattern found at index " << i - M << endl;
        } else {
            cout << "Pattern not found" << endl;
        }
    }
};

KMP::KMP(const string& pat){
    this->pat = pat;
    int M = pat.length();
    dfa = new int*[R];
    for(int i = 0; i < R; ++i)
        dfa[i] = new int[M]();
    dfa[pat[0]][0] = 1;
    for (int X = 0, j = 1; j < M; j++) {
        for (int c = 0; c < R; c++) 
            dfa[c][j] = dfa[c][X];   // 复制匹配失败情况下的值
        dfa[pat[j]][j] = j + 1;     // 设置匹配成功情况下的值
        X = dfa[pat[j]][X];         // 更新重启状态
    }
    this->M = M;
    showDFA();   
}

KMP::~KMP(){
    for(int i = 0; i < R; ++i)
        delete[] dfa[i];
    delete[] dfa;
}

int KMP::search(const string &txt){
    int N = txt.length();
    int i, j;
    for (i = 0, j = 0; i < N && j < M; i++) {
        j = dfa[txt[i]][j];
    }
    if (j == M) return i - M; // 找到匹配
    return -1;                // 未找到匹配
}

int main() {
    string txt = "BCBAABACAABABACAA";
    string pat = "ABABAC";
    KMP kmp(pat);
    // int result = kmp.search(txt);
    // if (result != -1) {
    //     cout << "Pattern found at index " << result << endl;
    // } else {
    //     cout << "Pattern not found" << endl;
    // }

    kmp.searchVisualized(txt);
    return 0;
}