#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cstdio>
using namespace std;
class Park;
class ParkTime
{
private:
    string in_time;
    string out_time;
public:
    ParkTime() {}
    ParkTime(string in, string out) : in_time(in), out_time(out) {}
    const string &get_in_time() const { return in_time; }
    const string &get_out_time() const { return out_time; }
};
class Info
{
friend class Park;
private:
    string id;
    int time;
    bool is_in;
public:
    Info(string i, int t, string in) : id(i), time(t), is_in(in == "in") {}
    friend bool operator<(const Info &info1, const Info &info2)
    {
        return (info1.id < info2.id) || (info1.id == info2.id && info1.time < info2.time);
    }
};
class Park
{
private:
    int total_num, total_query;
    vector<Info> info;
    map<string, int> duration;
    vector<int> query_time;
    map<string, bool> is_inputing;
    map<int, int> query_count;
    int max_duration;
    vector<string> max_id;
public:
    void init()
    {
        max_duration = 0;
        scanf("%d %d", &total_num, &total_query);
        for (int i = 0; i < total_num; i++)
        {
            string temp_id, temp_is_in;
            int temp_time;
            int h, m, s;
            char id_c[10], time_c[10], in_c[10];
            scanf("%s %d:%d:%d %s", id_c, &h, &m, &s, in_c);
            temp_id = string(id_c);
            temp_time = h * 3600 + m * 60 + s;
            temp_is_in = string(in_c);
            info.push_back(Info(temp_id, temp_time, temp_is_in));
            is_inputing[temp_id] = false;
        }
        sort(info.begin(), info.end());
        for (int i = 0; i < total_query; i++)
        {
            int temp_time;
            int h, m, s;
            scanf("%d:%d:%d", &h, &m, &s);
            query_time.push_back(h * 3600 + m * 60 + s);
        }
    }
    void process()
    {
        bool flag = false;
        string last_car_id;
        string temp_in;
        vector<int>::iterator its = query_time.begin();
        for (vector<Info>::iterator it = info.begin(); it <= info.end() - 1; it++)
        {
            if (it->id == (it + 1)->id && it->is_in == true && (it + 1)->is_in == false)
            {
                if (flag == false || last_car_id != it->id)
                {
                    its = query_time.begin();
                }
                flag = true;
                last_car_id = it->id;
                for (; its != query_time.end(); its++)
                {
                    if (*its >= it->time && *its < (it + 1)->time)
                    {
                        if (query_count.count(*its) == 0)
                        {
                            query_count[*its] = 1;
                        }
                        else
                        {
                            query_count[*its]++;
                        }
                    }
                    else if (*its >= (it + 1)->time)
                    {
                        break;
                    }
                }
                if (duration.count(it->id) == 0)
                {
                    duration[it->id] = (it + 1)->time - it->time;
                }
                else
                {
                    duration[it->id] += (it + 1)->time - it->time;                    
                }
                it++;
                if (max_duration < duration[it->id])
                    max_duration = duration[it->id];
            }
        }
    }
    void print()
    {
        map<int, int>::iterator pos = query_count.begin();
        for (int i = 0; i < total_query; i++)
        {
            if (query_count.count(query_time[i]))
            {
                printf("%d\n", query_count[query_time[i]]);
            }
            else
            {
                printf("0\n");
            }
        }
        for (map<string, int>::iterator it = duration.begin(); it != duration.end(); it++)
        {
            if (it->second == max_duration)
            {
                printf("%s ", (it->first).c_str());
            }
        }
        printf("%02d:%02d:%02d\n", max_duration / 3600, max_duration / 60 - max_duration / 3600 * 60, max_duration % 60);
    }
};
int main(void)
{
    Park p;
    p.init();
    p.process();
    p.print();
    return 0;
}