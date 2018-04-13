#include <iostream>
using namespace std;
int main(void)
{
    int num, MaxSum = 0, CurrentSum = 0;
    int start = 0, end = 0, TempStart = -1;
    cin >> num;
    int *data = new int[num];
    for (int i = 0; i < num; i++)
    {
        cin >> data[i];
        CurrentSum += data[i];
        if (CurrentSum > MaxSum)
        {
            MaxSum = CurrentSum;
            start = TempStart + 1;
            end = i;
        }
        else if (CurrentSum < 0)
        {
            CurrentSum = 0;
            TempStart = i;
        }
    }
    cout << MaxSum << ' ' << data[start] << ' ' << data[end] << endl;
    system("pause");
    return 0;
}