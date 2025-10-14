#include <iostream>
#include <vector>
using namespace std;

class MSD
{
private:
    int R = 256;             // 基数
    int M = 15;              // 小数组切换阈值
    vector<string> arr, aux; // 辅助数组

    int charAt(const string &s, int d)
    {
        if (d < s.size())
            return s[d];
        else
            return -1;
    }

public:
    MSD(const vector<string> &a) : arr(a), aux(a.size())
    {
        for (string &s : arr)
        {
            cout << s << " ";
        }
        cout << endl;
        sort(arr);
        for (string &s : arr)
        {
            cout << s << " ";
        }
        cout << endl;
    }

    ~MSD() {}

    void sort(vector<string> &a)
    {
        int N = a.size();
        sort(a, 0, N - 1, 0);
    }

    // 以第d个字符为键将a[lo]至a[hi]排序
    void sort(vector<string> &a, int lo, int hi, int d)
    {
        if (hi <= lo + M)
        {
            // 小数组使用插入排序
            for (int i = lo; i <= hi; i++)
                for (int j = i; j > lo && a[j].substr(d) < a[j - 1].substr(d); j--)
                    swap(a[j], a[j - 1]);
            return;
        }

        vector<int> count(R + 2, 0); // 频率数组
        for (int i = lo; i <= hi; i++)
            count[charAt(a[i], d) + 2]++;

        for (int r = 0; r < R + 1; r++){
            count[r + 1] += count[r]; // 计算索引
        }

        for (int i = lo; i <= hi; i++) {
            aux[count[charAt(a[i], d) + 1]++] = a[i];
        }

        for (int i = lo; i <= hi; i++) {
            a[i] = aux[i - lo];
        }

        for (int r = 0; r < R; r++) 
        // 递归以每个字符为开头的字串进行排序
            sort(a, lo + count[r], lo + count[r + 1] - 1, d + 1);
    }  
};

int main()
{
    vector<string> arr = {
        "she", "sells", "seashells", "by", "the", "seashore",
        "shells", "shore", "sea", "hello", "world", "algorithm",
        "sort", "string", "data", "structure", "example", "test",
        "random", "words", "apple", "banana", "orange", "grape",
        "pear", "peach", "melon", "kiwi", "plum", "berry"
    };
    MSD msd(arr);
    return 0;
}
