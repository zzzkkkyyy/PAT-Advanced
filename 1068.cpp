#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <map>
#include <stack>
using namespace std;
class A
{
private:
    int *a, num, price;
    vector<int> result;
    int **dp;
    bool **isFind;
public:
    void init()
    {
        scanf("%d %d", &num, &price);
        a = new int[num + 1];
        dp = new int *[num + 1];
        isFind = new bool *[num + 1];
        for (int i = 0; i <= num; i++)
        {
            dp[i] = new int[price + 1];
            isFind[i] = new bool[price + 1];
            if (i)
                scanf("%d", &a[i]);
        }
        for (int i = 0; i <= num; i++)
        {
            dp[i][0] = 0;
        }
        for (int i = 0; i <= price; i++)
        {
            dp[0][i] = 0;
            for (int j = 0; j <= num; j++)
            {
                isFind[j][i] = false;
            }
        }
        sort(a + 1, a + num + 1, greater<int>());
    }
    void process()
    {
        stack<int> s;
        for (int i = 1; i <= num; i++)
        {
            for (int j = 1; j <= price; j++)
            {
                if (j < a[i] || dp[i - 1][j] > (dp[i - 1][j - a[i]] + a[i]))
                {
                    dp[i][j] = dp[i - 1][j];
                }
                else
                {
                    dp[i][j] = dp[i - 1][j - a[i]] + a[i];
                    isFind[i][j] = true;
                }
            }
        }
        if (dp[num][price] == price)
        {
            bool flag = true;
            for (int i = num; i >= 1; i--)
            {
                if (price <= 0)
                    break;
                if (isFind[i][price] == true)
                {
                    if (flag)
                        printf("%d", a[i]);
                    else
                        printf(" %d", a[i]);
                    flag = false;
                    price -= a[i];
                }
            }
            printf("\n");
        }
        else
        {
            printf("No Solution\n");
        }
    }
};
int main(void)
{
    A a;
    a.init();
    a.process();
}