#include <iostream>
#include <map>
using namespace std;

int main(void)
{
    int TotalNum, NonLeafNum;
    cin >> TotalNum >> NonLeafNum;
    bool *leaf = new bool[TotalNum];
    int *height = new int[TotalNum];
    map<int, int> Count;
    int max = 0;
    for (int i = 0; i < TotalNum; i++)
    {
        leaf[i] = true;
        height[i] = 0;
    }
    for (int i = 0; i < NonLeafNum; i++)
    {
        int id, ChildNum;
        cin >> id >> ChildNum;
        id--;
        leaf[id] = false;
        for (int j = 0; j < ChildNum; j++)
        {
            int tempchild;
            cin >> tempchild;
            tempchild--;
            height[tempchild] = height[id] + 1;
            if (max < height[tempchild])
            {
                max = height[tempchild];
            }
        }
    }
    for (int i = 0; i < TotalNum; i++)
    {
        if (leaf[i] == true)
        {
            if (Count.count(height[i]) == 0)
            {
                Count[height[i]] = 1;
            }
            else
            {
                Count[height[i]]++;
            }
        }
    }
    for (int i = 0; i <= max; i++)
    {
        if (i)
        {
            cout << " ";
        }
        if (Count.count(i) != 0)
        {
            cout << Count[i];
        }
        else
        {
            cout << 0;
        }
    }
    return 0;
}