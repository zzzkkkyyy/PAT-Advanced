#include <iostream>
#include <vector>
#define MAXTIME 540
using namespace std;

int main(void)
{
    int NumWin, MaxCap, NumCus, NumCusQuery;
    int CusFinish = 0;
    cin >> NumWin >> MaxCap >> NumCus >> NumCusQuery;
    vector<int> CusTime;
    int *ask = new int[NumCusQuery];
    int *WinTime = new int[NumWin];
    int *CusAsk = new int[NumCus];
    vector<int> *queue = new vector<int>[NumWin];
    for (int i = 0; i < NumCus; i++)
    {
        int temp;
        cin >> temp;
        CusTime.push_back(temp);
    }
    for (int i = 0; i < NumWin; i++)
    {
        WinTime[i] = 0;
    }
    for (int i = 0; i < NumCusQuery; i++)
    {
        cin >> ask[i];
        ask[i]--;
    }

    if (NumCus <= NumWin * MaxCap)
    {
        for (int i = 0; i < NumCus; i++)
        {
            queue[i % NumWin].push_back(i);
        }
        for (int i = 0; i < NumCus; i++)
        {
            WinTime[i % NumWin] += CusTime[i];
            CusAsk[i] = WinTime[i % NumWin];
        }
    }
    else
    {
        int current = 0;
        for (current = 0; current < NumWin * MaxCap; current++)
        {
            queue[current % NumWin].push_back(current);
        }
        while (current < NumCus)
        {
            int minwin = 0;
            for (int i = 0; i < NumWin; i++)
            {
                if ((WinTime[i] + CusTime[queue[i][0]]) < (WinTime[minwin] + CusTime[queue[minwin][0]]))
                {
                    minwin = i;
                }
            }
            WinTime[minwin] += CusTime[queue[minwin][0]];
            CusAsk[queue[minwin][0]] = WinTime[minwin];
            queue[minwin].erase(queue[minwin].begin());
            queue[minwin].push_back(current++);
        }
        for (int i = 0; i < NumWin * MaxCap; i++)
        {
            WinTime[i % NumWin] += CusTime[queue[i % NumWin][i / NumWin]];
            CusAsk[queue[i % NumWin][i / NumWin]] = WinTime[i % NumWin];
        }
    }
    
    for (int i = 0; i < NumCusQuery; i++)
    {
        if (CusAsk[ask[i]] - CusTime[ask[i]] >= MAXTIME)
        {
            cout << "Sorry" << endl;
        }
        else
        {
            if ((8 + CusAsk[ask[i]] / 60) < 10)
                cout << 0;
            cout << 8 + CusAsk[ask[i]] / 60 << ':';
            if (CusAsk[ask[i]] % 60 < 10)
                cout << 0;
            cout << CusAsk[ask[i]] % 60 << endl;
        }
    }
    return 0;
}