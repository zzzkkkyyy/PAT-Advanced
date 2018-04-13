#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef struct element
{
    int value;
    int index;
    int left_child;
    int right_child;
}element;
class Array
{
private:
    vector<element> data;
public:
    Array(int num)
    {
        for (int i = 0; i < num; i++)
        {
            element ele = {0, i, -1, -1};
            data.push_back(ele);
        }
    }
    ~Array()
    {
        data.clear();
    }
    void renew(int index, int left, int right)
    {
        data[index].left_child = left;
        data[index].right_child = right;
    }
    int insertValue(int *source, int index)
    {
        if (index == -1)
            return 0;
        int pre_count = insertValue(source, data[index].left_child);
        data[index].value = source[pre_count];
        int after_count = insertValue(source + pre_count + 1, data[index].right_child);
        //cout << pre_count << '+' << data[index].value << '+' << after_count << endl;
        return pre_count + after_count + 1;
    }
    void print()
    {
        queue<int> q;
        q.push(0);
        while (!(q.empty()))
        {
            if (q.front() != 0)
            {
                cout << " ";
            }
            cout << data[q.front()].value;
            if (data[q.front()].left_child != -1)
                q.push(data[q.front()].left_child);
            if (data[q.front()].right_child != -1)
                q.push(data[q.front()].right_child);
            q.pop();
        }
        cout << endl;
    }
};
int main(void)
{
    int total_num;
    cin >> total_num;
    Array array(total_num);
    for (int i = 0; i < total_num; i++)
    {
        int left, right;
        cin >> left >> right;
        array.renew(i, left, right);
    }

    int *source = new int[total_num];
    for (int i = 0; i < total_num; i++)
    {
        cin >> source[i];
    }
    sort(source, source + total_num, less<int>());
    
    array.insertValue(source, 0);
    array.print();
    return 0;
}