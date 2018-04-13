#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <queue>
using namespace std;
class Network;
class Node
{
friend class Network;
private:
    int index;
    vector<int> follow_index;
public:
    Node(int i) : index(i)
    {
        follow_index.clear();
    }
    ~Node() {}
    void insertNode(int follow_i)
    {
        follow_index.push_back(follow_i);
    }
};
class Network
{
private:
    vector<Node> user;
    int total_num;
    int query_depth;
    set<int> follower;
public:
    Network(int total, int depth) : total_num(total), query_depth(depth)
    {
        user.clear();
    }
    ~Network() {}
    void insertFollower()
    {
        for (int i = 0; i <= total_num; i++)
        {
            user.push_back(Node(i));
        }
        for (int i = 0; i < total_num; i++)
        {
            int follow_num;
            scanf("%d", &follow_num);
            for (int j = 0; j < follow_num; j++)
            {
                int follow_i;
                scanf("%d", &follow_i);
                user[follow_i].insertNode(i + 1);
            }
        }
    }
    int findFollow(int index, int height)
    {
        int count = 0;
        queue<int> q;
        q.push(index);
        while (count <= query_depth && !q.empty())
        {
            int length = q.size();
            for (int i = 0; i < length; i++)
            {
                int up = q.front();
                q.pop();
                follower.insert(up);
                if (count != (query_depth))
                    for (vector<int>::iterator it = user[up].follow_index.begin(); it != user[up].follow_index.end(); it++)
                    {
                        if (follower.count(*it) == 0)
                            q.push(*it);
                    }
            }
            count++;
        }
        return follower.size() - 1;
    }
    void clearSet(int index)
    {
        follower.clear();
        follower.insert(index);
    }
};
int main(void)
{
    int total, depth;
    scanf("%d %d", &total, &depth);
    Network net(total, depth);
    net.insertFollower();

    int query_num;
    scanf("%d", &query_num);

    for (int i = 0; i < query_num; i++)
    {
        int query;
        scanf("%d", &query);
        net.clearSet(query);
        printf("%d\n", net.findFollow(query, 0));
    }

    return 0;
}