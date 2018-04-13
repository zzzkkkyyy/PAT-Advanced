#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#define EMPTYSTR "0"
using namespace std;
string Find(string x, map<string, string> &fore_node)
{
    if (x == fore_node[x])
        return x;
    return Find(fore_node[x], fore_node);
}
void Union(string x, string y, map<string, string> &fore_node)
{
    string head_x = Find(x, fore_node), head_y = Find(y, fore_node);
    if (head_x != head_y)
    {
        fore_node[head_y] = head_x;
    }
}
typedef struct gang
{
    string max_name;
    int max_time;
    int num;
}Gang;
bool compare(const Gang &g1, const Gang &g2)
{
    return (g1.max_name < g2.max_name);
}
int main(void)
{
    int call_num, threshold;
    cin >> call_num >> threshold;
    map<string, int> call_time;
    map<string, string> fore_node;
    map<string, int> road_sum_time;
    vector<string> head;
    vector<Gang> gang;
    set<string> name;

    for (int i = 0; i < call_num; i++)
    {
        string node1, node2;
        int time;
        vector<string> head;
        cin >> node1 >> node2 >> time;
        name.insert(node1);
        name.insert(node2);
        
        if (fore_node.count(node1) == 0)
            fore_node[node1] = node1;
        if (fore_node.count(node2) == 0)
            fore_node[node2] = node2;
        Union(node1, node2, fore_node);
        string temp = Find(node1, fore_node);
        if (road_sum_time.count(temp) == 0)
            road_sum_time[temp] = time;
        else
            road_sum_time[temp] += time;

        if (call_time.count(node1) == 0)
            call_time[node1] = time;
        else
            call_time[node1] += time;
        if (call_time.count(node2) == 0)
            call_time[node2] = time;
        else
            call_time[node2] += time;
    }
    for (set<string>::iterator it = name.begin(); it != name.end(); it++)
    {
        string innertemp = Find(*it, fore_node);
        //cout << *it << endl;
        //cout << "head: " << Find(*it, fore_node) << endl;
        //cout << "amount: " << call_time[*it] << endl;
        if (count(head.begin(), head.end(), innertemp) == 0)
        {
            head.push_back(innertemp);
            Gang temp = {*it, call_time[*it], 1};
            gang.push_back(temp);
        }
        else
        {
            for (int i = 0; i < head.size(); i++)
            {
                if (innertemp == head[i])
                {
                    gang[i].num++;
                    if (call_time[*it] > gang[i].max_time)
                    {
                        gang[i].max_name = *it;
                        gang[i].max_time = call_time[*it];
                    }
                }
            }
        }
    }
    int count = 0;
    for (int i = 0; i < gang.size(); i++)
    {
        count += (gang[i].num > 2 && road_sum_time[head[i]] > threshold);
    }
    cout << count << endl;
    sort(gang.begin(), gang.end(), compare);
    for (int i = 0; i < gang.size(); i++)
    {
        //cout << gang[i].max_name << ' ' << gang[i].num << ' ' << road_sum_time[head[i]] << endl;
        if (gang[i].num > 2 && road_sum_time[head[i]] > threshold)
        {
            cout << gang[i].max_name << ' ' << gang[i].num << endl;
        }
    }
    return 0;
}