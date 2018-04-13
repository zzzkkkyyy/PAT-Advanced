#include <iostream>
#include <vector>
#include <map>
#define MAXINT 65535

using namespace std;

typedef struct Node
{
    int StartCity;
    int EndCity;
    int len;
}Node;

void MyDijkstra(int start, int end, int CityNum, int** road, map<int, int> &dist, map<int, int> &previous, map<int, int> TeamInCity)
{
    int *count = new int[CityNum];
    int *team = new int[CityNum];
    bool *S = new bool[CityNum];
    for (int i = 0; i < CityNum; i++)
    {
        team[i] = TeamInCity[i];
    }
    for (int i = 0; i < CityNum; i++)
    {
        count[i] = 1;
        if (road[start][i] < MAXINT)
        {
            previous[i] = start;
            dist[i] = road[start][i];
            team[i] = team[start] + TeamInCity[i];
        }
        else
        {
            previous[i] = -1;
            dist[i] = MAXINT;
            team[i] = TeamInCity[i];
        }
        S[i] = false;
    }

    dist[start] = 0;
    S[start] = true;
    team[start] = TeamInCity[start];
    int u = start;

    for (int i = 1; i < CityNum; i++)
    {
        int min = MAXINT;
        for (int j = 0; j < CityNum; j++)
        {
            if (!S[j])
            {
                if (dist[j] < min)
                {
                    u = j;
                    min = dist[j];
                }
            }
        }
        S[u] = true;
        for (int j = 0; j < CityNum; j++)
        {
            if (S[j] == true)
            {
                continue;
            }
            if ((dist[u] + road[u][j]) < dist[j])
            {
                dist[j] = dist[u] + road[u][j];
                previous[j] = u;
                team[j] = team[u] + TeamInCity[j];
                count[j] = count[u];
            }
            else if ((dist[u] + road[u][j]) == dist[j])
            {
                if (team[j] < (team[u] + TeamInCity[j]))
                {
                    previous[j] = u;
                    team[j] = team[u] + TeamInCity[j];
                }
                count[j] += count[u];
            }
        }
    }
    cout << count[end] << ' ' << team[end] << endl;
}

int main(void)
{
    int CityNum, RoadNum, BeginCity, EndCity;
    map<int, int> TeamInCity;
    map<int, int> MinDist;
    map<int, int> PreviousPoint;

    cin >> CityNum >> RoadNum >> BeginCity >> EndCity;
    int **road = new int *[CityNum];
    for (int i = 0; i < CityNum; i++)
    {
        road[i] = new int[CityNum];
        for (int j = 0; j < CityNum; j++)
        {
            road[i][j] = MAXINT;
        }
    }
    
    for (int i = 0; i < CityNum; i++)
    {
        cin >> TeamInCity[i];
    }
    for (int i = 0; i < RoadNum; i++)
    {
        int len, start, end;
        cin >> start >> end >> len;
        road[start][end] = road[end][start] = len;
    }

    MyDijkstra(BeginCity, EndCity, CityNum, road, MinDist, PreviousPoint, TeamInCity);
    
    system("pause");
    return 0;
}