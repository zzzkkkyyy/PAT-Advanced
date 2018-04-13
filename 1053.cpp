#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
bool compare(const vector<int> &routine1, const vector<int> &routine2)
{
    for (int i = 0; i < min(routine1.size(), routine2.size()); i++)
    {
        if (routine1[i] != routine2[i])
            return routine1[i] > routine2[i];
    }
    return routine1.size() > routine2.size();
}
class Tree;
class Node
{
private:
    int index;
    int value;
    vector<Node *> child_list;
    Node *father;
public:
    friend class Tree;
    Node(const int input_index, const int input_value) : index(input_index), value(input_value)
    {
        child_list.clear();
        father = NULL;
    }
    ~Node()
    {
        child_list.clear();
        father = NULL;
    }
    void set_father(Node *ptr_father)
    {
        father = ptr_father;
    }
    void add_child(Node *ptr_child)
    {
        child_list.push_back(ptr_child);
    }
};
class Tree
{
private:
    vector<Node> node_list;
    int node_num, non_leaf_node_num, given_weight;
    vector<int> routine;
    vector< vector<int> > routine_set;
public:
    friend class Node;
    Tree()
    {
        node_list.clear();
    }
    ~Tree()
    {
        node_list.clear();
        routine.clear();
        routine_set.clear();
    }
    void init_tree()
    {
        cin >> node_num >> non_leaf_node_num >> given_weight;
        for (int i = 0; i < node_num; i++)
        {
            int temp;
            cin >> temp;
            node_list.push_back(Node(i, temp));
        }
        for (int i = 0; i < non_leaf_node_num; i++)
        {
            int index, child_num;
            cin >> index >> child_num;
            for (int j = 0; j < child_num; j++)
            {
                int child;
                cin >> child;
                node_list[index].add_child(&node_list[child]);
                node_list[child].set_father(&node_list[index]);
            }
        }
        routine.push_back(node_list[0].value);
        //root = &node_list[0];
    }
    void find_routine(int start, int sum)
    {
        if (node_list[start].child_list.empty())
        {
            sum += node_list[start].value;
            //routine.push_back(node_list[start].value);
            if (sum == given_weight)
            {
                routine_set.push_back(routine);
            }
            //routine.pop_back();
            return;
        }
        for (vector<Node *>::iterator it = node_list[start].child_list.begin(); it != node_list[start].child_list.end(); it++)
        {
            routine.push_back((*it)->value);
            find_routine((*it)->index, sum + node_list[start].value);
            routine.pop_back();
        }
    }
    void print_routine()
    {
        sort(routine_set.begin(), routine_set.end(), compare);
        for (vector< vector<int> >::iterator it = routine_set.begin(); it != routine_set.end(); it++)
        {
            for (vector<int>::iterator itin = it->begin(); itin != it->end(); itin++)
            {
                if (itin != it->begin())
                {
                    cout << " ";
                }
                cout << *itin;
            }
            cout << endl;
        }
    }
};
int main(void)
{
    Tree tree;
    tree.init_tree();
    tree.find_routine(0, 0);
    tree.print_routine();
    return 0;
}