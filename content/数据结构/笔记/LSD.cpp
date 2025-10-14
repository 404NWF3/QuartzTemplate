#include <iostream>
#include <vector>
using namespace std;

class LSD
{
public:
    LSD(vector<string> &arr)
    {
        for (string &s : arr)
        {
            cout << s << " ";
        }
        cout << endl;

        sort(arr, arr[0].size());

        for (string &s : arr)
        {
            cout << s << " ";
        }
        cout << endl;
    }

    ~LSD()
    {
    }

    void sort(vector<string> &arr, int w)
    {
        int N = arr.size();    // 数组元素个数
        int R = 256;           // 基数
        vector<string> aux(N); // 辅助数组

        for (int d = w - 1; d >= 0; d--)
        {                                // 从最右侧字符开始排序
            vector<int> count(R + 1, 0); // 计数数组
            for (string s : arr)
                count[s[d] + 1]++; // 计算频率
            // s[d] + 1 是为了让索引从1开始，方便计算

            for (int r = 0; r < R; r++)
                count[r + 1] += count[r]; // 计算索引

            for (string s : arr)
                aux[count[s[d]]++] = s; // 根据count[s[d]]的位置放入aux数组 s[d]之后+1

            for (int l = 0; l < N; l++)
                arr[l] = aux[l]; // 回写到arr数组
        }
    }
};

int main()
{
    vector<string> arr = {"she", "sells", "seashells", "by", "the", "seashore"};
    LSD lsd(arr);
    return 0;
}
