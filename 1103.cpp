#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <numeric>
using namespace std;
class Factor
{
private:
    int *threshold, *powNum;
    int sum, count, point;
    int maxSum, currentSum;
    vector<int> answer;
    vector<int> result;
public:
    void init()
    {
        maxSum = currentSum = 0;
        cin >> sum >> count >> point;
        threshold = new int[sum + 1];
        powNum = new int[21];
        for (int i = 0; i <= sum; i++)
        {
            int temp = pow(i, 1.0 / point);
            threshold[i] = temp;
        }
        for (int i = 0; i <= 20; i++)
        {
            powNum[i] = pow(i, point);
        }
        answer.clear();
        result.clear();
    }
    bool compare(vector<int> &v, vector<int> &ans)
    {   
        vector<int>::iterator itrV = v.begin();
        vector<int>::iterator itrAns = ans.begin();
        if (currentSum > maxSum)
        {
            currentSum = maxSum;
            return true;
        }
        else if (currentSum == maxSum)
        {
            while (*itrV == *itrAns)
            {
                itrV++;
                itrAns++;
            }
            if (*itrV > *itrAns)
                return true;
        }
        return false;
    }
    void process()
    {
        dfs(0, 0, 1);
    }
    void dfs(int s, int cnt, int start)
    {
        if (s == sum && cnt == count)
        {
            if (compare(result, answer))
            {
                answer.clear();
                answer.assign(result.begin(), result.end());
            }
            return;
        }
        else if (s >= sum || cnt >= count)
        {
            return;
        }
        
        for (int i = start; i <= threshold[(sum - s) / (count - cnt)]; i++)
        {
            if (s + powNum[i] > sum)
                break;
            result.push_back(i);
            currentSum += i;
            dfs(s + powNum[i], cnt + 1, i);
            result.pop_back();
            currentSum -= i;
        }
    }
    void print()
    {
        if (answer.empty())
        {
            cout << "Impossible" << endl;
        }
        else
        {
            cout << sum;
            for (vector<int>::iterator it = answer.end() - 1; it >= answer.begin(); it--)
            {
                if (it != answer.end() - 1)
                    cout << " + ";
                else
                    cout << " = ";
                cout << *it << "^" << point;
            }
            cout << endl;
        }
    }
};
int main(void)
{
    Factor f;
    f.init();
    f.process();
    f.print();
    return 0;
}