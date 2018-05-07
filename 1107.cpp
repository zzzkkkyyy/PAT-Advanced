#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <cstdio>
using namespace std;
class Cluster
{
private:
    int people_num;
    map<int, vector<int> > interest;
    int *father, *cnt;
public:
    void init()
    {
        cin >> people_num;
        cnt = new int[people_num];
        for (int i = 0; i < people_num; i++)
        {
            cnt[i] = 0;
            int total, temp;
            //char ch;
            scanf("%d:", &total);
            //cin >> total >> ch;
            for (int j = 0; j < total; j++)
            {
                scanf(" %d", &temp);
                interest[temp - 1].push_back(i);
            }
            //cin.clear();
        }
        father = new int[people_num];
        for (int i = 0; i < people_num; i++)
        {
            father[i] = i;
        }
        for (map<int, vector<int> >::iterator it = interest.begin(); it != interest.end(); it++)
        {
            if (it->second.size() >= 2)
            {
                for (vector<int>::iterator itv = it->second.begin(); itv != it->second.end(); itv++)
                {
                    Union(*itv, *(it->second.begin()));
                }
            }
        }
    }
    int findFather(int node)
    {
        while (node != father[node])
        {
            node = father[node];
        }
        return node;
    }
    void Union(int node1, int node2)
    {
        father[findFather(node1)] = findFather(node2);
    }
    int process()
    {
        set<int> s;
        for (int i = 0; i < people_num; i++)
        {
            int temp = findFather(i);
            s.insert(temp);
            cnt[temp]++;
        }
        cout << s.size() << endl;
        sort(cnt, cnt + people_num, greater<int>());
        for (int i = 0; i < people_num && cnt[i] != 0; i++)
        {
            if (i)
                cout << " ";
            cout << cnt[i];
        }
        cout << endl;
    }
};
int main(void)
{
    Cluster c;
    c.init();
    c.process();
    return 0;
}