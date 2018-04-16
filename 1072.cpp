#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;
#define INT16_MAX 32767

class Graph
{
private:
    int house_num, station_num, road_num, threshold;
    int node_num;
    double min_result, ave_result;
    int choice;
    int **road;
    int *min_dist;
    bool *is_visited;
    int *house_to_station;
public:
    Graph() : min_result(0), ave_result(INT16_MAX), choice(-1) {}
    int convert(string str)
    {
        if (str[0] == 'G')
        {
            return atoi(str.substr(1).c_str()) - 1 + house_num;
        }
        else
        {
            return atoi(str.c_str()) - 1;
        }
    }
    void init()
    {
        cin >> house_num >> station_num >> road_num >> threshold;
        node_num = house_num + station_num;
        is_visited = new bool[node_num];
        road = new int *[node_num];
        min_dist = new int[node_num];
        house_to_station = new int[house_num];
        for (int i = 0; i < node_num; i++)
        {
            is_visited[i] = false;
            house_to_station[i] = INT16_MAX;
            road[i] = new int[node_num];
            for (int j = 0; j < node_num; j++)
            {
                road[i][j] = INT16_MAX;
            }
            road[i][i] = 0;
        }
        for (int i = 0; i < road_num; i++)
        {
            string start, end;
            int s, e, length;
            cin >> start >> end >> length;
            s = convert(start);
            e = convert(end);
            road[s][e] = road[e][s] = length;
        }
    }
    void reset(int start)
    {
        for (int i = 0; i < node_num; i++)
        {
            is_visited[i] = (i == start) ? true : false;
            min_dist[i] = min(road[start][i], INT16_MAX);
        }
    }
    void process()
    {
        for (int i = house_num; i < node_num; i++)
        {
            reset(i);
            int count = node_num - 1;
            int min_l, min_pt;
            while (count--)
            {
                min_l = INT16_MAX;
                for (int j = 0; j < node_num; j++)
                {
                    if (is_visited[j] == false)
                    {
                        if (min_dist[j] < min_l)
                        {
                            min_l = min_dist[j];
                            min_pt = j;
                        }
                    }
                }
                is_visited[min_pt] = true;
                //cout << min_pt << ": " << min_l << " ";
                for (int j = 0; j < node_num; j++)
                {
                    if (is_visited[j] == false)
                    {
                        if (min_dist[j] > (min_l + road[min_pt][j]))
                        {
                            min_dist[j] = min_l + road[min_pt][j];
                        }
                    }
                }
            }
            int house_min_l = INT16_MAX;
            double sum_l = 0;
            bool flag = true;
            for (int k = 0; k < house_num; k++)
            {
                sum_l += min_dist[k];
                if (house_min_l > min_dist[k])
                {
                    house_min_l = min_dist[k];
                }
                if (min_dist[k] > threshold)
                {
                    flag = false;
                    break;
                }
            }
            if (flag == false)
            {
                continue;
            }
            sum_l /= house_num;
            //cout << house_min_l << " " << sum_l << endl;
            if (house_min_l > min_result || (house_min_l == min_result && sum_l < ave_result))
            {
                for (int k = 0; k < house_num; k++)
                {
                    house_to_station[k] = min_dist[k];
                }
                choice = i;
                min_result = house_min_l;
                ave_result = sum_l;
            }
            //cout << endl;
        }
    }
    void print()
    {
        if (choice == -1)
        {
            cout << "No Solution" << endl;
        }
        else
        {
            cout << "G" << choice - house_num + 1 << endl;
            cout << setiosflags(ios::fixed) << setprecision(1) << ((int)(min_result * 10 + 0.5)) * 1.0 / 10 << " " << setiosflags(ios::fixed) << setprecision(1) << ((int)(ave_result * 10 + 0.5)) * 1.0 / 10 << endl;
        }
    }
};

int main(void)
{
    Graph g;
    g.init();
    g.process();
    g.print();
    return 0;
}