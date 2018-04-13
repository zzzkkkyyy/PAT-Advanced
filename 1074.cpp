#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
class List
{
private:
    int startAdd;
    int totalNum, subNum;
    map<int, int> begin2Value;
    map<int, int> value2Begin;
    map<int, int> value2End;
    vector<int> list;
    vector<int> valueList;
public:
    void init()
    {
        scanf("%d %d %d", &startAdd, &totalNum, &subNum);
        //cin >> startAdd >> totalNum >> subNum;
        for (int i = 0; i < totalNum; i++)
        {
            int start, end;
            int v;
            scanf("%d %d %d", &start, &v, &end);
            //cin >> start >> v >> end;
            value2Begin[v] = start;
            value2End[v] = end;
            begin2Value[start] = v;
        }
    }
    void process()
    {
        int start = startAdd;
        int temp;
        if (totalNum % subNum == 0)
            temp = totalNum / subNum;
        else
            temp = totalNum / subNum + 1;
        for (int i = 0; i < temp; i++)
        {
            int flag = true;
            for (int j = 0; j < subNum; j++)
            {
                valueList.push_back(begin2Value[start]);
                start = value2End[begin2Value[start]];
                if (j < subNum - 1 && start == -1)
                {
                    flag = false;
                    break;
                }
            }
            if (flag == true)
                reverse(valueList.begin() + i * subNum, valueList.end());
        }
    }
    void print()
    {
        for (vector<int>::iterator it = valueList.begin(); it != valueList.end(); it++)
        {
            if (it != valueList.begin())
            {
                printf(" %05d\n", value2Begin[*it]);
                //cout << ' ' << value2Begin[*it] << endl;
            }
            printf("%05d %d", value2Begin[*it], *it);
            //cout << value2Begin[*it] << ' ' <<  *it;
        }
        printf(" -1\n");
        //cout << ' ' << -1 << endl;
    }
};
int main(void)
{
    List l;
    l.init();
    l.process();
    l.print();
    return 0;
}