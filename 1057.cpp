#include <iostream>
#include <stack>
#include <cstdio>
#include <set>
//#include <algorithm>
using namespace std;
int main(void)
{
    int command_num;
    stack<int> Stack;
    char command_str[30];
    multiset<int> more;
    multiset< int, greater<int> > less;
    int median = 0;
    scanf("%d", &command_num);
    //cin >> command_num;
    for (int i = 0; i < command_num; i++)
    {
        //string command_str;
        //cin >> command_str;
        scanf("%s", command_str);
        if (command_str[1] == 'e')
        {
            if (median == 0)
                printf("Invalid\n");
            else
                printf("%d\n", median);
        }
        else if (command_str[1] == 'u')
        {
            int num;
            scanf("%d", &num);
            //cin >> num;
            Stack.push(num);
            if (num <= median)
                less.insert(num);
            else
                more.insert(num);
            if (less.size() > (more.size() + 1))
            {
                multiset<int>::iterator it = less.begin();
                more.insert(*it);
                less.erase(it);
            }
            else if (less.size() < more.size())
            {
                multiset<int>::iterator it = more.begin();
                less.insert(*it);
                more.erase(it);
            }
            median = *less.begin();
        }
        else
        {
            if (Stack.empty())
            {
                printf("Invalid\n");
                continue;
            }
            int num = Stack.top();
            Stack.pop();
            printf("%d\n", num);
            if (num <= median)
            {
                less.erase(less.find(num));
            }
            else
            {
                more.erase(more.find(num));
            }
            if (Stack.empty())
            {
                median = 0;
                continue;
            }
            else if (more.size() > less.size())
            {
                multiset<int>::iterator it = more.begin();
                less.insert(*it);
                more.erase(it);
            }
            else if (more.size() < (less.size() - 1))
            {
                multiset<int>::iterator it = less.begin();
                more.insert(*it);
                less.erase(it);
            }
            median = *less.begin();
        }
    }
}