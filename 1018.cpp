#include <iostream>
#include <vector>
#define INTMAX 65535
using namespace std;

vector<int> routine, best_routine;
int send_num = 0, receive_num = 0, dist = 0;
int min_send_num = INTMAX, min_receive_num = INTMAX, min_dist = INTMAX;
int **road, right_cap, num_station;
vector<int>current_num;
bool *isVisited;

void dfs(int start, int end)
{
    if (start == end)
    {
        if (dist < min_dist)
        {
            min_dist = dist;
            min_send_num = send_num;
            min_receive_num = receive_num;
            best_routine.assign(routine.begin(), routine.end());
        }
        else if (dist == min_dist)
        {
            if ((send_num < min_send_num) || ((send_num == min_send_num) && (receive_num < min_receive_num)))
            {
                min_dist = dist;
                min_send_num = send_num;
                min_receive_num = receive_num;
                best_routine.assign(routine.begin(), routine.end());
            }
        }
        return;
    }
    for (int i = 0; i < num_station; i++)
    {
        if ((road[start][i] < INTMAX) && (isVisited[i] == false))
        {
            isVisited[i] = true;
            //cout << "route: ->" << i << endl;
            int send_copy = send_num;
            int receive_copy = receive_num;
            routine.push_back(i);
            dist += road[start][i];
            if (current_num[i] > right_cap)
            {
                receive_num += current_num[i] - right_cap;
            }
            else if (current_num[i] < right_cap)
            {
                if ((right_cap - current_num[i]) < receive_num)
                {
                    receive_num -= (right_cap - current_num[i]);
                }
                else
                {
                    send_num += (right_cap - current_num[i] - receive_num);
                    receive_num = 0;
                }
            }
            dfs(i, end);
            isVisited[i] = false;
            routine.pop_back();
            dist -= road[start][i];
            send_num = send_copy;
            receive_num = receive_copy;
        }
    }
}

int main(void)
{
    int pro_station, num_road;
    cin >> right_cap >> num_station >> pro_station >> num_road;
    num_station++;
    right_cap /= 2;
    isVisited = new bool[num_station];

    road = new int *[num_station];
    current_num.push_back(INTMAX);
    isVisited[0] = true;
    for (int i = 1; i < num_station; i++)
    {
        int temp;
        cin >> temp;
        current_num.push_back(temp);
        isVisited[i] = false;
    }
    for (int i = 0; i < num_station; i++)
    {
        road[i] = new int[num_station];
        for (int j = 0; j < num_station; j++)
        {
            road[i][j] = INTMAX;
        }
    }
    for (int i = 0; i < num_road; i++)
    {
        int sta1, sta2, len;
        cin >> sta1 >> sta2 >> len;
        road[sta1][sta2] = road[sta2][sta1] = len;
    }

    routine.clear();
    routine.push_back(0);

    dfs(0, pro_station);

    cout << min_send_num << ' ';
    for (vector<int>::iterator it = best_routine.begin(); it != best_routine.end(); it++)
    {
        if (it != best_routine.begin())
        {
            cout << "->";
        }
        cout << *it;
    }
    cout << ' ' << min_receive_num  << endl;
    return 0;
}