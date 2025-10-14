#include <iostream>
#include <vector>
using namespace std;

class Quick3string {
private:
    int charAt(const string &s, int d) {
        if (d < s.size())
            return s[d];
        else
            return -1;
    }
    void exch(vector<string> &a, int i, int j) {
        swap(a[i], a[j]);
    }
    void sort(vector<string> &a, int lo, int hi, int d);

public:
    Quick3string(const vector<string> &a) {
        vector<string> arr = a;
        for (string &s : arr) {
            cout << s << " ";
        }
        cout << endl;
        sort(arr);
        for (string &s : arr) {
            cout << s << " ";
        }
        cout << endl;
    }
    ~Quick3string() {}
    void sort(vector<string> &a) {
        sort(a, 0, a.size() - 1, 0);
    }
};

void Quick3string::sort(vector<string> &a, int lo, int hi, int d) {
    if (hi <= lo)
        return;
    int lt = lo, gt = hi;
    int v = charAt(a[lo], d);
    int i = lo + 1;
    while (i <= gt) {
        int t = charAt(a[i], d);
        if (t < v)
            exch(a, lt++, i++);
        else if (t > v)
            exch(a, i, gt--);
        else
            i++;
    }
    sort(a, lo, lt - 1, d);
    if (v >= 0)
        sort(a, lt, gt, d + 1);
    sort(a, gt + 1, hi, d);
}

int main() {
    vector<string> arr = {
        "she", "sells", "seashells", "by", "the", "seashore",
        "shells", "shore", "sea", "hello", "world", "algorithm",
        "sort", "string", "data", "structure", "example", "test",
        "random", "words", "apple", "banana", "orange", "grape",
        "pear", "peach", "melon", "kiwi", "plum", "berry"
    };
    Quick3string q3s(arr);
    return 0;
}