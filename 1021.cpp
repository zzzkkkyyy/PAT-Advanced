#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
using namespace std;
class Graph
{
private:
    int *father;
    bool *isVisited;
    int num;
    map<int, vector<int> > graph;
    set<int> deepestRoot;
    
    int maxHeight;
    vector<int> maxh;
public:
    Graph() : maxHeight(0) {}
    void init()
    {
        cin >> num;
        father = new int[num + 1];
        isVisited = new bool[num + 1];
        for (int i = 1; i <= num; i++)
        {
            father[i] = i;
            isVisited[i] = false;
            graph[i].clear();
        }
        for (int i = 0; i < num - 1; i++)
        {
            int node1, node2;
            cin >> node1 >> node2;
            father[node2] = node1;
            graph[node1].push_back(node2);
            graph[node2].push_back(node1);
        }
    }
    int findFather(int index)
    {
        while (index != father[index])
        {
            index = father[index];
        }
        return index;
    }
    bool check()
    {
        set<int> f;
        int flag = 0;
        int count = 0;
        for (int i = 1; i <= num; i++)
        {
            f.insert(findFather(i));
        }
        if (f.size() >= 2)
        {
            cout << "Error: " << f.size() << " components" << endl;
            return false;
        }
        else
            return true;
    }
    void DFS(int start, int total)
    {
        bool allVisited = true;
        for (vector<int>::iterator it = graph[start].begin(); it != graph[start].end(); it++)
        {
            if (isVisited[*it] == false)
            {
                allVisited = false;
                break;
            }
        }
        if (allVisited)
        {
            if (total > maxHeight)
            {
                maxh.clear();
                maxh.push_back(start);
                maxHeight = total;
            }
            else if (total == maxHeight)
            {
                maxh.push_back(start);
            }
            return;
        }
        for (vector<int>::iterator it = graph[start].begin(); it != graph[start].end(); it++)
        {
            if (isVisited[*it] == false)
            {
                isVisited[*it] = true;
                DFS(*it, total + 1);
                isVisited[*it] = false;
            }
        }
    }
    void process()
    {
        if (check() == false)
        {
            return;
        }
        /*
        int height = 0, count;
        for (int i = 1; i <= num; i++)
        {
            count = 0;
            int index = i;
            while (i != father[i])
            {
                i = father[i];
                count++;
            }
            if (count > height)
            {
                deepestRoot.clear();
                deepestRoot.insert(index);
                height = count;
            }
            else if (count == height)
            {
                deepestRoot.insert(index);
            }
            i = index;
        }*/
        isVisited[1] = true;
        DFS(1, 1);
        isVisited[1] = false;
        maxHeight = 0;
        
        isVisited[*(deepestRoot.begin())] = true;
        DFS(*(deepestRoot.begin()), 1);
        for (vector<int>::iterator it = maxh.begin(); it != maxh.end(); it++)
        {
            deepestRoot.insert(*it);
        }
    }
    void print()
    {
        for (set<int>::iterator it = deepestRoot.begin(); it != deepestRoot.end(); it++)
        {
            cout << *it << endl;
        }
    }
};
int main(void)
{
    Graph g;
    g.init();
    g.process();
    g.print();
    return 0;
}