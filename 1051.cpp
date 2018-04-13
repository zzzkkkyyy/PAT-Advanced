#include <iostream>
#include <stack>
#define ERROR {yes = false; break;}
using namespace std;
int main(void)
{
    stack<int> Stack;
    bool yes = true;
    int capacity, push_num, test_num;
    int count = 1;
    cin >> capacity >> push_num >> test_num;
    capacity++;
    Stack.push(0);
    for (int i = 0; i < test_num; i++)
    {
        count = 1;
        yes = true;
        //while (Stack.top() != 0)
        //    Stack.pop();
        for (int j = 0; j < push_num; j++)
        {
            int current_top;
            cin >> current_top;
            if (yes)
            {
                if (current_top < Stack.top())
                {
                    yes = false;
                }
                else
                {
                    while (Stack.top() < current_top)
                    {
                        if (count > push_num)
                        {
                            yes = false;
                            break;
                        }
                        if (Stack.size() == capacity)
                        {
                            if (current_top != Stack.top())
                            {
                                yes = false;
                                break;
                            }
                            break;
                        }
                        Stack.push(count++);
                    }
                    if (yes)
                    {
                        Stack.pop();
                    }
                }
            }
        }
        if (yes)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}